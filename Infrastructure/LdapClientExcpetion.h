
#ifndef LDAPEXCEPTION
#define LDAPEXCEPTION

#include "exceptionBase.h"



class LdapClientException : public ExceptionBase 
{

    public:
        LdapClientException(std::string message);

};


#endif