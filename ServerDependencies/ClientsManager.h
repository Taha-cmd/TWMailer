#ifndef CLIENTSMANAGER
#define CLIENTSMANAGER


#include <map>
#include <string>
#include <chrono>
#include "../Infrastructure/functions.h"

#define MAX_FAILED_ATTEMPTS 3
#define BLOCK_PERIOD_SECONDS 30


struct ClientStats
{
    ClientStats(int attempts = 0)
        :failedAttempts(attempts) {}
    
    int failedAttempts;
    std::chrono::_V2::system_clock::time_point blockedTimeBegin;
};

class ClientsManager
{

    public:
        ClientsManager(/* args */);
        ~ClientsManager();


        void addClient(const std::string& IP);
        bool isBlocked(const std::string& IP);
        bool exists(const std::string& IP);
        void increaseFailedAttempts(const std::string& IP);
        void resetFailedAttempts(const std::string& IP);
        int getRemainingAttempts(const std::string& IP);
        int getRemainingBlockTime(const std::string& IP);


    private:
        std::map<std::string, ClientStats> clients;

};





#endif