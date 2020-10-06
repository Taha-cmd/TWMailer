
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
        ~MessageRepository();

        void Establish();

        void Insert(const Message& message);
    private:

        const FileSystem& fileManager;
        IDGenerator* idGenerator;

        std::string name = "MessageDatabase";
        std::string databaseFolder;

        std::mutex fileAccessMutex;
};

#endif
