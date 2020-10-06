#include "message.h"

Message::Message(std::string sender, std::string recipient, std::string subject, std::string message)
    : sender(sender), recipient(recipient), subject(subject), message(message)
{
    Validate();
}

Message::~Message()
{
}

void Message::Validate()
{
    if(sender.size() > 8)
        throw std::invalid_argument("sender.size() must be smaller than 9.");

    if(recipient.size() > 8)
        throw std::invalid_argument("recipient.size() must be smaller than 9.");
    
    if(subject.size() > 80)
        throw std::invalid_argument("subject.size() must be smaller than 9.");
}