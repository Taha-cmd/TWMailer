
#ifndef MESSAGEREPOSITORY
#define MESSAGEREPOSITORY

#include <mutex>

#include "../Infrastructure/message.h"
#include "../ServerDependencies/fileSystem.class.h"
#include "../Infrastructure/functions.h"
#include "idGenerator.h"
#include "messageRepositoryException.h"
#include <algorithm>


// the database of the project
// only this class can access the files stored in the mail pool
// each access is secured with a mutex

class MessageRepository{
    public:
        MessageRepository(const FileSystem& fileManager);
        MessageRepository() = delete;
        ~MessageRepository();

        void Establish();

        void Insert(const Message& message);
        std::vector< Message > GetMessages(const std::string& username);
        Message GetMessage(const std::string& username, int index);
        void DeleteMessage(const std::string& username, int index);
    private:

        FileSystem fileManager;
        IDGenerator* idGenerator;

        std::string name = "MessageDatabase";
        std::string databaseFolder;

        std::mutex fileAccessMutex;
};

#endif
