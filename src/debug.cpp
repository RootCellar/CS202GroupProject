#include "debug.h"

//If debug mode is enabled (DEBUG defined), print the debug message.
void debug(const char* s) {
    #ifdef DEBUG
    std::cout << "[DEBUG] " << s << std::endl;
    #endif
}
