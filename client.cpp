#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdexcept>
#include <signal.h>

#include "Infrastructure/configReader.h"
#include "Infrastructure/functions.h"
#include "Infrastructure/message.h"
#include "client.class.h"

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

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        
        try
        {
            std::string sendRequest;

            if(lower(command) == "send")
            {
                std::string sender, recipient, subject, message;

                reader.ReadLineParameter("Sender", sender, 8);
                reader.ReadLineParameter("Empfänger", recipient, 8);
                reader.ReadLineParameter("Betreff", subject, 80);
                reader.ReadTextParameter("Nachricht", message, 10000);

                Message msg(sender, recipient, subject, message);
                sendRequest = "SEND\n";
                sendRequest += msg.ToNetworkString();
            }
            else if( lower(command) == "list" )
            {
                std::string username;

                reader.ReadLineParameter("Username", username, 8);

                sendRequest = "LIST\n";
                sendRequest += username;

            }
            else if(  lower(command) == "read" || lower(command) == "delete" )
            {
                std::string username, number;

                reader.ReadLineParameter("Username", username, 8);
                reader.ReadLineParameter("Message number", number, 8);

                sendRequest = lower(command) == "read" ? "READ\n" : "DELETE\n";
                sendRequest += username + "\n";
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
