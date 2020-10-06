
#ifndef IDGENERATOREXCEPTION
#define IDGENERATOREXCEPTION

#include "../Infrastructure/exceptionBase.h"

class IdGeneratorException : public ExceptionBase{
    public:
        IdGeneratorException(std::string errorMessage);
        ~IdGeneratorException();
};

#endif
