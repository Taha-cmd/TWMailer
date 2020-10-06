#include "messageRepository.h"

MessageRepository::MessageRepository(const FileSystem& fileManager)
    : fileManager(fileManager)
{
    this->databaseFolder = fileManager.combineWithRoot(name);
    this->idGenerator = new IDGenerator("RecipientIDGen", databaseFolder, fileManager);
}

MessageRepository::~MessageRepository()
{
    delete idGenerator;
}

void MessageRepository::Establish()
{
    std::cout << "Establishing Message- Database." << std::endl;

    std::lock_guard<std::mutex> guard(fileAccessMutex);

    if(!fileManager.Exists(databaseFolder))
    {
        std::cout << "Message Databasefolder: " << databaseFolder << " does not exist. Creating Folder." << std::endl;
        fileManager.createDir(databaseFolder);
    }
    else if(!fileManager.isDir(databaseFolder))
        throw MessageRepositoryException("Error Establishing MessageRepository: " + databaseFolder + " exists, but is not a Directory.");

    std::cout << "MessageRepository Established." << std::endl;
    idGenerator->Establish();
}

void MessageRepository::Insert(const Message& message)
{
    std::string recipient = message.GetRecipient();

    std::lock_guard<std::mutex> guard(this->fileAccessMutex);

    std::string recipientFolder = databaseFolder + "/" + recipient;
    std::cout << "Looking for Recipientfolder: " << recipientFolder << std::endl;

    if(!fileManager.Exists(recipientFolder))
        fileManager.createDir(recipientFolder);
    
    if(!fileManager.isDir(recipientFolder))
        throw MessageRepositoryException("Error Inserting Message for Recipient: " + recipient + " File exists but it is not a Folder.");

    int messageId = idGenerator->NextID();

    std::string messageFilePath = recipient + "/" + std::to_string(messageId) + "txt";

    if(!fileManager.Exists(messageFilePath))
        throw MessageRepositoryException("Error inserting Message ID: " + std::to_string(messageId) + ". File already exists");
    
    fileManager.writeToFile(messageFilePath, message.ToString());
}