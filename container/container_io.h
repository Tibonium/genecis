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

template<template<typename> class T, typename E>
std::ostream& operator<< (std::ostream& os, container_expression<T, E>& c)
{
	typedef E		value_type ;
	typedef size_t	size_type ;	

    std::stringstream s ;	
	s << "[" << c.size() << "]: {" ;
	for(size_t i=0; i<c.size(); ++i) {
		s << c(i) ;
		(i!=(c.size()-1)) ? s << "," :
			s << "}" ;
	}
	os << s.str().c_str() ;
	return os ;
}

}	// end of namespace container
}	// end of namespace genecis

#endif
