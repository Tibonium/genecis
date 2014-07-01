/**
 * @file math_functions.h
 */
 
#ifndef GENECIS_MATH_MATH_FUNCTIONS_H
#define GENECIS_MATH_MATH_FUNCTIONS_H

#include "../container/array.h"

namespace genecis {
namespace math {

class math_functions {

	public:
	
		template <typename _T>
		static void convolve(_T& _u, _T& _v, _T& result) {
			for(size_t i=0; i<_u.size(); ++i) {
				for(size_t j=0; j<_v.size(); ++j) {
					result(i) += _u(i) * _v(j) ;
				}
			}
		}

};

}	// end namespace math
}	// end namespace genecis

#endif
