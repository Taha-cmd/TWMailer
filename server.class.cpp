
#include "server.class.h"


Server::Server(int domain, int type, int protocol, const std::string& mailpool)
    :listening(false), sd(-1), domain(domain), type(type), protocol(protocol), addrlen(sizeof(struct sockaddr_in))
{
    if ( (sd = socket(domain, type, protocol)) < 0)
        error_and_die("error creating socket");

    memset( buffer, 0, BUFFERSIZE );
    memset( &serverIP, 0, sizeof(serverIP) );
    memset( &clientIP, 0, sizeof(clientIP) );

    messageDb = new MessageRepository(FileSystem(mailpool));
    messageHandler = new MessageHandler(*messageDb);
}

Server::~Server()
{    
    shutDown();
}

void Server::shutDown()
{
    if(messageDb != nullptr)
        delete messageDb;

    if(messageHandler != nullptr)
        delete messageHandler;
        
    close(sd);
}

void Server::start(const std::string& port, int backlog)
{
    std::cout << "Starting Server" << std::endl;
    std::cout << "Start Tcp- Listener on Port: " << port << std::endl;

    serverIP.sin_family = domain;
    serverIP.sin_addr.s_addr = INADDR_ANY;
    
    try{
        serverIP.sin_port = htons(std::stoi(port));
    } catch(...) {
        error_and_die("error parsing port");
    }
        

    if( ( bind(sd, (struct sockaddr*)&serverIP, sizeof(serverIP)) ) != 0)
        error_and_die("error binding socket");

    listen(sd, backlog);
    listening = true;

    messageDb->Establish();
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
    assert(messageDb != nullptr);
    assert(messageHandler != nullptr);

    while(true)
    {
        try
        {
            std::string request = this->readMessage(socket);
            std::string command = lower(readLine(request));
            std::string response;

            if (commands.find(command) == commands.end())
            {
                sendMessage(socket, "unknown command");
                continue;
            }

            if (command == "quit")
            {
                std::cout << "client exited" << std::endl;
                break;
            }

            if (command == "send")
            {
                std::cout << "Received Send Request" << std::endl;
                response = messageHandler->HandleSendMessage(request);
            }
            else if (command == "read" || command == "delete")
            {
                std::cout << "Received " << command << " Request" << std::endl;
                std::string username = readLine( request );
                std::string number = readLine( request );
                response = command == "read" ?  messageHandler->ReadMessage(username, number)
                                            : messageHandler->DeleteMessage(username,  number);     
            }
            else if (command == "list")
            {
                std::cout << "Received List Request" << std::endl;
                std::string username = readLine( request );
                response = messageHandler->ListMessages( username );
            }
            
            this->sendMessage(socket, response);
        }
        catch(const MessageHandlerException& msgEx )
        {
            std::cout << msgEx.what() << std::endl;
            this->sendMessage( socket, "ERROR: " + std::string(msgEx.what()) );
        }
        catch(const MessageRepositoryException& ex)
        {
            std::cout << ex.what() << std::endl;
            this->sendMessage( socket, "ERROR: " + std::string(ex.what()) );
        }
        catch(const std::exception& e)
        {
            std::cerr << "Unexpected Error: " << e.what() << '\n';
        }
    }

    close(socket);
}


