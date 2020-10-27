
#include "server.class.h"


Server::Server(int domain, int type, int protocol, const std::string& mailpool)
    :listening(false), sd(-1), domain(domain), type(type), protocol(protocol), addrlen(sizeof(struct sockaddr_in))
{
    if ( (sd = socket(domain, type, protocol)) < 0)
        error_and_die("error creating socket");

    memset( &serverIP, 0, sizeof(serverIP) );
    memset( &clientIP, 0, sizeof(clientIP) );

    messageDb = new MessageRepository(FileSystem(mailpool));
    messageHandler = new MessageHandler(*messageDb);
    clientsManager = new ClientsManager();
    LDAP = new LdapClient(FH_LDAP_URI, FH_LDAP_SEARCHBASE);
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

    if(clientsManager != nullptr)
        delete clientsManager;

    if(LDAP != nullptr)
        delete LDAP;
        
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

    if( listen(sd, backlog) == -1 )
        error_and_die("error starting to listen to port");

    listening = true;
    messageDb->Establish();

    try{
        LDAP->connect();
    } catch (const LdapClientException& ex) {
       error_and_die(ex.what()); 
    }

}

ConnectedClient Server::acceptClient()
{
    int newSocket = accept(sd, (struct sockaddr*)&clientIP, &addrlen);

    return ConnectedClient(newSocket, inet_ntoa(clientIP.sin_addr));
}

std::string Server::readMessage(int socket)
{
    
    int size = std::stoi( readLineFromSocket(socket) );
    if(size == 0)
        return "quit";

    std::string body = readNBytesFromSocket(socket, size);
    return body;
}

void Server::sendMessage(int socket, const std::string& message)
{
    sendNBytes(socket, std::to_string(message.size()) + "\n", std::to_string( message.size() ).size() + 1);
    sendNBytes(socket, message, message.size());
}


void Server::handleClient(ConnectedClient client)
{
    assert(messageDb != nullptr);
    assert(messageHandler != nullptr);
    assert(clientsManager != nullptr);
    assert(LDAP != nullptr);

    std::cout << "Client " + client.getIP() + " connected" << std::endl;

    if(!clientsManager->exists(client.getIP())) 
        clientsManager->addClient(client.getIP());

    Session session;

    while(true)
    {
        try
        {
            std::string request = this->readMessage(client.getSocket());
            std::string command = lower(readLine(request));
            std::string response;

            if (commands.find(command) == commands.end())
            {
                sendMessage(client.getSocket(), "unknown command");
                continue;
            }

            if (command == "quit")
            {
                std::cout << "ending session for " + session.username << std::endl;
                break;
            }

            if(clientsManager->isBlocked(client.getIP()))
            {
                int remainingBlockTimeInSeconds = clientsManager->getRemainingBlockTime(client.getIP());
                sendMessage(client.getSocket(), "You are blocked for another " + std::to_string(remainingBlockTimeInSeconds) + " seconds");
                continue;
            }

            if(command != "login" && !client.isLoggedIn())
            {
                sendMessage(client.getSocket(), "Error, you need to be logged in to perform this action");
                continue;
            }

            if(command == "login")
            {
                std::cout << "Received Login Request" << std::endl;
                
                if(client.isLoggedIn())
                {
                    sendMessage(client.getSocket(), "You are allready logged in");
                    continue;
                }

                std::string username = readLine( request );
                std::string password = readLine( request );

                //TODO: validate username and password 
                bool success = LDAP->authenticateUser(username, password);

                if(!success)
                {
                    clientsManager->increaseFailedAttempts(client.getIP());
                    response = "Invalid Credentials";

                    int remainingAttempts = clientsManager->getRemainingAttempts(client.getIP());

                    if(remainingAttempts > 0)
                        response += ", remaining attempts: " + std::to_string(remainingAttempts);
                    else
                        response += ", you are not blocked for " + std::to_string( clientsManager->getRemainingBlockTime(client.getIP()) ) + " seconds";   
                }
                else
                {
                    clientsManager->resetFailedAttempts(client.getIP());
                    client.startSession();
                    session.username = username;
                    std::cout << "Starting session for " + username << std::endl;
                    response = "Logged in Successfully";
                }      
            }
            else if (command == "send")
            {
                std::cout << "Received Send Request" << std::endl;
                response = messageHandler->HandleSendMessage(request);
            }
            else if (command == "read" || command == "delete")
            {
                std::cout << "Received " << command << " Request" << std::endl;
                std::string number = readLine( request );
                response = command == "read" ?  messageHandler->ReadMessage(session.username, number)
                                            : messageHandler->DeleteMessage(session.username, number);     
            }
            else if (command == "list")
            {
                std::cout << "Received List Request" << std::endl;
                response = messageHandler->ListMessages( session.username );
            }
            
            this->sendMessage( client.getSocket(), response );
        }
        catch(const MessageHandlerException& msgEx )
        {
            std::cerr << msgEx.what() << std::endl;
            this->sendMessage( client.getSocket(), "ERROR: " + std::string(msgEx.what()) );
        }
        catch(const MessageRepositoryException& ex)
        {
            std::cerr << ex.what() << std::endl;
            this->sendMessage( client.getSocket(), "ERROR: " + std::string(ex.what()) );
        }
        catch(const std::exception& e)
        {
            std::cerr << "Unexpected Error: " << e.what() << '\n';
        }
        catch(...)
        {
            std::cerr << "unknown error"  << std::endl;
        }
    }

    client.closeConnection();
}


