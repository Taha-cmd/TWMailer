
#ifndef IDGENERATOR
#define IDGENERATOR

#include <mutex>
#include <stdexcept>
#include <string>

#include "idGeneratorException.h"
#include "../Infrastructure/fileSystem.class.h"

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
