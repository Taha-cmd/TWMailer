#include "ClientsManager.h"


ClientsManager::ClientsManager(/* args */)
{

}

ClientsManager::~ClientsManager()
{

}

void ClientsManager::addClient(const std::string& IP)
{
    if(!exists(IP))
        clients.emplace(IP, ClientStats());
}

bool ClientsManager::exists(const std::string& IP)
{
    return clients.find(IP) != clients.end(); 
}

bool ClientsManager::isBlocked(const std::string& IP)
{
    if(exists(IP))
    {
        //if blocked, check for time
        if(clients[IP].failedAttempts == MAX_FAILED_ATTEMPTS)
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now - clients[IP].blockedTimeBegin).count();

            if(seconds >= BLOCK_PERIOD_SECONDS)
            {
                resetFailedAttempts(IP);
                return false;
            }

            return true;
        } 
    }
        
    return false;
}

void ClientsManager::increaseFailedAttempts(const std::string& IP)
{
    if(!exists(IP)) return;

    clients[IP].failedAttempts++;

    if(clients[IP].failedAttempts == MAX_FAILED_ATTEMPTS)
        clients[IP].blockedTimeBegin =  std::chrono::high_resolution_clock::now();

}

void ClientsManager::resetFailedAttempts(const std::string& IP)
{
    if(!exists(IP)) return;

    clients[IP].failedAttempts = 0;    
}

int ClientsManager::getRemainingAttempts(const std::string& IP)
{
    if(!exists(IP)) return -1;

    return MAX_FAILED_ATTEMPTS - clients[IP].failedAttempts;
}

int ClientsManager::getRemainingBlockTime(const std::string& IP)
{
    if(!exists(IP)) return -1;

    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now - clients[IP].blockedTimeBegin).count();

    return BLOCK_PERIOD_SECONDS - seconds;

}