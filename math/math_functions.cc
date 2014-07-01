/**
 * @file @math_functions.cc
 */

#include "math_functions.h"

using namespace genecis::math ;

template <typename _T>
void math_functions::convolve(
	_T& _u, _T& _v, _T& result)
{
	for(int i=0; i<_u.size(); ++i) {
		for(int j=0; j<_v.size(); ++j) {
			result(i) += _u(i) * _v(j) ;
		}
	}
}
