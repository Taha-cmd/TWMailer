#include "fileSystem.class.h"



FileSystem::FileSystem(std::string root): root(root)
{

    if(!this->Exists(root))
        this->createDir(root);
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

std::vector< std::string > FileSystem::getFiles(const std::string& path, bool sorted = false) const
{

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

    if(sorted)
    {
        std::sort(files.begin(), files.end(), [](const std::string& p1, const std::string& p2){
            return std::stoi( p1 ) < std::stoi( p2 );
        });
    }
 

    closedir(dir);
    return files;
}

std::string FileSystem::combineWithRoot(std::string path) const
{
    return root + "/" + path;
}

std::string FileSystem::joinPaths(const std::vector< std::string >& paths) const
{
    std::string path = paths.at(0);

    for(std::size_t i = 1; i < paths.size(); i++)
        path.append( "/" + paths.at(i) );

    return path;
}