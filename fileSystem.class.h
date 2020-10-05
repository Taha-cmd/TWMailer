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
        FileSystem(std::string);
        ~FileSystem();

        bool isDir(std::string);
        bool isFile(std::string);
        void deleteFile(std::string);
        std::string createDir(std::string);
        void writeToFile(std::string, std::string);
        std::string readFile(std::string);
        std::vector<std::string> getFiles(std::string);

        std::string getRootFolder() const { return this->root; }


    private:
        std::string root;
        

};
 