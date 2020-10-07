
#ifndef MESSAGEREPOSITORY
#define MESSAGEREPOSITORY

#include <mutex>

#include "../Infrastructure/message.h"
#include "../Infrastructure/fileSystem.class.h"
#include "../Infrastructure/functions.h"
#include "idGenerator.h"
#include "messageRepositoryException.h"
#include <algorithm>

class MessageRepository{
    public:
        MessageRepository(const FileSystem& fileManager);
        MessageRepository() = delete;
        ~MessageRepository();

        void Establish();

        void Insert(const Message& message);
        std::vector< std::string > GetMessages(const std::string& username);
        std::string GetMessage(const std::string& username, int index);
    private:

        const FileSystem& fileManager;
        IDGenerator* idGenerator;

        std::string name = "MessageDatabase";
        std::string databaseFolder;

        std::mutex fileAccessMutex;
};

#endif
