#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "client.class.h"
#include "functions.h"



int main(int argc, char** argv)
{
    if(argc != 3)
        error_and_die("usage: client <ip4> <port>");

    Client client(AF_INET, SOCK_STREAM, 0);
    client.connectToServer(argv[1], argv[2]);
    
    std::string command;

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        client.sendMessage(command);
    }

    return 0;

}


