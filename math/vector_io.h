/**
 * @file vector_io.h
 */
 
#ifndef GENECIS_MATH_VECTOR_IO_H
#define GENECIS_MATH_VECTOR_IO_H

#include <iostream>
#include <sstream>
#include <genecis/math/vector_expression.h>

namespace genecis {
namespace math {

	template<typename T> class svector ;

	template<typename T>
	std::ostream& operator<< (std::ostream& os, 
		vector_expression<svector, T>& v)
	{

		std::stringstream s ;
		s << "(rho,theta,phi): ["
		   << v.u1() << ", "
		   << v.u2() << ", "
		   << v.u3() << "]" ;
		os << s.str().c_str() ;
		return os ;
	}

	template<typename T> class bvector ;

	template<typename T>
	std::ostream& operator<< (std::ostream& os, 
		vector_expression<bvector, T>& v)
	{

		std::stringstream s ;
		s << "(x,y,z): ["
		   << v.u1() << ", "
		   << v.u2() << ", "
		   << v.u3() << "]" ;
		os << s.str().c_str() ;
		return os ;
	}

	template<typename T> class cvector ;

	template<typename T>
	std::ostream& operator<< (std::ostream& os, 
		vector_expression<cvector, T>& v)
	{

		std::stringstream s ;
		s << "(rho,phi,z): ["
		   << v.u1() << ", "
		   << v.u2() << ", "
		   << v.u3() << "]" ;
		os << s.str().c_str() ;
		return os ;
	}

}	// end of namespace math
}	// end of namespace genecis
#endif
