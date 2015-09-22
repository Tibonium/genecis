/**
 * @file container_io.h
 */
#pragma once

#include <iostream>
#include <iosfwd>
#include <sstream>
#include <typeinfo>
#include <genecis/container/container_expression.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(container)

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
		if( i!=(size-1) ) s << "," ;
	}
	s << "}" ;
	os << s.str().c_str() ;
	return os ;
}

END_NAMESPACE
END_NAMESPACE
