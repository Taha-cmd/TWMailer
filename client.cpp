#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "client.class.h"
#include "functions.h"
#define BUFFERSIZE 1024


int main(int argc, char** argv)
{

    if(argc != 3)
        error_and_die("usage: client <ip4> <port>");

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0)
        error_and_die("error creating socket");

    struct sockaddr_in serverIP;
    memset( &serverIP, 0, sizeof(serverIP) );
    serverIP.sin_family = AF_INET;
    serverIP.sin_port = htons(std::stoi(argv[2]));

    if( inet_aton(argv[1], &serverIP.sin_addr) == 0 )
        error_and_die("error converting ip address");

    if( ( connect( sd, (struct sockaddr *)&serverIP, sizeof(serverIP) ) ) != 0)
        error_and_die("error connecting to server");

    char buffer[BUFFERSIZE];
    memset( buffer, 0, BUFFERSIZE);

    int size = recv(sd, buffer, BUFFERSIZE - 1, 0);

    buffer[BUFFERSIZE - 1] = '\0';
    if(size <= 0)
        error_and_die("error retrieving data from socket");

    for(auto c : buffer)
        std::cout << c;


}


