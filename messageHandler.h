
#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER

#include "Database/messageRepository.h"
#include "messageHandlerException.h"

#include <string>
#include <sstream>

#include "message.h"
#include "Infrastructure/functions.h"

class MessageHandler
{
    public:
        MessageHandler(MessageRepository& messageRepo);
        ~MessageHandler();

        std::string HandleSendMessage(const std::string request);
        std::string ListMessages(const std::string& username);
    private:
        MessageHandler();

        MessageRepository& messageRepo;
};

#endif