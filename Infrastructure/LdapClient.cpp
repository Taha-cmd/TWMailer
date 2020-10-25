#include "LdapClient.h"
#include <ldap.h>

#include <string.h>
#include <iostream>


LdapClient::LdapClient(const std::string& URI, const std::string& searchbase)
    :URI(URI), searchbase(searchbase), handle(nullptr), version(LDAP_VERSION3)
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
}

void LdapClient::test()
{

  const char* BIND_USER = "";
  char* BIND_PW = "";
  BerValue cred;

  cred.bv_val = BIND_PW;
  cred.bv_len = strlen(BIND_PW);

  BerValue* servercredp;

  int rc = ldap_sasl_bind_s(handle,BIND_USER,LDAP_SASL_SIMPLE,&cred,NULL,NULL,&servercredp);

  std::cout << ldap_err2string(rc) << std::endl;


}

