#include "messageRepositoryException.h"

MessageRepositoryException::MessageRepositoryException(std::string errorMessage)
    : ExceptionBase(errorMessage)
{
}
        
MessageRepositoryException::~MessageRepositoryException()
{
}