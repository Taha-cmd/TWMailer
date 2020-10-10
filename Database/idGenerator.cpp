#include "idGenerator.h"

IDGenerator::IDGenerator(std::string name, std::string workingDirectory, const FileSystem& fileManager)
    : name(name), workingDirectory(workingDirectory), fileManager(fileManager)
{
    if(name.empty())
        throw std::invalid_argument("name cannot be empty.");
    
    this->fileName = name + ".keygen";
    this->keyGendFilePath = fileManager.joinPaths( {workingDirectory, fileName} );
}

IDGenerator::~IDGenerator()
{
}

void IDGenerator::Establish()
{
    std::cout << "Establishing Id Generator: " << name << std::endl;

    std::lock_guard<std::mutex> guard(this->fileAccessMutex);

    if(!fileManager.Exists(keyGendFilePath))
    {
        std::cout << "Id- Generatorfile does not exist. Creating File: " << keyGendFilePath << std::endl;
        fileManager.writeToFile(keyGendFilePath, "0");
    }
    else if(!fileManager.isFile(keyGendFilePath))
        throw IdGeneratorException("Invalid File- Format for Idgenerator- File: " + keyGendFilePath);

    std::cout << "Id- Generator: " << name << " established." << std::endl;
}

int IDGenerator::NextID()
{
    std::lock_guard<std::mutex> guard(this->fileAccessMutex);

    if(!fileManager.Exists(keyGendFilePath))
        throw IdGeneratorException("File: " + keyGendFilePath + " not found.");

    std::string currentIdText = fileManager.readFile(keyGendFilePath);
    std::cout << "NextID: " << std::stoi( currentIdText ) + 1 << " " << std::endl;
    
    int currentId = std::stoi(currentIdText);
    ++currentId;

    currentIdText = std::to_string(currentId);
    fileManager.writeToFile(keyGendFilePath, currentIdText);

    return currentId;
}