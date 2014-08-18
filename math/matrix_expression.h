/**
 * @file matrix_expression.h
 */
 
#ifndef GENECIS_MATH_MATRIX_EXPRESSION_H
#define GENECIS_MATH_MATRIX_EXPRESSION_H

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstring>

namespace genecis {
namespace math {

	using namespace std ;
	 
	template<template<typename> class E, typename T>
	class matrix_expression {
		public:
			size_t rows() const {
				return static_cast<E<T> const&> (*this).rows() ;
			}
			size_t cols() const {
				return static_cast<E<T> const&> (*this).cols() ;
			}
			T det() {
				return static_cast<E<T> &> (*this).det() ;
			}
			bool singular() const {
				return static_cast<E<T> const&> (*this).singular() ;
			}
			bool verify() const {
				return static_cast<E<T> const&> (*this).verify() ;
			}
			T* data() const {
				return static_cast<E<T> const&> (*this).data() ;
			}
			T operator() (size_t i, size_t j) const {
				return static_cast<E<T> const&> (*this)(i,j) ;
			}
			operator E<T>& () {
				return static_cast<E<T>&> (*this) ;
			}
			operator E<T> const&() const {
				return static_cast<const E<T>&> (*this) ;
			}

	};

}	// end of namespace math
}	// end of namespace genecis

#endif
