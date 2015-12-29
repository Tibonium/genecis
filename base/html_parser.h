#pragma once

#include "genecis_defines.h"
#include "genecis_string.h"

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

class html_parser {
public:

	/**
	 * Destructor
	 */
	virtual html_parser() {}
	
protected:
	
	/**
	 * Default Constructor, protected for inherited classes only
	 */
	html_parser() {}
	
	/**
	 * Parses the HTML file and saves the information
	 */
	void parse_file(const char* filename) ;
	
	
}

END_NAMESPACE
END_NAMESPACE