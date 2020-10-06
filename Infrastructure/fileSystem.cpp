#include "fileSystem.class.h"



FileSystem::FileSystem(std::string root): root(root)
{

}

FileSystem::~FileSystem()
{
    
}

bool FileSystem::Exists(std::string path) const
{
    struct stat attr;
    return stat(path.data(), &attr) == 0;
}

bool FileSystem::isDir(std::string path) const
{
    struct stat attr;
    return stat(path.data(), &attr) == 0 && attr.st_mode & S_IFDIR;
}

bool FileSystem::isFile(std::string path) const
{
    struct stat attr;
    return stat(path.data(), &attr) == 0 && attr.st_mode & S_IFREG;
}

void FileSystem::deleteFile(std::string path)
{
    path = root + "/" + path;
    path = realpath(path.data(), NULL);
    remove(path.data());
}

int FileSystem::createDir(std::string path) const
{
    return mkdir(path.data(), 0777);
}

void FileSystem::writeToFile(std::string path, std::string content) const
{
    std::ofstream newFile(path);
    newFile << content;
    newFile.close();
}

std::string FileSystem::readFile(std::string path) const
{
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

std::string FileSystem::combineWithRoot(std::string path) const
{
    return root + "/" + path;
}
