/**
 * @file container_io.h
 */
 
#ifndef GENECIS_MATH_CONTAINER_IO_H
#define GENECIS_MATH_CONTAINER_IO_H

#include <iostream>
#include <iosfwd>
#include <sstream>
#include <typeinfo>
#include "container_expression.h"

namespace genecis {
namespace container {

template<class E>
std::ostream& operator<< (std::ostream& os, container_expression<E>& c)
{
	typedef E							expression_type ;
	typedef typename E::value_type		value_type ;
	typedef typename E::size_type		size_type ;	

	expression_type e = c() ;
	size_type size = e.size() ;
    std::stringstream s ;	
	s << "[" << size << "]: {" ;
	for(size_t i=0; i<size; ++i) {
		s << e (i) ;
		(i!=(size-1)) ? s << "," :
			s << "}" ;
	}
	os << s.str().c_str() ;
	return os ;
}

}	// end of namespace container
}	// end of namespace genecis

#endif
