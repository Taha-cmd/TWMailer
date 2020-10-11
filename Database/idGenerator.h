
#ifndef IDGENERATOR
#define IDGENERATOR

#include <mutex>
#include <stdexcept>
#include <string>

#include "idGeneratorException.h"
#include "../ServerDependencies/fileSystem.class.h"


// creates the index file if not existing, protect it with a mutex when generating an id and incremeting the value


class IDGenerator{
    public:
        std::string GetName() const { return name; };
        std::string GetFileName() const { return fileName; };

        IDGenerator(std::string name, std::string workingDirectory, const FileSystem& fileManager);
        IDGenerator() = delete;
        ~IDGenerator();

        void Establish();
        int NextID();
    private:

        std::string name;
        std::string workingDirectory;
        std::string fileName;
        std::string keyGendFilePath;

        const FileSystem& fileManager;
        std::mutex fileAccessMutex;
};

#endif
