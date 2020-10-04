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
    shutDown();
}

void Client::shutDown()
{
    this->sendMessage("quit");
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

std::string Client::readMessage()
{
    if(!this->connected)
        return "";

    int size = std::stoi( readLineFromSocket(sd) );
    std::string body = readNBytesFromSocket(sd, size);
    return body;
}

void Client::sendMessage(const std::string& message)
{
    if(!this->connected)
        return;

    sendNBytes(sd, std::to_string(message.size()) + "\n", std::to_string( message.size() ).size() + 1);
    sendNBytes(sd, message, message.size());
}