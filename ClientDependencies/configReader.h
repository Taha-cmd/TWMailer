
#ifndef CONFIGREADER
#define CONFIGREADER

#include <iostream>
#include <limits>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string>

#include "configReaderException.h"


// this class reads parameters from the console with constraints on length and validates the input

class ConfigReader{
    public:
        ConfigReader(std::istream& inputStream);
        ConfigReader() = delete;
        ~ConfigReader();

        void ReadLineParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength = std::numeric_limits<std::size_t>::max());
        void ReadTextParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength = std::numeric_limits<std::size_t>::max());
        void ReadPassword(std::string& target, const std::size_t maxLength = std::numeric_limits<std::size_t>::max());
    private:

        void PrintReadParameterInfo(const std::string& parameterName, const std::size_t maxLength);
        int getch();
        std::string getpass();

        std::istream& inputStream;
};

#endif
