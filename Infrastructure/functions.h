#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 
#include <string>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <algorithm>


#define BUFFERSIZE 1024

// functions that are used across all classes

void error_and_die(const std::string&); // for error handling
std::string readLine(std::string&);    // reading a line from a string, modify the original string
std::string readLineFromSocket(int);   // read one line from a given socket, needed to parse the content-length header
std::string readNBytesFromSocket(int,int);  // read exactly n bytes from a socket
std::string lower(std::string);  // UPPERCASE to lowercase
int sendNBytes(int,const std::string&,int);  // send exactly n bytes to a socket
void exitProgram(int);  // signals route to a normal exit
std::time_t getCurrentTime();  // I'll let you figure this one out

struct Session {
   std::string username;
};

#endif