#include "configReaderException.h"

ConfigReaderException::ConfigReaderException(std::string errorMessage)
    : ExceptionBase(errorMessage)
{
}

ConfigReaderException::~ConfigReaderException()
{
}
