#ifndef FILESYSTEM
#define FILESYSTEM

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ftw.h>

class FileSystem {

    public:

        FileSystem(std::string root);
        ~FileSystem();

        bool Exists(std::string path) const;
        bool isDir(std::string path) const;
        bool isFile(std::string path) const;

        int createDir(std::string) const;

        void deleteFile(std::string);
        
        void writeToFile(std::string path, std::string content) const;
        std::string readFile(std::string) const;
        std::vector<std::string> getFiles(const std::string&) const;

        std::string getRootFolder() const { return this->root; }

        std::string combineWithRoot(std::string) const;
    private:
        std::string root;
};

#endif
