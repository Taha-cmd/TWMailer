
#ifndef MESSAGEREPOSITORY
#define MESSAGEREPOSITORY

#include <mutex>

#include "../message.h"
#include "../Infrastructure/fileSystem.class.h"
#include "idGenerator.h"
#include "messageRepositoryException.h"

class MessageRepository{
    public:
        MessageRepository(const FileSystem& fileManager);
        MessageRepository() = delete;
        ~MessageRepository();

        void Establish();

        void Insert(const Message& message);
        std::vector< std::string > GetMessages(const std::string& username);
    private:

        const FileSystem& fileManager;
        IDGenerator* idGenerator;

        std::string name = "MessageDatabase";
        std::string databaseFolder;

        std::mutex fileAccessMutex;
};

#endif
