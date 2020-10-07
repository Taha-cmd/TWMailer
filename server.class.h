#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <set>
#include <thread>
#include <unistd.h>
#include <sstream>

#include "Infrastructure/functions.h"
#include "messageHandler.h"
#include "Database/messageRepository.h"
#include "Infrastructure/message.h"

enum Command {Read, Delete, List, Quit};


class Server {
     public:

        Server(int, int, int, const std::string&);
        virtual ~Server();

        bool isListening() const { return listening; };
        void shutDown();
        
        void start(const std::string&, int);
        int acceptClient();
        std::string readMessage(int);
        void sendMessage(int, const std::string&);

        void handleRequest(int);

     private:
         bool listening;
         int sd;

         int domain;
         int type;
         int protocol;

         char buffer[BUFFERSIZE];
         struct sockaddr_in serverIP;
         struct sockaddr_in clientIP;
         socklen_t addrlen;

         MessageRepository* messageDb;
         MessageHandler* messageHandler;

         std::set<std::string> commands = {"send", "read", "list", "delete", "quit"};
};