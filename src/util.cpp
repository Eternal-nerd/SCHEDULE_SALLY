#include "util.h"


/*-----------------------------------------------------------------------------
------------------------------LOGGIN-------------------------------------------
-----------------------------------------------------------------------------*/
void util::log(const std::string& src, const std::string& msg) {
    // thread safe 
    std::stringstream output;
    output << "[" << src << "]: " << msg << "\n";
    std::cout << output.str();
}