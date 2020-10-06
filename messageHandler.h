
#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER

#include "Database/messageRepository.h"
#include "messageHandlerException.h"

#include <string>
#include <sstream>

#include "message.h"

class MessageHandler
{
    public:
        MessageHandler(MessageRepository& messageRepo);
        ~MessageHandler();

        std::string HandleSendMessage(const std::string request);
    private:
        MessageHandler();

        MessageRepository& messageRepo;
};

#endif