#ifndef LDAPCLIENT
#define LDAPCLIENT


#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <ldap.h>

#include "LdapClientExcpetion.h"



#define FH_LDAP_URI "ldap://ldap.technikum.wien.at:389"
#define FH_LDAP_SEARCHBASE "dc=technikum-wien,dc=at"


class LdapClient
{

    public:
        LdapClient(const std::string& URI, const std::string& searchbase);
        ~LdapClient();
        
        void connect();

        int getVersion() const { return version; }

        void test();


    private:
        std::string URI;
        std::string searchbase;

        LDAP* handle;
        const int version;


};


#endif