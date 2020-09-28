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


#include "functions.h"
#include "server.class.h"


int main(int argc, char** argv)
{

    if(argc != 2)
        error_and_die("usage server <port>");

    Server server(AF_INET, SOCK_STREAM, 0);
    server.start(argv[1], BACKLOG);

    std::cout << "listening on port " << argv[1] << std::endl;
    while(true)
    {
        int newSocket = server.acceptClient();
        if (newSocket > 0)
        {
            while(true)
            {
                int size = server.readBodySize(newSocket);
                std::string command = server.readBody(newSocket, size);

                std::cout << size << std::endl;
                std::cout << command << std::endl;
            }
        }
    }
}

            //std::cout << msg << std::endl;
            //write(clientSD, buffer, strlen(buffer));

            /*sdFlags = fcntl( newSocket, F_GETFL );
            sdFlags |= O_NONBLOCK;
            fcntl( newSocket, F_SETFL, sdFlags );
            std::string msg = "";

            do
            {
                size = recv(newSocket, buffer, BUFFERSIZE - 1, 0);
                std::cout << size << std::endl;
                buffer[size] = '\0';
                msg.append(buffer);
            } while ( size > 0); */