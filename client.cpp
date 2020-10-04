#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <signal.h>

#include "client.class.h"
#include "functions.h"


void cleanUp(int placeholder, void* client)
{
    (*(Client*)client).~Client();
}

int main(int argc, char** argv)
{
    if(argc != 3)
        error_and_die("usage: client <ip4> <port>");


    Client client(AF_INET, SOCK_STREAM, 0);
    
    signal(SIGINT, exitProgram);

    if( (on_exit(cleanUp, (void*)&client)) != 0 )
        error_and_die("error registering exit handler");
    
    client.connectToServer(argv[1], argv[2]);

    std::string command;

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        client.sendMessage(command);

        if( lower(command) == "quit" ){
            break;
        }
    
        std::string msg = client.readMessage();
        std::cout << msg.size() << std::endl;
        std::cout << msg << std::endl;
    }

    exit(EXIT_SUCCESS);
}


