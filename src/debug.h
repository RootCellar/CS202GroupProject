#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

using std::string;
using std::to_string;

//This line defines DEBUG, a preprocessor variable
//Commenting this line out will disable debug printing
#define DEBUG

//If debug mode is enabled (DEBUG defined), print the debug message.
//Prototype
void debug(const char* s);

#endif
