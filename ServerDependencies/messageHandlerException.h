
#ifndef MESSAGEHANDLEREXCEPTION
#define MESSAGEHANDLEREXCEPTION

#include<string>

#include "../Infrastructure/exceptionBase.h"

class MessageHandlerException : public ExceptionBase
{
    public:
        MessageHandlerException(std::string errorMessage);
        ~MessageHandlerException();
};

#endif