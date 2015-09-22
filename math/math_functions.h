/**
 * @file math_functions.h
 */
#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <genecis/container/array.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(math)

/**
 * Convolution
 */
template <typename T>
static void convolve(T& u, T& v, T& result)
{
	for(size_t i=0; i<u.size(); ++i) {
		for(size_t j=0; j<v.size(); ++j) {
			result(i) += u(i) * v(j) ;
		}
	}
}

/**
 * Factorial
 */
static double factorial(std::size_t i)
{
	double result = 1 ;
	if( i == 0 ) {
		return result ;
	} else
	if( 100 < i ) {
		for(std::size_t j=2; j<=i; ++j) {
			result *= j ;
		}
	} else {
		result = std::sqrt(2.0*M_PI*i) ;
		double tmp = i / std::exp(1) ;
		result *= std::pow( tmp, i ) ;
		result *= std::exp( 1.0/(12*i) - 1.0/(360*i*i*i) ) ;
	}
	return result ;
}

/**
 * N choose K
 */
static double choose(std::size_t n, std::size_t k)
{
	double tmp = 1 ;
	for(std::size_t i=(n-k)+1; i<=n; ++i) {
		tmp *= i ;
	}
	tmp /= factorial(k) ;
	return tmp ;
}

END_NAMESPACE
END_NAMESPACE
