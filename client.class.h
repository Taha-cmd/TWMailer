#pragma once
 
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


#include "Infrastructure/functions.h"

class Client {
     public:

        Client(int, int, int);
        virtual ~Client();

        bool isConnected() const { return connected; };
        void shutDown();
        
        void connectToServer(const std::string&, const std::string&);
        std::string readMessage();
        void sendMessage(const std::string&);
        void printHelp() const;


     private:
         bool connected;
         int sd;

         int domain;
         int type;
         int protocol;

         char buffer[BUFFERSIZE];
         struct sockaddr_in serverIP;
};

 
