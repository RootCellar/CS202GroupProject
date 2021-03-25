#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

//This line defines DEBUG, a preprocessor variable
//Commenting this line out will disable debug printing
#define DEBUG true

//If debug mode is enabled (DEBUG defined), print the debug message.
void debug(const char* s) {
    #ifdef DEBUG
    std::cout << "[DEBUG] " << s << std::endl;
    #endif
}

#endif
