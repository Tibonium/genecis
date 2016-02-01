/**
 * @file goal.h
 */
#pragma once

#include <genecis/base/genecis_stringlist.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(ai)

USING_NAMESPACE(base)

class goal {
public:

	typedef goal			self_type ;
	typedef genecis_string	string_type ;

	// Constructor
	goal(const string_type name) : _goal_name(name) {}

	friend std::ostream& operator<< (std::ostream& os, const self_type& other) ;

private:
	
	string_type _goal_name ;
	
};

inline std::ostream& operator<< (std::ostream& os, const goal& other) {
	os << other._goal_name ;
	return os ;
}

END_NAMESPACE
END_NAMESPACE
