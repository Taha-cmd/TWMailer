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


#include "../Infrastructure/functions.h"


// this class implements the socket api for the client side in an easy and understandable object oriented way
// connect to the server, send and receive messages in one line, the ugly c functions are in the background

class Client {
     public:

        Client(int, int, int);
        virtual ~Client();

        bool isConnected() const { return connected; };
        bool isLoggedIn() const { return loggedIn; };
        void shutDown();
        
        void connectToServer(const std::string&, const std::string&);
        std::string readMessage();
        void sendMessage(const std::string&);
        void printHelp() const;


     private:
         bool connected;
         bool loggedIn;
         int sd;

         int domain;
         int type;
         int protocol;
         
         struct sockaddr_in serverIP;
};

 
