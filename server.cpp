#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <thread>


#include "functions.h"
#include "server.class.h"


void cleanUp(int placeholder, void* server)
{
    (*(Server*)server).shutDown();
}

int main(int argc, char** argv)
{

    if(argc != 2)
        error_and_die("usage server <port>");
    
    Server server(AF_INET, SOCK_STREAM, 0);

    signal(SIGINT, exitProgram);

    if( (on_exit(cleanUp, (void*)&server)) != 0 )
        error_and_die("error registering exit handler");

    server.start(argv[1], BACKLOG);

    std::cout << "listening on port " << argv[1] << std::endl;
    while(true)
    {
        int newSocket = server.acceptClient();
        if(newSocket > 0){
            std::thread requestHandler(&Server::handleRequest, &server, newSocket);
            requestHandler.detach();
        }         
    }
    

    exit(EXIT_SUCCESS);
}