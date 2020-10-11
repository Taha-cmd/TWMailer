#include "configReader.h"

ConfigReader::ConfigReader(std::istream& inputStream)
    : inputStream(inputStream)
{
}

ConfigReader::~ConfigReader()
{
}

void ConfigReader::ReadLineParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength)
{
    if(maxLength == 0)
        throw std::invalid_argument("maxLength must be larger than 0.");

    PrintReadParameterInfo(parameterName, maxLength);

    std::getline(this->inputStream, target);
    
    if(target.length() > maxLength)
        throw ConfigReaderException("Invalid Length of Parameter: " + parameterName);
}

void ConfigReader::ReadTextParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength)
{
    if(maxLength == 0)
        throw std::invalid_argument("maxLength must be larger than 0.");
    
    PrintReadParameterInfo(parameterName, maxLength);
    std::cout << "Type :wq to save." << std::endl;

    std::size_t index;
    std::string temp;
    
    while((index = temp.find(":wq")) == std::string::npos)
    {
        std::string line;
        std::getline(this->inputStream, line);
        temp += line + '\n';
    }

    temp.erase(index);

    if(temp.length() > maxLength)
        throw ConfigReaderException("Invalid Length of Parameter: " + parameterName);

    target = temp;
}

void ConfigReader::PrintReadParameterInfo(const std::string& parameterName, const std::size_t maxLength)
{
    if(maxLength == std::numeric_limits<std::size_t>::max())
        std::cout << "Enter " << parameterName <<  ": " << std::endl;
    else
        std::cout << "Enter " << parameterName << "(max characters: " << maxLength << ") : ";
}
