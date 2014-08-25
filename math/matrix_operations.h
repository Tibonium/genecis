/**
 * @file matrix_operations.h
 */
 
#ifndef GENECIS_MATH_MATRIX_OPERATIONS_H
#define GENECIS_MATH_MATRIX_OPERATIONS_H

#include <genecis/math/matrix_expression.h>

namespace genecis {
namespace math {

	/**
	 * Calculates the determinant of the matrix using Laplace's formula
	 * and the cofactor matricies. 
	 */
	template<class M>
	typename M::value_type determinant( matrix_expression<M>& m ) {
		typedef typename M::value_type	value_type ;
		typedef typename M::size_type	size_type ;
		
		value_type result = 1 ;
		size_type rows = m().rows() ;
		if( !m().diagonal() ) {
			M upper( m() ) ;
			M lower( m() ) ;
			lu_factorize( upper, lower, m ) ;
			for(size_type i=0; i<rows; ++i) {
				result *= upper(i,i) ;
			}
		} else {
			for(size_type i=0; i<rows; ++i) {
				result *= m()(i,i) ;
			}
		}
		return result ;
	}

	/**
	 * Checks for a zero row within the matrix
	 */
	template<class C, class __Size>
	bool check_zero_row( const C& data, __Size rows, __Size cols ) {
		typedef typename C::value_type		value_type ;
		typedef typename C::size_type		size_type ;

		bool zero = false ;
		for(size_type i=0; i<rows; ++i) {
			if( data(i*cols) == 0 ) {
				for(size_type j=1; j<cols; ++j) {
					if( data(i*cols+j) != 0 ) {
						zero = false ;
						break ;
					} else {
						zero = true ;
					}
				}
			}
		}
		return zero ;
	}

	/**
	 * Checks for a zero column within the matrix
	 */
	template<class C, typename __Size>
	bool check_zero_column( const C& data, __Size rows, __Size cols ) {
		typedef typename C::value_type		value_type ;
		typedef typename C::size_type		size_type ;
	
		bool zero = false ;
		for(size_type i=0; i<cols; ++i) {
			if( data(i) == 0 ) {
				for(size_type j=1; j<rows; ++j) {
					if( data(j*cols+i) != 0 ) {
						zero = false ;
						break ;
					} else {
						zero = true ;
					}
				}
			}
		}
		return zero ;
	}

	/**
	 * Decomposes a matrix into its upper and lower triangular
	 * matricies.
	 */
	template<class M>
	void lu_factorize( matrix_expression<M>& upper,
					   matrix_expression<M>& lower,
					   const matrix_expression<M>& origin )
	{
		typedef M expression_type ;
		typedef typename M::value_type		value_type ;
		typedef typename M::size_type		size_type ;
		
		size_type rows = origin().rows() ;
		size_type cols = origin().cols() ;

		upper().resize(rows, cols) ;
		lower().resize(rows, cols) ;
		for(size_type i=0; i<rows; ++i) {
			for(size_type j=0; j<cols; ++j) {
				if( i == 0 ) upper()(i,j) = origin()(i,j) ;
				if( i == j ) lower()(i,j)= 1 ;
				if( (i != 0) && (j == 0) ) {
					lower()(i,0) = origin()(i,0) / upper()(0,0) ;
				}
				if( (j >= i) && (i != 0) ) {
					value_type temp = 0 ;
					for(size_type k=0; k<=i-1; ++k) {
						temp += lower()(i,k) * upper()(k,j) ;
					}
					upper()(i,j) = origin()(i,j) - temp ;
				}
				if( (j < i) && (j != 0) ) {
					value_type temp = 0 ;
					for(size_type k=0; k<=j-1; ++k) {
						temp += lower()(i,k) * upper()(k,j) ;
					}
					lower()(i,j) = (origin()(i,j) - temp) / upper()(j,j) ;
				}
			}
		}
		upper().diagonal(true) ;
		lower().diagonal(true) ;
	}

}	// end of namespace math
}	// end of namespace genecis

#endif
