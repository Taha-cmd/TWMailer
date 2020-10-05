#include "exceptionBase.h"

class ConfigReaderException : public ExceptionBase{
    public:
        ConfigReaderException(std::string errorMessage);
        ~ConfigReaderException();
};