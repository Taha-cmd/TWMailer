#include "fileSystem.class.h"



FileSystem::FileSystem(std::string root): root(root)
{

}

FileSystem::~FileSystem()
{
    
}

bool FileSystem::isDir(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);

    struct stat attributes;
    stat(path.data(), &attributes);
    return static_cast<bool>(S_ISDIR(attributes.st_mode));
}

bool FileSystem::isFile(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);

    struct stat attributes;
    stat(path.data(), &attributes);
    return static_cast<bool>(S_ISREG(attributes.st_mode));
}

void FileSystem::deleteFile(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);
    remove(path.data());
}

std::string FileSystem::createDir(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);
    mkdir(path.data(), 0777);

    return path;
}

void FileSystem::writeToFile(std::string path, std::string content)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);
    std::ofstream newFile(path);
    newFile << content;
    newFile.close();
}

std::string FileSystem::readFile(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);
    std::string content;
    std::string line;
    std::ifstream targetFile(path);

    if(targetFile.is_open())
    {
        while(!targetFile.eof())
        {
            std::getline(targetFile, line);
            content.append(line).append("\n");
        }
    }

    return content;
}

std::vector< std::string > FileSystem::getFiles(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);

    struct dirent* entry;
    DIR* dir = opendir(path.data());
    std::vector<std::string> files;

    if(dir)
    {
        while( (entry = readdir(dir)) != NULL)
        {
            if(entry->d_type == DT_REG)
            {
                files.emplace_back( entry->d_name );
            }
        }
    }

    closedir(dir);
    return files;
}
