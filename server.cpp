#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <string.h>


#include "functions.h"
#define BUFFERSIZE 1024

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
    strcpy(buffer, "hello world\0");
    
    socklen_t addrlen = sizeof(struct sockaddr_in);
    while(true)
    {
        int clientSD = accept(sd, (struct sockaddr*)&clientaddress, &addrlen);
        if (clientSD > 0)
        {
            send(clientSD, buffer, strlen(buffer), 0);
        }
    }
}