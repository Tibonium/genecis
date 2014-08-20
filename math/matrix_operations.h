/**
 * @file matrix_operations.h
 */
 
#ifndef GENECIS_MATH_MATRIX_OPERATIONS_H
#define GENECIS_MATH_MATRIX_OPERATIONS_H

namespace genecis {
namespace math {

	/**
	 * Calculates the determinant of the matrix using Laplace's formula
	 * and the cofactor matricies. 
	 */
	template<typename __Type, typename __Size>
	__Type determinant(__Type* data, __Size n) {
		typedef __Type	value_type ;
		typedef __Size	size_type ;
		
		value_type result = 0 ;
		value_type* temp = new value_type[n*n] ;
		if( n == 1 ) {
			delete[] temp ;
			return data[0] ;
		} else if( n == 2 ) {
			delete[] temp ;
			return (data[0]*data[3]-data[1]*data[2]) ;
		} else {
			for(size_type p=0; p<n; ++p) {
				size_type h = 0 ;
				size_type k = 0 ;
				for(size_type i=1; i<n; ++i) {
					for(size_type j=0; j<n; ++j) {
						if( j == p ) continue ;
						temp[h*n+k] = data[i*n+j] ;
						++k ;
						if( k == n ) { ++h ; k = 0 ;}
					}
				}
				result += data[0+p]*pow(-1,p)*determinant(temp, n-1) ;
			}
			delete[] temp ;
			return result ;
		}
	}

	/**
	 * Checks for a zero row within the matrix
	 */
	template<typename __Type, typename __Size>
	bool check_zero_row( __Type* data, __Size rows, __Size cols ) {
		typedef __Type		value_type ;
		typedef __Size		size_type ;
	
		bool zero = false ;
		for(size_type i=0; i<rows; ++i) {
			if( data[i*rows+0] == 0 ) {
				for(size_type j=1; j<cols; ++j) {
					if( data[i*rows+j] != 0 ) {
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
	template<typename __Type, typename __Size>
	bool check_zero_column( __Type* data, __Size rows, __Size cols ) {
		typedef __Type		value_type ;
		typedef __Size		size_type ;
	
		bool zero = false ;
		for(size_type i=0; i<cols; ++i) {
			if( data[i] == 0 ) {
				for(size_type j=1; j<rows; ++j) {
					if( data[j*rows+i] != 0 ) {
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
	template<class M, typename __Type, typename __Size>
	void lu_factorize( M& upper, M& lower,
			__Type* data, __Size& rows, __Size& cols )
	{
		typedef __Type		value_type ;
		typedef __Size		size_type ;

		upper.resize(rows, cols) ;
		lower.resize(rows, cols) ;
		for(size_type i=0; i<rows; ++i) {
			for(size_type j=0; j<cols; ++j) {
				if( i == 0 ) upper(i,j) = data[i*rows+j] ;
				if( i == j ) lower(i,j)= 1 ;
				if( (i != 0) && (j == 0) ) {
					lower(i,0) = data[i*rows] / upper(0,0) ;
				}
				if( (j >= i) && (i != 0) ) {
					value_type temp = 0 ;
					for(size_type k=0; k<=i-1; ++k) {
						temp += lower(i,k) * upper(k,j) ;
					}
					upper(i,j) = data[i*rows+j] - temp ;
				}
				if( (j < i) && (j != 0) ) {
					value_type temp = 0 ;
					for(size_type k=0; k<=j-1; ++k) {
						temp += lower(i,k) * upper(k,j) ;
					}
					lower(i,j) = (data[i*rows+j] - temp) / upper(j,j) ;
				}
			}
		}
	}

}	// end of namespace math
}	// end of namespace genecis
#endif
