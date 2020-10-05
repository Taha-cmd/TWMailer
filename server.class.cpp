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
    shutDown();
}

void Server::shutDown()
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
    listening = true;
}

int Server::acceptClient()
{
    int newSocket = accept(sd, (struct sockaddr*)&clientIP, &addrlen);

    return newSocket;
}


std::string Server::readMessage(int socket)
{
    int size = std::stoi( readLineFromSocket(socket) );
    std::string body = readNBytesFromSocket(socket, size);
    return body;
}

void Server::sendMessage(int socket, const std::string& message)
{
    sendNBytes(socket, std::to_string(message.size()) + "\n", std::to_string( message.size() ).size() + 1);
    sendNBytes(socket, message, message.size());
}


void Server::handleRequest(int socket)
{
    // here use readline function to parse the request

    while(true)
    {
        std::string request = this->readMessage(socket);

        //        std::cout << request << std::endl;
        //std::cout << request.size() << std::endl;


        std::string command = lower( readLine(request) );

        if(commands.find(command) == commands.end()){
            sendMessage(socket, "unknown command");
            continue;
        }
        
        if(command == "quit"){
            std::cout << "client exited" << std::endl;
            break;
        }


            // handle commands, maybe write a function for each command
        if(command == "send")
        {
            std::cout << "YAY" << std::endl;
        }
        else if( command == "read" )
        {

        } 
        else if( command == "list" )
        {

        } 
        else if( command == "delete" )
        {

        } else if( command == "send" ){

        }

        std::cout << request << std::endl;
        std::cout << request.size() << std::endl;

        this->sendMessage(socket, request);
        std::cout << command << std::endl; 
    }

    close(socket);
}