#include "message.h"

Message::Message(std::string sender, std::string recipient, std::string subject, std::string message)
    : sender(sender), recipient(recipient), subject(subject), message(message)
{
    Validate();
}

Message::Message(std::string text)
{
    sender = readLine( text );
    recipient = readLine( text );
    subject = readLine( text );
    message = text;
    Validate();
}

Message::~Message()
{
}

std::string Message::ToEmailFormat() const
{
    std::string response;

    response  = "Absender:  " + sender + "\n";
    response += "Empfänger: " + recipient + "\n";
    response += "Betreff:   " + subject + "\n";
    response += "Message: \n" + message + "\n";

    return response;
}

void Message::Validate()
{
    if(sender.size() > 8 || sender.empty())
        throw std::invalid_argument("sender.size() must be smaller than 9 and greater than 0.");

    if(recipient.size() > 8 || recipient.empty() )
        throw std::invalid_argument("recipient.size() must be smaller than 9 and greater than 0.");
    
    if(subject.size() > 80 || subject.empty() )
        throw std::invalid_argument("subject.size() must be smaller than 9 and greater than 0.");
}