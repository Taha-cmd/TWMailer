#include "exceptionBase.h"

ExceptionBase::ExceptionBase(std::string errorMessage)
    : errorMessage(errorMessage)
{
}

ExceptionBase::~ExceptionBase()
{
}

const char* ExceptionBase::what() const throw()
{
    return errorMessage.c_str();
}