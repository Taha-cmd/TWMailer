#include "idGeneratorException.h"

IdGeneratorException::IdGeneratorException(std::string errorMessage)
    : ExceptionBase(errorMessage)
{
}

IdGeneratorException::~IdGeneratorException()
{
}