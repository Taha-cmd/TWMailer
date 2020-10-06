
#ifndef MESSAGEREPOSITORYEXCEPTION
#define MESSAGEREPOSITORYEXCEPTION

#include "../Infrastructure/exceptionBase.h"

class MessageRepositoryException : public ExceptionBase{
    public:
        MessageRepositoryException(std::string);
        ~MessageRepositoryException();
};

#endif
