
#ifndef CONFIGREADEREXCEPTION
#define CONFIGREADEREXCEPTION

#include "exceptionBase.h"

class ConfigReaderException : public ExceptionBase{
    public:
        ConfigReaderException(std::string errorMessage);
        ~ConfigReaderException();
};

#endif
