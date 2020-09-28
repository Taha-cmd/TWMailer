#pragma once
 
#include <iostream>
#include <string>
#include "functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>


class Server {
     public:

        Server(int, int, int);
        virtual ~Server();

        bool isListening() const { return listening; };
        
        void start(const std::string&, int);
        int acceptClient();

        int readBodySize(int);
        std::string readBody(int, int);
        void sendMessage(const std::string&);


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
};