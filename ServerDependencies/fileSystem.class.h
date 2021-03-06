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
#include <algorithm>


// this class works with the filesystem and wraps the ugly c functions with more understandable and compact method names
// similar to filesystem namespace in c++17


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
        std::string joinPaths(const std::vector< std::string >&) const;
        std::vector<std::string> getFiles(const std::string&, bool) const;

        std::string getRootFolder() const { return this->root; }

        std::string combineWithRoot(std::string) const;
    private:
        std::string root;
};

#endif
