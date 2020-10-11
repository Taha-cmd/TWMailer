#include "messageHandler.h"

MessageHandler::MessageHandler(MessageRepository& messageRepo)
    : messageRepo(messageRepo)
{
}

MessageHandler::~MessageHandler()
{
}

std::string MessageHandler::HandleSendMessage(const std::string& request)
{
    std::size_t eofIndex = request.find("\n.\n");

    if(eofIndex == std::string::npos)
        throw MessageHandlerException("Invalid Send- Request Format: Request must be delimited by \\n.\\n");

    std::string requestCopy = request;
    requestCopy.erase(eofIndex);
    
    messageRepo.Insert( Message( requestCopy ) );

    return "Message saved.";
}

std::string MessageHandler::ListMessages(const std::string& username)
{   
    int number = 1;
    std::vector< Message > messages = messageRepo.GetMessages(username);
    std::string response = "total number of messages: " + std::to_string(messages.size()) + "\n";

    for(const auto& msg : messages )
    {
        response += "Betreff für Nachricht " + std::to_string(number) + ": " + msg.GetSubject() + "\n";
        number++;
    }

    return response;
}

std::string MessageHandler::ReadMessage(const std::string& username, const std::string& number)
{
    int messageIndex = parseIndex(number);
    Message message = messageRepo.GetMessage(username, messageIndex);

    return message.ToEmailFormat();
}

std::string MessageHandler::DeleteMessage(const std::string& username, const std::string& number)
{
    int messageIndex = parseIndex(number);
    messageRepo.DeleteMessage(username, messageIndex);

    return "OK\n";

}

int MessageHandler::parseIndex(const std::string& number) const
{
    int index;

    try {
        index = std::stoi( number ) - 1;
    } catch(...) {
        throw MessageHandlerException("Invalid Read- Request Format: Error parsing Message Number."); 
    }

    return index;
}