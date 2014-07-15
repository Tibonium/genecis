/**
 * @file new matrix class
 */

#ifndef GENECIS_MATH_MATRIX_H
#define GENECIS_MATH_MATRIX_H

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <typeinfo>
#include "matrix_expression.h"

namespace genecis {
namespace math {

using namespace std ;

template<class T> class matrix ;

template<class T>
std::ostream& operator<< (std::ostream& os, matrix<T>& output) ;

template<class T> class matrix : public matrix_expression<matrix, T> {

		typedef matrix<T> self_type ;

	public:
/******************** Constructor/Destructors *********************/
		/**
		 * Main  Constructor
		 * Creates an NxM matrix from a basic array
		 * Defaults to a 1x1 matrix
		 */
		matrix(size_t rows=1, size_t cols=1) : 
			_rows(rows), _cols(cols),
			bSingular(false), bVerify(true)
		{
			size_t N = _rows * _cols ;
			pData = new T[N] ;
			memset(pData, 0, N * sizeof(T)) ;
		}

		/**
		 * Copy Constructor
		 */
		template<template <typename> class E>
		matrix(matrix_expression<E,T> const& r) {
			E<T> const& rhs = r ;
			_rows = rhs.rows() ;
			_cols = rhs.cols() ;
			bVerify = true ;
			bSingular = rhs.singular() ;
			size_t N = _rows * _cols ;
			pData = new T[N] ;
			for(size_t i=0; i<_rows; ++i) {
				for(size_t j=0; j<_cols; ++j) {
					pData[i*_cols+j] = rhs(i,j) ;
				}
			}
		}
		
		/**
		 * Destructor
		 */
		virtual ~matrix() {
			if(pData) {
				delete[] pData ;
				pData = NULL ;
			}
		}

		inline size_t rows() const {
			return _rows ;
		}

		inline size_t cols() const {
			return _cols ;
		}

		inline bool singular() const {
			return bSingular ;
		}
		
		inline T det() {
			if ( bVerify ) {
				singularity() ;
			}
			return m_det ;
		}
		
		inline bool verify() const {
			return bVerify ;
		}
		
		inline T* data() const {
			return pData ;
		}

/************************* Operators ******************************/
		/* Accessor and Assigner */
		inline T& operator() (size_t i, size_t j) const {
			return pData[ i * _cols + j ] ;
		}

		template<size_t _index>
		inline void operator= (T c) {
			bVerify = true ;
			pData[_index] = c ;
		}

	/*================= Matrix Scalar Operators ================*/
		inline void operator*= (T c) {
			for(size_t i=0; i<(_rows*_cols); ++i) {
				pData[i] *= c ;
			}
			m_det *= pow(c,_rows) ; ;
		}

		inline void operator/= (T c) {
			for(size_t i=0; i<(_rows*_cols); ++i) {
				pData[i] /= c ;
			}
			m_det /= pow(c,_rows) ; ;
		}

		inline void operator+= (T c) {
			for(size_t i=0; i<(_rows*_cols); ++i) {
				pData[i] += c ;
			}
			determinant() ;
		}

		inline void operator-= (T c) {
			for(size_t i=0; i<(_rows*_cols); ++i) {
				pData[i] -= c ;
			}
			determinant() ;
		}

		inline void operator%= (T c) {
			for(size_t i=0; i<(_rows*_cols); ++i) {
				pData[i] %= c ;
			}
			determinant() ;
		}

	/*================ Matrix Matrix Operators =================*/
		inline void operator*= (matrix& rhs) {
			try {
				if( _cols != rhs._rows ) {
					throw 1;
				} else {
					matrix<T> temp = *this ;
					*this = temp * rhs ;
					this->bVerify = true ;
					this->bSingular = false ;
				}
			} catch (int e) {
				cout << "matrix::operator*=: A cols(" << _cols
					 << ") must equal B rows(" << rhs._rows
					 << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline void operator+= (matrix& rhs) {
			try {
				if( _rows != rhs._rows || _cols != rhs._cols ) {
					throw 1 ;
				} else {
					matrix<T> temp = *this ;
					*this = temp + rhs ;
					bVerify = true ;
					bSingular = false ;
				}
			} catch (int e) {
				cout << "matrix::operator+=: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << rhs << endl ;
				exit(e) ;
			}
		}
		
		inline void operator-= (matrix& rhs) {
			try {
				if( _rows != rhs._rows || _cols != rhs._cols ) {
					throw 1 ;
				} else {
					matrix<T> temp = *this ;
					*this = temp - rhs ;
					bVerify = true ;
					bSingular = false ;
				}
			} catch (int e) {
				cout << "matrix::operator-=: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << rhs << endl ;
				exit(e) ;
			}
		}
		
		inline void operator/ (matrix& rhs) {
			cout << "matrix::operator/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		inline void operator/= (matrix& rhs) {
			cout << "matrix::operator=/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		/**
		 * Mutates the matrix into its transpose.
		 */
		inline void transpose() {
			matrix<T>* temp = new matrix<T>(_cols,_rows) ;
			for(size_t i=0; i<_rows; ++i) {
				for(size_t j=0; j<_cols; ++j) {
					temp->pData[j*_rows+i] = pData[i*_rows+j] ;
				}
			}
			*this = *temp ;
			delete temp ;
		}
		
		/**
		 * Mutates the passed in matrix into the transpose of the
		 * matrix that called this function. The calling matrix
		 * remains unaltered.
		 */
		inline void transpose(matrix& m_trans) {
			m_trans.resize(_cols, _rows) ;
			for(size_t i=0; i<_rows; ++i) {
				for(size_t j=0; j<_cols; ++j) {
					m_trans->pData[j*_rows+i] = pData[i*_rows+j] ;
				}
			}
		}
		
		/**
		 * Mutates the calling matrix into its inverse, if it exists.
		 * Otherwise an exit status is passed and the program ends.
		 */
		inline matrix* inverse() {
			try {
				singularity() ;
				if( bSingular || m_det == 0 ) {
					throw 1 ;
				} else {
					matrix<T>* inv_mtx = this ;
					cout << "something" << endl ;
					return inv_mtx ;
				}
			} catch (int e) {
				cout << "matrix::inverse(): inverse not defined for"
					 << " singular matrices at this time." << endl ;
				cout << "Non-singular matrices must be square and"
					 << " have a non-zero determinant." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		/**
		 * Exponent operator. When called on a matrix it will mutate
		 * the matrix it operates on into a new matrix equal to the
		 * original matrix times itself n times, where n is the
		 * exponent.
		 * For an exponent of zero, the matrix will take on the form
		 * of the identity matrix.
		 * For an exponent of -1, the matrix will become the original
		 * matrix's inverse.
		 *
		 * NOTE: At present only integer values for the exponent are
		 * accepted.
		 */
		inline void operator^ (int exp) {
			try {
				if( _cols != _rows ) {
					throw 1 ;
				} else {
					if( exp < 0 ) {
						if( exp == -1 ) {
							inverse() ;
						} else {
							cout << "do some other negative power > 1" << endl ;
						}
					} else if( exp == 0 ) {
						cout << "return identity matrix" << endl ;
					} else {
						int i = 1 ;
						matrix<T> temp = *this ;
						while(i < exp) {
							*this *= temp ;
							++i ;
						}
					}
				}
			} catch(int e) {
				cout << "matrix<T>::operator^ "
					<< "only valid for square matrices." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		/**
		 * Decomposes a matrix into its upper and lower triangular
		 * matricies.
		 */
		inline void lu_decomp(matrix& upper, matrix& lower) {
			try {
				if( _rows != _cols ) {
					throw -1 ;
				} else {
					upper.resize(_rows, _cols) ;
					lower.resize(_rows, _cols) ;
					for(size_t i=0; i<_rows; ++i) {
						for(size_t j=0; j<_cols; ++j) {
							if( i == 0 ) upper.pData[i*_rows+j] = pData[i*_rows+j] ;
							if( i == j ) lower.pData[i*_rows+j]= 1 ;
							if( (i != 0) && (j == 0) ) {
								lower.pData[i*_rows+j] = pData[i*_rows] / upper.pData[0] ;
							}
							if( (j >= i) && (i != 0) ) {
								T temp = 0 ;
								for(size_t k=0; k<=i-1; ++k) {
									temp +=
										lower.pData[i*_rows+k] * upper.pData[k*_rows+j] ;
								}
								upper.pData[i*_rows+j] = pData[i*_rows+j] - temp ;
							}
							if( (j < i) && (j != 0) ) {
								T temp = 0 ;
								for(size_t k=0; k<=j-1; ++k) {
									temp +=
										lower.pData[i*_rows+k] * upper.pData[k*_rows+j] ;
								}
								lower.pData[i*_rows+j] =
									(pData[i*_rows+j] - temp) / upper.pData[j*_rows+j] ;
							}
						}
					}
				}
			} catch (int e) {
				cout << "matrix::lu_decomp: Only square, non-singular "
					 << "matrices may be decompesed into upper/lower "
					 << "triangular matrices. Setting determinant to "
					 << "zero and singularness to true."
					 << endl ;
				m_det = 0 ;
				bSingular = true ;
				bVerify = false ;
			}
		}

		/**
		 * Resizes matrix to have r rows and c columns. Data
		 * is then deleted and reallocated to the new size.
		 * Data is not preserved at resizing a matrix!!
		 */
		inline void resize(const size_t& r, const size_t& c) {
			size_t N = r * c ;
			_rows = r ;
			_cols = c ;
			bVerify = true ;
			bSingular = false ;
			delete[] pData ;
			pData = new T[N] ;
			memset(pData, 0, N*sizeof(T)) ;
		}
		
		/**
		 * Swaps row a with row b.
		 */
		inline void swap_row(const size_t& r1, const size_t& r2) {
			T temp ;
			for(size_t i=0; i<_cols; ++i) {
				temp = pData[r1*_rows+i];
				pData[r1*_rows+i] = pData[r2*_rows+i] ;
				pData[r2*_rows+i] = temp ;
			}
			bVerify = true ;
			bSingular = false ;
		}
		
		/**
		 * Swaps column a with column b
		 */
		inline void swap_col(const size_t& c1, const size_t& c2) {
			T temp ;
			for(size_t i=0; i<_rows; ++i) {
				temp = pData[i*_rows+c1] ;
				pData[i*_rows+c1] = pData[i*_rows+c2] ;
				pData[i*_rows+c2] = temp ;
			}
			bVerify = true ;
			bSingular = false ;
		}
		
		/**
		 * Adds row r1 * x to row r2
		 */
		inline void add_row(const size_t& r1, 
							const size_t& r2, T x=1 )
		{
			for(size_t i=0; i<_cols; ++i) {
				pData[r2*_rows+i] += pData[r1*_rows+i] * x ;
			}
		}
		
		/**
		 * Adds column c1 * x to column c2
		 */
		inline void add_col(const size_t& c1, 
							const size_t& c2, T x=1 )
		{
			for(size_t i=0; i<_rows; ++i) {
				pData[i*_rows+c2] += pData[i*_rows+c1] * x ;
			}
		}
		
		/**
		 * Multiply a row by x
		 */
		inline void x_row(const size_t& r, T x) {
			for(size_t i=0; i<_cols; ++i) {
				pData[r*_rows+i] *= x ;
			}
		}

		/**
		 * Multiply a column by x
		 */
		inline void x_col(const size_t& c, T x) {
			for(size_t i=0; i<_rows; ++i) {
				pData[i*_rows+c] *= x ;
			}
		}
				
	/*================== Comparison Operators ==================*/
		inline bool operator== (matrix& rhs) {
			int n = memcmp( pData, rhs.pData, 
						    sizeof(T)*sizeof(pData) ) ;
			return ( _rows == rhs._rows &&
				 	 _cols == rhs._cols && n == 0 ) ;
		}

		inline bool operator!= (matrix& rhs) {
			return !(*this==rhs) ;
		}

/********************** IO Stream overloads ***********************/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

	private:
		T* pData ;
		size_t _rows ;
		size_t _cols ;
		bool bSingular ;
		bool bVerify ;
		T m_det ;


		/**
		 * Determine if the matrix is singular
		 * This function is used to determine if a matrix is singular
		 * by first looking to see if a zero row or column exists.
		 * If one exists, the bSingular member variable is set to
		 * true and m_det is set to zero.
		 * If a zero row/column is not found, the determinant of the
		 * matrix is then calculated and checked to be non-zero.
		 */		
		inline void singularity() {
			if( bVerify ) {

				if( _rows != _cols ) {
					m_det = 0 ;
					bSingular = true ;
				}

				// check for a zero row
				if( !bSingular ) {
					for(size_t i=0; i<_rows; ++i) {
						bool _zero = false ;
						if( pData[i*_rows+0] == 0 ) {
							for(size_t j=1; j<_cols; ++j) {
								if( pData[i*_rows+j] != 0 ) {
									_zero = false ;
									break ;
								} else {
									_zero = true ;
								}
							}
						}
						if( _zero ) {
							bSingular = true ;
							m_det = 0 ;
							break ;
						}
					}
				}

				// check for a zero column
				if( !bSingular ) {
					for(size_t i=0; i<_cols; ++i) {
						bool _zero = false ;
						if( pData[i] == 0 ) {
							for(size_t j=1; j<_rows; ++j) {
								if( pData[j*_rows+i] == 0 ) {
									_zero = true ;
								} else {
									_zero = false ;
									break ;
								}
							}
						}
						if( _zero ) {
							bSingular = true ;
							m_det = 0 ;
							break ;
						}
					}
				}

				// check for determinant equals zero and for matrices
				// of int types, determinant must be 1 or -1 otherwise
				// matrix is singular
				if( !bSingular ) {
					determinant() ;
					T zero = m_det ;
					if( zero == 0 ) {
						bSingular = true ;
					} else {
						if( typeid(T) == typeid(int) ) {
							if( zero == 1 || zero == -1 ) {
								bSingular = false ;
							} else {
								bSingular = true ;
							}
						} else {
							bSingular = false ;
						}
					}
				}
				
				bVerify = false ;
			}
		}

		/**
		 * Calculates the determinant of the matrix. If the determinant
		 * is returned as zero, bSingular flag is set to true. 
		 * Otherwise it is set to true. In both cases the bVerify
		 * flag is then set to false.
		 */
		inline void determinant() {
			m_det = determinant(pData, _cols) ;
		}
		
		inline T determinant(const T* data, const size_t& n) {
			T result = 0 ;
			T* temp = new T[n*n] ;
			if( n == 1 ) {
				delete[] temp ;
				return data[0] ;
			} else if( n == 2 ) {
				delete[] temp ;
				return (data[0]*data[3]-data[1]*data[2]) ;
			} else {
				for(size_t p=0; p<n; ++p) {
					size_t h = 0 ;
					size_t k = 0 ;
					for(size_t i=1; i<n; ++i) {
						for(size_t j=0; j<n; ++j) {
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

};

template <class T>
inline std::ostream& operator<< (std::ostream& os, matrix<T>& output) {
	os << "\nrows: " << output._rows << "   det:   " << output.det() 
	   << "\ncols: " << output._cols ;
	if( output.bSingular ) {
		os << "   singular" << endl ;
	} else {
		os << "   non-singular" << endl ;
	}
	for(size_t i=0; i<output._rows; ++i) {
		os << "| " ;
		for(size_t j=0; j<output._cols; ++j) {
			char buf[32];
            T data = output.pData[i*output._rows+j];
            if( typeid(T) == typeid(int) ) {
            	if( data >= 1e5 ) {
            		sprintf(buf, "%1.1e ", (double)data) ;
            	} else {
        			sprintf(buf, "%7d ", (int)data) ;
        		}
            } else {
            	if( (abs(data) >= 1e10) || (abs(data) <= 1e-4) ) {
            		if( abs(data) <= 1e-40 ) {
            			sprintf(buf, "%10.0f ", (double)data) ;
            		} else {
            			sprintf(buf, "%10.3e ", (double)data) ;
            		}
            	} else {
        			sprintf(buf, "%10.3f ", (double)data) ;
        		}
            }
            os <<  buf ;
		}
		os << " |" << endl ;
	}
	return os ;
}

/*********************** MATRIX OPERATIONS *************************
**
* This section contains all metatemplates for the various
* matrix operations for this class. That would return a new matrix
* but instead return class copies.
*
*******************************************************************/

/** ===================Scalar Multiplication=================== **/
template<typename T>
class matrix_scale_up : public matrix_expression<matrix_scale_up,T> {
		T _c ;
		matrix<T> const& _m ;
	public:
		matrix_scale_up(T c, matrix<T> const& m) :
			_c(c), _m(m) {}
		size_t rows() const { return _m.rows() ; }
		size_t cols() const { return _m.cols() ; }
		bool verify() const { return _m.verify() ; }
		bool singular() const { return _m.singular() ; }
		T operator() (size_t i, size_t j) const { return _c * _m(i,j) ; }
};

template<typename T>
matrix_scale_up<T> const operator* (T c, matrix<T> const& m)
{
	return matrix_scale_up<T>(c,m) ;
}

template<typename T>
matrix_scale_up<T> const operator* (matrix<T> const& m, T c)
{
	return matrix_scale_up<T>(c,m) ;
}

/** ======================Scalar Division====================== **/
template<typename T>
class matrix_scale_down : public matrix_expression<matrix_scale_down,T> {
		T _c ;
		matrix<T> const& _m ;
	public:
		matrix_scale_down(T c, matrix<T> const& m) :
			_c(c), _m(m) {}
		size_t rows() const { return _m.rows() ; }
		size_t cols() const { return _m.cols() ; }
		bool verify() const { return _m.verify() ; }
		bool singular() const { return _m.singular() ; }
		T operator() (size_t i, size_t j) const { return _m(i,j) / _c ; }
};

template<typename T>
matrix_scale_down<T> const operator/ (T c, matrix<T> const& m)
{
	return matrix_scale_down<T>(c,m) ;
}

template<typename T>
matrix_scale_down<T> const operator/ (matrix<T> const& m, T c)
{
	return matrix_scale_down<T>(c,m) ;
}

/** ======================Scalar Addition====================== **/
template<typename T>
class matrix_scale_add : public matrix_expression<matrix_scale_add,T> {
		T _c ;
		matrix<T> const& _m ;
	public:
		matrix_scale_add(T c, matrix<T> const& m) :
			_c(c), _m(m) {}
		size_t rows() const { return _m.rows() ; }
		size_t cols() const { return _m.cols() ; }
		bool verify() const { return _m.verify() ; }
		bool singular() const { return _m.singular() ; }
		T operator() (size_t i, size_t j) const { return _m(i,j) + _c ; }
};

template<typename T>
matrix_scale_add<T> const operator+ (T c, matrix<T> const& m)
{
	return matrix_scale_add<T>(c,m) ;
}

template<typename T>
matrix_scale_add<T> const operator+ (matrix<T> const& m, T c)
{
	return matrix_scale_add<T>(c,m) ;
}

/** =====================Scalar Subtration===================== **/
template<typename T>
class matrix_scale_minus : public matrix_expression<matrix_scale_minus,T> {
		T _c ;
		matrix<T> const& _m ;
	public:
		matrix_scale_minus(T c, matrix<T> const& m) :
			_c(c), _m(m) {}
		size_t rows() const { return _m.rows() ; }
		size_t cols() const { return _m.cols() ; }
		bool verify() const { return _m.verify() ; }
		bool singular() const { return _m.singular() ; }
		T operator() (size_t i, size_t j) const { return _m(i,j) - _c ; }
};

template<typename T>
matrix_scale_minus<T> const operator- (T c, matrix<T> const& m)
{
	return matrix_scale_minus<T>(c,m) ;
}

template<typename T>
matrix_scale_minus<T> const operator- (matrix<T> const& m, T c)
{
	return matrix_scale_minus<T>(c,m) ;
}

/** ===================== Modulation ===================== **/
template<typename T>
class matrix_scale_mod : public matrix_expression<matrix_scale_mod,T> {
		T _c ;
		matrix<T> const& _m ;
	public:
		matrix_scale_mod(T c, matrix<T> const& m) :
			_c(c), _m(m) {}
		size_t rows() const { return _m.rows() ; }
		size_t cols() const { return _m.cols() ; }
		bool verify() const { return _m.verify() ; }
		bool singular() const { return _m.singular() ; }
		T operator() (size_t i, size_t j) const { return _m(i,j) % _c ; }
};

template<typename T>
matrix_scale_mod<T> const operator- (T c, matrix<T> const& m)
{
	return matrix_scale_mod<T>(c,m) ;
}

template<typename T>
matrix_scale_mod<T> const operator- (matrix<T> const& m, T c)
{
	return matrix_scale_mod<T>(c,m) ;
}

/** ================== Matrix Multiplication ================== **/
template<typename T>
class matrix_prod : public matrix_expression<matrix_prod,T> {
		matrix<T> const& _lhs ;
		matrix<T> const& _rhs ;
	public:
		matrix_prod(matrix<T> const& lhs, matrix<T> const& rhs) :
			_lhs(lhs), _rhs(rhs) {}
		size_t rows() const { return _lhs.rows() ; }
		size_t cols() const { return _rhs.cols() ; }
		bool verify() const { return true ; }
		bool singular() const { return false ; }
		T operator() (size_t i, size_t j) const {
			T c = 0 ;
			for(size_t n=0; n<_lhs.cols(); ++n) {
				c += _lhs(i,n) * _rhs(n,j) ;
			}
			return c ;
		}
};

template<typename T>
matrix_prod<T> const operator* (matrix<T> const& lhs, matrix<T> const& rhs)
{
	assert( lhs.cols() == rhs.rows() ) ;
	return matrix_prod<T>(lhs,rhs) ;
}

/** ===================== Matrix Addition ===================== **/
template<typename T>
class matrix_sum : public matrix_expression<matrix_sum,T> {
		matrix<T> const& _lhs ;
		matrix<T> const& _rhs ;
	public:
		matrix_sum(matrix<T> const& lhs, matrix<T> const& rhs) :
			_lhs(lhs), _rhs(rhs) {}
		size_t rows() const { return _lhs.rows() ; }
		size_t cols() const { return _rhs.cols() ; }
		bool verify() const { return true ; }
		bool singular() const { return false ; }
		T operator() (size_t i, size_t j) const {
			return _lhs(i,j) + _rhs(i,j) ;
		}
};

template<typename T>
matrix_sum<T> const operator+ (matrix<T> const& lhs, matrix<T> const& rhs)
{
	assert( lhs.cols() == rhs.cols() &&
			lhs.rows() == rhs.rows() ) ;
	return matrix_sum<T>(lhs,rhs) ;
}

/** =================== Matrix Subtraction =================== **/
template<typename T>
class matrix_minus : public matrix_expression<matrix_minus,T> {
		matrix<T> const& _lhs ;
		matrix<T> const& _rhs ;
	public:
		matrix_minus(matrix<T> const& lhs, matrix<T> const& rhs) :
			_lhs(lhs), _rhs(rhs) {}
		size_t rows() const { return _lhs.rows() ; }
		size_t cols() const { return _rhs.cols() ; }
		bool verify() const { return true ; }
		bool singular() const { return false ; }
		T operator() (size_t i, size_t j) const {
			return _lhs(i,j) - _rhs(i,j) ;
		}
};

template<typename T>
matrix_minus<T> const operator- (matrix<T> const& lhs, matrix<T> const& rhs)
{
	assert( lhs.cols() == rhs.cols() &&
			lhs.rows() == rhs.rows() ) ;
	return matrix_minus<T>(lhs,rhs) ;
}

}	// end of namespace math
}	// end of namespace genecis

#endif
