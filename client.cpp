#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdexcept>
#include <signal.h>

#include "ClientDependencies/configReader.h"
#include "ClientDependencies/client.class.h"
#include "Infrastructure/functions.h"
#include "Infrastructure/message.h"


void cleanUp(int placeholder, void* client)
{
    (*(Client*)client).shutDown();
}

int main(int argc, char** argv)
{
    if(argc != 3)
        error_and_die("usage: client <ip4> <port>");

    Client client(AF_INET, SOCK_STREAM, 0);
    
    signal(SIGINT, exitProgram);

    if( (on_exit(cleanUp, (void*)&client)) != 0 )
        error_and_die("error registering exit handler");

    
    client.connectToServer(argv[1], argv[2]);

    std::string command;
    client.printHelp();

    ConfigReader reader(std::cin);

    Session session;
    session.username = "anonymous";

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        
        try
        {
            std::string sendRequest;

            if(  lower(command) == "login" )
            {
                std::string username, password;

                reader.ReadLineParameter("Username", username, 8);
                reader.ReadPassword(password, 24);

                sendRequest = "LOGIN\n";
                sendRequest += username + "\n";
                sendRequest += password + "\n";

                client.sendMessage(sendRequest);
                std::string response = client.readMessage();
                std::cout << response << std::endl;

                if(response == "Logged in Successfully")
                    session.username = username;

                continue;
            }
            else if( lower(command) == "send" )
            {
                std::string recipient, subject, message;

                reader.ReadLineParameter("Empfänger", recipient, 8);
                reader.ReadLineParameter("Betreff", subject, 80);
                reader.ReadTextParameter("Nachricht", message, 10000);

                std::cout << session.username << std::endl;
                                std::cout << session.username.length() << std::endl;
                Message msg(session.username, recipient, subject, message);
                sendRequest = "SEND\n";
                sendRequest += msg.ToNetworkString();
            }
            else if( lower(command) == "list" )
            {
                sendRequest = "LIST\n";
            }
            else if(  lower(command) == "read" || lower(command) == "delete" )
            {
                std::string number;

                reader.ReadLineParameter("Message number", number, 8);

                sendRequest = lower(command) == "read" ? "READ\n" : "DELETE\n";
                sendRequest += number + "\n";
            }
            else if ( lower(command) == "help" )
            {
                client.printHelp();
                continue;
            }
            else if( lower(command) == "quit" )
                break;
            else
                sendRequest = command;

            std::cout << "Sending Request: [" << sendRequest << "] at " << getCurrentTime() << std::endl;
            client.sendMessage(sendRequest);

            std::cout << "Start waiting for Response, at " << getCurrentTime() << std::endl;
            std::string response = client.readMessage();
            std::cout << "Response received, at " << getCurrentTime() << std::endl;
            std::cout << "response: \n\n" << response << std::endl;
        }
        catch(const ConfigReaderException& e)
        {
            std::cerr << "ERROR: " <<  e.what() << std::endl;
        }
        catch(const std::invalid_argument& ex)
        {
            std::cerr << "ERROR: " <<  ex.what() << std::endl;
        }
        catch(...)
        {
            std::cerr << "unknown error" << std::endl;
        }
    }

    exit(EXIT_SUCCESS);
}
