/**
 * @file math_functions.h
 */
 
#ifndef GENECIS_MATH_MATH_FUNCTIONS_H
#define GENECIS_MATH_MATH_FUNCTIONS_H

#include "../container/array.h"

namespace genecis {
namespace math {

class array ;

class math_functions {

	friend class array ;

	private:
	
		template <typename _T>
		static void convolve(_T& _u, _T& _v, _T& result) ;

};

}	// end namespace math
}	// end namespace genecis

#endif
