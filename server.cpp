#include <iostream>
#include <fstream>
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
#include <unistd.h>


#include "ServerDependencies/server.class.h"
#include "Infrastructure/LdapClient.h"

#define BACKLOG 5

void cleanUp(int placeholder, void* server)
{
    (*(Server*)server).shutDown();
}

int main(int argc, char** argv)
{
    if(argc != 3)
        error_and_die("usage server <port> <mailpool>");
    
    Server server(AF_INET, SOCK_STREAM, 0, argv[2]);

    signal(SIGINT, exitProgram);

    if( (on_exit(cleanUp, (void*)&server)) != 0 )
        error_and_die("error registering exit handler");

    server.start(argv[1], BACKLOG);

    std::cout << "listening on port " << argv[1] << std::endl;
    while(true)
    {
        ConnectedClient client = server.acceptClient();
        if(client.getSocket() > 0){
            std::thread requestHandler(&Server::handleClient, &server, client);
            requestHandler.detach();
        }         
    }   
    
    exit(EXIT_SUCCESS);
}