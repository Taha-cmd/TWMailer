#ifndef LDAPCLIENT
#define LDAPCLIENT


#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <ldap.h>

#include "LdapClientExcpetion.h"



#define FH_LDAP_URI "ldap://ldap.technikum-wien.at:389"
#define FH_LDAP_SEARCHBASE "dc=technikum-wien,dc=at"


class LdapClient
{

    public:
        LdapClient(const std::string& URI, const std::string& searchbase);
        ~LdapClient();
        
        void connect();
        //bool userExists(const std::string& username);
        bool authenticateUser(const std::string& username, const std::string& password);

        int getVersion() const { return version; }
        bool isConnected() const { return connected; }

    private:
        std::string URI;
        std::string searchbase;

        LDAP* handle;
        const int version;

        bool connected;


};


#endif