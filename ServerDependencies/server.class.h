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
#include <map>
#include <thread>
#include <unistd.h>
#include <sstream>

#include "../Infrastructure/functions.h"
#include "messageHandler.h"
#include "../Database/messageRepository.h"
#include "../Infrastructure/message.h"
#include "ConnectedClient.h"
#include "ClientsManager.h"
#include "../Infrastructure/LdapClient.h"



// similar like client.class, this class abstracts the ugly c socket functions for the server side
// the method handleRequest is a threaded method which parses the client's command and call the proper method from messageHandler

class Server {
     public:

        Server(int, int, int, const std::string&);
        virtual ~Server();

        bool isListening() const { return listening; };
        void shutDown();
        
        void start(const std::string&, int);
        ConnectedClient acceptClient();
        std::string readMessage(int);
        void sendMessage(int, const std::string&);

        void handleClient(ConnectedClient client);

     private:
         bool listening;
         int sd;

         int domain;
         int type;
         int protocol;

         struct sockaddr_in serverIP;
         socklen_t addrlen;

         MessageRepository* messageDb;
         MessageHandler* messageHandler;
         ClientsManager* clientsManager;
         LdapClient* LDAP;

         std::set<std::string> commands = {"login", "send", "read", "list", "delete", "quit"};
};