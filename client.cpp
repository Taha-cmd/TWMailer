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


Client* client = nullptr;

void cleanUp(int signal)
{
    delete client;
    exit(EXIT_SUCCESS);
}


int main(int argc, char** argv)
{
    if(argc != 3)
        error_and_die("usage: client <ip4> <port>");

    signal(SIGINT, cleanUp);
    client = new Client(AF_INET, SOCK_STREAM, 0);
    client->connectToServer(argv[1], argv[2]);
    
    std::string command;

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        client->sendMessage(command);

        if(command == "quit"){
            break;
        }
    
        std::string msg = client->readMessage();
        std::cout << msg.size() << std::endl;
        std::cout << msg << std::endl;
    }


    delete client;
    return 0;
}


