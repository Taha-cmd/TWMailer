#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

#include <signal.h>
#include "Infrastructure/configReader.h"
#include "client.class.h"
#include "functions.h"
#include "message.h"

void cleanUp(int placeholder, void* client)
{
    (*(Client*)client).~Client();
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

    ConfigReader reader(std::cin);

    while(true)
    {
        std::cout << "enter a command: ";
        std::getline(std::cin, command);
        std::cout << "Entered command: " << command << std::endl;
        
        if(lower(command) == "send")
        {
            std::string sender, recipient, subject, message;

            reader.ReadLineParameter("Sender", sender, 8);
            reader.ReadLineParameter("Empfänger", recipient, 8);
            reader.ReadLineParameter("Betreff", subject, 80);
            reader.ReadTextParameter("Nachricht", message, 10000);

            Message msg(sender, recipient, subject, message);
            std::string sendRequest = "SEND\n";
            sendRequest += msg.ToString();

            client.sendMessage(sendRequest);
        }
        else if(lower(command) == "quit")
            break;
    
        std::string msg = client.readMessage();
        std::cout << msg.size() << std::endl;
        std::cout << msg << std::endl;
    }

    exit(EXIT_SUCCESS);
}
