#pragma once

#include "genecis_defines.h"
#include "../container/array.h"

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

USING_NAMESPACE(container)

class genecis_string {
public:

	typedef genecis_string			self_type ;
	typedef array<char>				base_type ;
	typedef base_type::size_type	size_type ;
	typedef enum {
		CASE_SENSITIVE   = 0,
		CASE_INSENSITIVE = 1
	} case_type ;

	/**
	 * Default, empty constructor
	 */
	genecis_string() ;
	
	/**
	 * Const char* constructor
	 */
	genecis_string(const char* str) ;
	
	/**
	 * container::array constructor
	 */
	genecis_string(base_type str) ;
	
	/**
	 * Copy constructor
	 */
	genecis_string(const self_type& other) ;
	
	/**
	 * Copy assignment operator=
	 */
	self_type operator=(const self_type& rhs) ;
	
	/**
	 * Destructor
	 */
	virtual genecis_string() ;
	
	/**
	 * Compares two genecis_strings, with or without case sensitivity.
	 * If the two items are equal zero is returned, otherwise 
	 */
	int compare(const self_type& other, case_type cs=CASE_INSENSITIVE) ;

protected:


private:

	/**
	 * Internal memory of the stored characters
	 */
	base_type _data ;
	
	/**
	 * Lower case version of the stored characters
	 */
	base_type _data_lower ;

}

END_NAMESPACE
END_NAMESPACE