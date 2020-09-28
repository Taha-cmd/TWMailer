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


int main(int argc, char** argv)
{

    if(argc != 2)
        error_and_die("usage server <port>");

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd == -1)
        error_and_die("error creating socket");

    struct sockaddr_in address, clientaddress;

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(std::stoi(argv[1]));

    if( ( bind(sd, (struct sockaddr*)&address, sizeof(address)) ) != 0)
        error_and_die("error binding socket");

    listen(sd, 5);


    char buffer[BUFFERSIZE];
    //strcpy(buffer, "hello world\0");
    
    socklen_t addrlen = sizeof(struct sockaddr_in);
    long sdFlags;
    int size;

    std::cout << "listening on port " << argv[1] << std::endl;
    while(true)
    {
        int newSocket = accept(sd, (struct sockaddr*)&clientaddress, &addrlen);
        if (newSocket > 0)
        {
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

            std::string msg = readNBytesFromSocket(newSocket, 15);
            std::cout << msg << std::endl;
            std::cout << readLine(msg) << std::endl;
            
            //std::cout << msg << std::endl;
            //write(clientSD, buffer, strlen(buffer));
        }
    }
}