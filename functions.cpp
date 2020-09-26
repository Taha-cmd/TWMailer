#include <iostream>

void error_and_die(const std::string& errorMsg)
{
    std::cerr << errorMsg << std::endl;
    exit(EXIT_FAILURE);
}