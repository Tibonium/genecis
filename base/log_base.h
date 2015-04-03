/**
 * @file log_base.h
 * Logger class to help with debugging. The user can specify
 * whether to save the debug output to console or file.
 */
#include <fstream>
#include <iostream>

namespace genecis {
namespace base {

class log_base {

public:

    /**
     * Constructor
     */
    log_base() : __file__(NULL) {}

    /**
     * Public access to the debug file used by all classes
     */
    static char* __file__;
};

}
}
