#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 
#include <string>


#define BUFFERSIZE 1024


void error_and_die(const std::string&);
std::string readLine(std::string&);
std::string readLineFromSocket(int);
std::string readNBytesFromSocket(int,int);
void sendNBytes(int,const std::string&,int);


#endif