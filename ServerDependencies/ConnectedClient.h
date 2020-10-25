#ifndef CONNECTEDCLIENT
#define CONNECTEDCLIENT


#include <string>
#include <unistd.h>

class ConnectedClient
{

    public:
        ConnectedClient(int socket, std::string IP);
        ~ConnectedClient();

        int getSocket() const { return socket; }
        std::string getIP() const { return IP; }
        bool isLoggedIn() const { return loggedIn; }

        void startSession() { loggedIn = true; }
        void closeConnection();

    private:
        int socket;
        std::string IP;
        bool loggedIn;
};


#endif