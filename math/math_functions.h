/**
 * @file math_functions.h
 */
 
#ifndef GENECIS_MATH_MATH_FUNCTIONS_H
#define GENECIS_MATH_MATH_FUNCTIONS_H

#include <genecis/container/array.h>

namespace genecis {
namespace math {

	class math_functions {

		public:
	
			template <typename T>
			static void convolve(T& u, T& v, T& result) {
				for(size_t i=0; i<u.size(); ++i) {
					for(size_t j=0; j<v.size(); ++j) {
						result(i) += u(i) * v(j) ;
					}
				}
			}

	};

}	// end namespace math
}	// end namespace genecis

#endif
