
#ifndef CONFIGREADEREXCEPTION
#define CONFIGREADEREXCEPTION

#include "../Infrastructure/exceptionBase.h"

class ConfigReaderException : public ExceptionBase{
    public:
        ConfigReaderException(std::string errorMessage);
        ~ConfigReaderException();
};

#endif
