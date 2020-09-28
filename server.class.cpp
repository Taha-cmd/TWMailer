#include "server.class.h"


Server::Server(int domain, int type, int protocol)
    :listening(false), sd(-1), domain(domain), type(type), protocol(protocol), addrlen(sizeof(struct sockaddr_in))
{
    if ( (sd = socket(domain, type, protocol)) < 0)
        error_and_die("error creating socket");

    memset( buffer, 0, BUFFERSIZE );
    memset( &serverIP, 0, sizeof(serverIP) );
    memset( &clientIP, 0, sizeof(clientIP) );
}

Server::~Server()
{
    close(sd);
}

void Server::start(const std::string& port, int backlog)
{
    serverIP.sin_family = domain;
    serverIP.sin_addr.s_addr = INADDR_ANY;
    serverIP.sin_port = htons(std::stoi(port));

    if( ( bind(sd, (struct sockaddr*)&serverIP, sizeof(serverIP)) ) != 0)
        error_and_die("error binding socket");

    listen(sd, backlog);
}

int Server::acceptClient()
{
    int newSocket = accept(sd, (struct sockaddr*)&clientIP, &addrlen);

    return newSocket;
}

int Server::readBodySize(int socket)
{
    std::string bodySize = readLineFromSocket(socket);

    return std::stoi(bodySize);
}

std::string Server::readBody(int socket, int size)
{
    std::string body = readNBytesFromSocket(socket, size);

    return body;
}