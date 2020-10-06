
#ifndef CONFIGREADER
#define CONFIGREADER

#include <iostream>
#include <limits>
#include <stdexcept>

#include "configReaderException.h"

class ConfigReader{
    public:
        ConfigReader(std::istream& inputStream);
        ~ConfigReader();

        void ReadLineParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength = std::numeric_limits<std::size_t>::max());
        void ReadTextParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength = std::numeric_limits<std::size_t>::max());
    private:

        void PrintReadParameterInfo(const std::string& parameterName, const std::size_t maxLength);

        std::istream& inputStream;
};

#endif
