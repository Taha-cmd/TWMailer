#include "LdapClient.h"
#include <ldap.h>

#include <string.h>
#include <iostream>


LdapClient::LdapClient(const std::string& URI, const std::string& searchbase)
    :URI(URI), searchbase(searchbase), handle(nullptr), version(LDAP_VERSION3), connected(false)
{

}

LdapClient::~LdapClient()
{
    ldap_unbind_ext_s(handle , nullptr, nullptr);
}


void LdapClient::connect()
{
    int returnCodeInit = ldap_initialize(&handle, URI.data());   
    if(returnCodeInit != LDAP_SUCCESS)
        throw LdapClientException("Initialization of ldap client failed (" + std::to_string(returnCodeInit)  + ") : " + std::string(ldap_err2string(returnCodeInit)));

    int returnCodeOptions = ldap_set_option(handle, LDAP_OPT_PROTOCOL_VERSION, &version);
    if(returnCodeOptions != LDAP_OPT_SUCCESS)
        throw LdapClientException("Setting ldap version failed (" + std::to_string(returnCodeOptions) + ") : " + std::string(ldap_err2string(returnCodeOptions)));
        
    int returnCodeEncryption = ldap_start_tls_s(handle, nullptr, nullptr);
    if(returnCodeEncryption != LDAP_SUCCESS)
        throw LdapClientException("Starting secure connection failed (" + std::to_string(returnCodeEncryption) + ") : " + std::string(ldap_err2string(returnCodeEncryption)));

    connected = true;
}

bool LdapClient::authenticateUser(const std::string& username, const std::string& password)
{
    if(username.empty() || password.empty())
        throw LdapClientException("Error: username and password cannot be empty");

    if(username.length() > MAX_USERNAME_LENGTH)
        throw LdapClientException("Error: username length cannot exceed " + std::to_string(MAX_USERNAME_LENGTH));

    BerValue cred;
    cred.bv_val = (char*) password.data();
    cred.bv_len = password.length();

    std::string bindUsername = "uid=" + username + ",ou=people,dc=technikum-wien,dc=at";

    int returnCodeAuthentication = ldap_sasl_bind_s(handle, bindUsername.data(), LDAP_SASL_SIMPLE, &cred, nullptr, nullptr, nullptr);

    if(returnCodeAuthentication == LDAP_INVALID_CREDENTIALS)
        return false;

    if(returnCodeAuthentication != LDAP_SUCCESS)
        throw LdapClientException("User Authentication failed (" + std::to_string(returnCodeAuthentication) + ") : " + std::string(ldap_err2string(returnCodeAuthentication)));

    return true;
}

/*bool LdapClient::userExists(const std::string& username)
{
    // not possible to perform anonymous search outside of the fh's network

    if(!connected)
        throw LdapClientException("Error, not able to perform search without being connected");

    // search settings
    //std::string searchFilter = "(uid=" + username + ")";
    std::string searchFilter = "(uid=if17b*)";
    ber_int_t  searchScope = LDAP_SCOPE_SUBTREE;
    const char *ldapSearchResultAttributes[] = {"uid", "cn", nullptr};

    LDAPMessage* searchResult;

    int returnCodeSearch = ldap_search_ext_s(
                            handle,
                            searchbase.data(),
                            searchScope,
                            searchFilter.data(),
                            (char **)ldapSearchResultAttributes,
                            0,
                            nullptr,
                            nullptr,
                            nullptr,
                            500,
                            &searchResult
                            );

    if(returnCodeSearch != LDAP_SUCCESS)
        throw LdapClientException("Error performing search (" + std::to_string(returnCodeSearch) + ") : " + std::string(ldap_err2string(returnCodeSearch)));    

    return ldap_count_entries(handle, searchResult) == 1;

} */

