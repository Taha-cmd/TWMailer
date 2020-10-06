#include "messageHandlerException.h"

MessageHandlerException::MessageHandlerException(std::string errorMessage)
    : ExceptionBase(errorMessage)
{
}

MessageHandlerException::~MessageHandlerException()
{
}
