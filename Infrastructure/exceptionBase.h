
#ifndef EXCEPTIONBASE
#define EXCEPTIONBASE

#include <exception>
#include <string>

class ExceptionBase : public std::exception {
    public:
        std::string GetErrorMessage() const {return errorMessage;};

        ExceptionBase(std::string errorMessage);
        ~ExceptionBase();

        virtual const char* what() const throw();

    private:
        std::string errorMessage;
};

#endif
