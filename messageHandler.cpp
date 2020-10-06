#include "messageHandler.h"

MessageHandler::MessageHandler(MessageRepository& messageRepo)
    : messageRepo(messageRepo)
{
}

MessageHandler::~MessageHandler()
{
}

std::string MessageHandler::HandleSendMessage(const std::string request)
{
    std::size_t eofIndex = request.find("\n.\n");

    if(eofIndex == std::string::npos)
        throw MessageHandlerException("Invalid Send- Request Format: Request must be delimited by \\n.\\n");

    std::string requestCopy = request;
    requestCopy.erase(eofIndex);

    std::stringstream requestTextStream(requestCopy);
    std::string sender, recipient, subject, message;

    std::getline(requestTextStream, sender);

    if (sender.empty())
        throw MessageHandlerException("Invalid Send- Request Format: Sender cannot be empty.");

    std::getline(requestTextStream, recipient);

    if (recipient.empty())
        throw MessageHandlerException("Invalid Send- Request Format: Recipient cannot be empty.");

    std::getline(requestTextStream, subject);

    if (subject.empty())
        throw MessageHandlerException("Invalid Send- Request Format: Subject cannot be empty.");

    std::getline(requestTextStream, message);

    Message messageDto(sender, recipient, subject, message);
    messageRepo.Insert(messageDto);

    return "Message saved.";
}