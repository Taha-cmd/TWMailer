#include "ConnectedClient.h"


ConnectedClient::ConnectedClient(int socket, std::string IP)
    :socket(socket), IP(IP), loggedIn(false)
{

}


ConnectedClient::~ConnectedClient()
{

}

void ConnectedClient::closeConnection()
{
    close(socket);
}