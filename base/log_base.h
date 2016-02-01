/**
 * @file log_base.h
 * Logger class to help with debugging. The user can specify
 * whether to save the debug output to console or file.
 */
#pragma once

#include <genecis/base/genecis_defines.h>
#include <fstream>
#include <iostream>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

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

END_NAMESPACE
END_NAMESPACE
