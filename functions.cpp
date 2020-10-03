#include <iostream>
#include <unistd.h>
#include <string.h>

void error_and_die(const std::string& errorMsg)
{
    std::cerr << errorMsg << std::endl;
    exit(EXIT_FAILURE);
}

std::string readLine(std::string& message)
{
    std::string line = "";
    int index = 0;

    for(; index < message.size(); index++)
    {
        if(message.at(index) == '\n')
            break;

        line.push_back(message.at(index));
    }

    message = message.substr(index + 1,  message.size() - ( index  + 1 ) );
    return line;
}

std::string readLineFromSocket(int sd)
{
    std::string response = "";
    char charachter;
    int size;

    while(true)
    {
        size = read(sd, &charachter, 1);
        if(size == 1)
        {
            if(charachter == '\n')
                break;

            response.push_back(charachter);
        }
        else if(size == -1)
        {
            error_and_die("error reading charachters from socket in readLineFromSocket()");
        }
    }

    return response;
}

std::string readNBytesFromSocket(int socket, int size)
{
    char buffer[size+1];
    memset( buffer, 0, size + 1 );

    int bytesRead = 0;
    int bytesLeft = size;
    int n;

    while(bytesLeft > 0)
    {
        n = read(socket, buffer + bytesRead, bytesLeft);

        if(n == -1)
            error_and_die("error reading n bytes from socket in readNBytesFromSocket");

        if(n == 0)
            return "quit";
        
        bytesRead += n;
        bytesLeft -= n;
    }
    buffer[size] = '\0';

    return std::string(buffer);
}

void sendNBytes(int socket, const std::string& payload, int size)
{
    int bytesSent = 0;
    int bytesLeft = payload.size();
    int n = 0;

    while(bytesLeft > 0)
    {
        n = write( socket, payload.data() + bytesSent, bytesLeft);
        if( n == -1)
            error_and_die("error sending message in sendNBytes()");

        bytesSent += n;
        bytesLeft -= n;
    }
}