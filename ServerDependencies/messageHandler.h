
#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER



#include "../Database/messageRepository.h"
#include "messageHandlerException.h"

#include <string>
#include <sstream>

#include "../Infrastructure/message.h"
#include "../Infrastructure/functions.h"


// this class is the request handler for the server class
// the server calls one of these methods to handle requests
// this class communicates with the database and fetches the proper response to the server

class MessageHandler
{
    public:
        MessageHandler(MessageRepository& messageRepo);
        ~MessageHandler();

        std::string HandleSendMessage(const std::string& request);
        std::string ListMessages(const std::string& username);
        std::string ReadMessage(const std::string& username, const std::string& number);
        std::string DeleteMessage(const std::string& username, const std::string& number);
    private:
        MessageHandler();
        int parseIndex(const std::string&) const;

        MessageRepository& messageRepo;
};

#endif