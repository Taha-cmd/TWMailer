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


class Client {
     public:

        Client(int, int, int);
        virtual ~Client();

        bool isConnected() const { return connected; };
        
        void connectToServer(const std::string&, const std::string&);
        std::string read();
        void sendMessage(const std::string&);


     private:
         bool connected;
         int sd;

         int domain;
         int type;
         int protocol;

         char buffer[BUFFERSIZE];
         struct sockaddr_in serverIP;
};

 
