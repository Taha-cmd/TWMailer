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

    std::string recipientFolder = fileManager.joinPaths({databaseFolder, recipient});
    std::cout << "Looking for Recipientfolder: " << recipientFolder << std::endl;

    if(!fileManager.Exists(recipientFolder))
        fileManager.createDir(recipientFolder);
    
    if(!fileManager.isDir(recipientFolder))
        throw MessageRepositoryException("Error Inserting Message for Recipient: " + recipient + " File exists but it is not a Folder.");

    int messageId = idGenerator->NextID();
    std::string messageFilePath = fileManager.joinPaths( {databaseFolder, recipient, std::to_string(messageId) + ".txt"} );

    if(fileManager.Exists(messageFilePath))
        throw MessageRepositoryException("Error inserting Message ID: " + std::to_string(messageId) + ". File already exists");
    
    std::cout << "Creating MessageEntry: " << messageFilePath << std::endl;
    fileManager.writeToFile(messageFilePath, message.ToString());
}

std::vector< Message > MessageRepository::GetMessages(const std::string& username)
{
    std::lock_guard<std::mutex> guard(this->fileAccessMutex);
    std::vector< Message > messages;

    if( fileManager.Exists( fileManager.joinPaths( {databaseFolder, username} ) ) )
    {
        auto files = fileManager.getFiles( fileManager.joinPaths( {databaseFolder, username} ),  true );        
        messages.reserve( files.size() );

        for(const auto& path : files)
        {
            std::string text = fileManager.readFile( fileManager.joinPaths( {databaseFolder, username, path} ) );
            messages.emplace_back( text );
        }
            
    }

    return messages;
}

Message MessageRepository::GetMessage(const std::string& username, int index)
{
    std::lock_guard<std::mutex> guard(this->fileAccessMutex);
    
    if(!fileManager.Exists( fileManager.joinPaths( {databaseFolder, username} ) ))
        throw MessageRepositoryException("user hast no mailbox");

    auto files = fileManager.getFiles( fileManager.joinPaths( {databaseFolder, username} ), true );

    try 
    {
        std::string text = fileManager.readFile( fileManager.joinPaths( {databaseFolder, username, files.at(index)} ) );
        return Message( text );
    } 
    catch(...)
    {
        throw MessageRepositoryException("message does not exist");
    }

}

void MessageRepository::DeleteMessage(const std::string& username, int index)
{
    std::lock_guard<std::mutex> guard(this->fileAccessMutex);

    if(!fileManager.Exists( fileManager.joinPaths( {databaseFolder, username} ) ))
        throw MessageRepositoryException("user hast no mailbox");

    auto files = fileManager.getFiles( fileManager.joinPaths( {databaseFolder, username} ), true );

    try {
        fileManager.deleteFile( fileManager.joinPaths( {databaseFolder, username, files.at(index)} ) );
    } catch(...) {
        throw MessageRepositoryException("file not found for removal");
    } 
}