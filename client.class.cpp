#include "client.class.h"


Client::Client(int domain, int type, int protocol)
    :connected(false), sd(-1), domain(domain), type(type), protocol(protocol)
{
    if ( (sd = socket(domain, type, protocol)) < 0)
        error_and_die("error creating socket");

    memset(buffer, 0, BUFFERSIZE);
}

Client::~Client()
{
    close(sd);
}

void Client::connectToServer(const std::string& ip, const std::string& port)
{
    if(this->connected)
        close(sd);

    memset( &serverIP, 0, sizeof(serverIP) );
    serverIP.sin_family = domain;
    serverIP.sin_port = htons(std::stoi(port));

    if( inet_aton(ip.data(), &serverIP.sin_addr) == 0 )
        error_and_die("error converting ip address");

    if( ( connect( sd, (struct sockaddr *)&serverIP, sizeof(serverIP) ) ) != 0)
        error_and_die("error connecting to server");

    connected = true;

}

std::string Client::read()
{

    if(!this->connected)
        return "";

    std::string response = "";
    /*while( (recv(sd, buffer, BUFFERSIZE - 1, 0) > 0) this code will block
        need non blocking I/O
    {
        std::cout << size << std::endl;
        buffer[BUFFERSIZE - 1] = '\0';
        response.append(buffer);
    } */

    if( recv(sd, buffer, BUFFERSIZE - 1, 0) > 0){
        response.append(buffer);
        response.append("\0");
    } else {
        error_and_die("error reading from socket");
    }
        
    return response;

}

void Client::sendMessage(const std::string& message)
{
    if(!this->connected)
        return;

    int bytesSent = 0;
    int bytesLeft = message.size();
    int n = 0;

    while(bytesLeft > 0)
    {
        n = send( sd, message.data() + bytesSent, bytesLeft, 0 );
        if( n == -1)
            error_and_die("error sending message to server");

        bytesSent += n;
        bytesLeft -= n;
    }
}