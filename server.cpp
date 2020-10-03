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


#include "functions.h"
#include "server.class.h"

Server* server = nullptr;

void cleanUp(int signal)
{
    delete server;
    exit(EXIT_SUCCESS);
}


int main(int argc, char** argv)
{

    if(argc != 2)
        error_and_die("usage server <port>");


    signal(SIGINT, cleanUp);
    server = new Server(AF_INET, SOCK_STREAM, 0);
    server->start(argv[1], BACKLOG);

    std::cout << "listening on port " << argv[1] << std::endl;
    while(true)
    {
        int newSocket = server->acceptClient();

        // make this functionality in a thread
        if (newSocket > 0)
        {
            while(true)
            {
                std::string command = server->readMessage(newSocket);

                if(command == "quit"){
                    std::cout << "client exited" << std::endl;
                    break;
                }

                std::cout << command << std::endl;
                std::cout << command.size() << std::endl;
                server->sendMessage(newSocket, command);
            }
        }
        close(newSocket);
    }


    delete server;
    return 0;
}