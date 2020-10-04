#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class FileSystem {

    public:
        FileSystem(std::string);
        ~FileSystem();

        static bool pathExists(std::string);
        static bool isDir(std::string);

        bool isFile(std::string);
        bool deleteFile(std::string);
        bool deleteDir(std::string, bool);
        std::string createDir(std::string);
        std::string createFile(std::string);
        void writeToFile(std::string);
        std::string readFile(std::string);
        std::vector<std::string> getFiles(std::string);


    private:
        std::string root;

};
 