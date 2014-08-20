/**
 * @file new matrix class
 */

#ifndef GENECIS_MATH_MATRIX
#define GENECIS_MATH_MATRIX

#include <genecis/math/matrix_io.h>
#include <genecis/math/matrix_operations.h>

namespace genecis {
namespace math {

	using namespace std ;

	template<class _T> class matrix :
		public matrix_expression<matrix, _T> {

			typedef matrix<_T> 		self_type ;
			typedef _T				value_type ;
			typedef size_t			size_type ;
			typedef _T *			pointer ;
			typedef _T &			reference ;
			typedef const _T &		const_reference ;
			typedef pointer			iterator ;
			typedef const pointer	const_iterator ;

		public:
	/******************** Constructor/Destructors *********************/
			/**
			 * Main  Constructor
			 * Creates an NxM matrix from a basic array
			 * Defaults to a 1x1 matrix
			 */
			matrix(size_type _rows=1, size_type _cols=1) : 
				__rows(_rows), __cols(_cols),
				bSingular(false), bVerify(true)
			{
				size_type N = __rows * __cols ;
				__data = new value_type[N] ;
				memset(__data, 0, N * sizeof(value_type)) ;
			}

			/**
			 * Copy Constructor
			 */
			template<template <typename> class E>
			matrix(matrix_expression<E,value_type> const& r) {
				E<value_type> const& rhs = r ;
				__rows = rhs.rows() ;
				__cols = rhs.cols() ;
				bVerify = true ;
				bSingular = rhs.singular() ;
				size_type N = __rows * __cols ;
				__data = new value_type[N] ;
				for(size_type i=0; i<__rows; ++i) {
					for(size_type j=0; j<__cols; ++j) {
						__data[i*__cols+j] = rhs(i,j) ;
					}
				}
			}
		
			/**
			 * Destructor
			 */
			virtual ~matrix() {
				if(__data) {
					delete[] __data ;
					__data = NULL ;
				}
			}

			inline size_type rows() const {
				return __rows ;
			}

			inline size_type cols() const {
				return __cols ;
			}

			inline bool singular() const {
				return bSingular ;
			}
		
			inline value_type det() {
				if ( bVerify ) {
					singularity() ;
				}
				return m_det ;
			}
		
			inline bool verify() const {
				return bVerify ;
			}
		
			inline value_type* data() const {
				return __data ;
			}

	/************************* Operators ******************************/
			/* Accessor and Assigner */
			inline value_type& operator() (size_type i, size_type j) const {
				return __data[ i * __cols + j ] ;
			}

			template<size_type _index>
			inline void operator= (value_type c) {
				bVerify = true ;
				__data[_index] = c ;
			}

		/*================= Matrix Scalar Operators ================*/
			inline void operator*= (value_type c) {
				for(size_type i=0; i<(__rows*__cols); ++i) {
					__data[i] *= c ;
				}
				m_det *= pow(c,__rows) ; ;
			}

			inline void operator/= (value_type c) {
				for(size_type i=0; i<(__rows*__cols); ++i) {
					__data[i] /= c ;
				}
				m_det /= pow(c,__rows) ; ;
			}

			inline void operator+= (value_type c) {
				for(size_type i=0; i<(__rows*__cols); ++i) {
					__data[i] += c ;
				}
				m_det = determinant(__data, __cols) ;
			}

			inline void operator-= (value_type c) {
				for(size_type i=0; i<(__rows*__cols); ++i) {
					__data[i] -= c ;
				}
				m_det = determinant(__data, __cols) ;
			}

			inline void operator%= (value_type c) {
				for(size_type i=0; i<(__rows*__cols); ++i) {
					__data[i] %= c ;
				}
				m_det = determinant(__data, __cols) ;
			}

		/*================ Matrix Matrix Operators =================*/
			inline void operator*= (matrix& rhs) {
				try {
					if( __cols != rhs.__rows ) {
						throw 1;
					} else {
						matrix<value_type> temp = *this ;
						*this = temp * rhs ;
						this->bVerify = true ;
						this->bSingular = false ;
					}
				} catch (int e) {
					cout << "matrix::operator*=: A _cols(" << __cols
						 << ") must equal B _rows(" << rhs.__rows
						 << ")." << endl ;
					exit(e) ;
				}
			}
		
			inline void operator+= (matrix& rhs) {
				try {
					if( __rows != rhs.__rows || __cols != rhs.__cols ) {
						throw 1 ;
					} else {
						matrix<value_type> temp = *this ;
						*this = temp + rhs ;
						bVerify = true ;
						bSingular = false ;
					}
				} catch (int e) {
					cout << "matrix::operator+=: Only defined for matrices with "
						 << "the same number of _rows and columns." << endl ;
					cout << *this << endl ;
					cout << rhs << endl ;
					exit(e) ;
				}
			}
		
			inline void operator-= (matrix& rhs) {
				try {
					if( __rows != rhs.__rows || __cols != rhs.__cols ) {
						throw 1 ;
					} else {
						matrix<value_type> temp = *this ;
						*this = temp - rhs ;
						bVerify = true ;
						bSingular = false ;
					}
				} catch (int e) {
					cout << "matrix::operator-=: Only defined for matrices with "
						 << "the same number of _rows and columns." << endl ;
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
				matrix<value_type>* temp = new matrix<value_type>(__cols,__rows) ;
				for(size_type i=0; i<__rows; ++i) {
					for(size_type j=0; j<__cols; ++j) {
						temp->__data[j*__rows+i] = __data[i*__rows+j] ;
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
				m_trans.resize(__cols, __rows) ;
				for(size_type i=0; i<__rows; ++i) {
					for(size_type j=0; j<__cols; ++j) {
						m_trans->__data[j*__rows+i] = __data[i*__rows+j] ;
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
						matrix<value_type>* inv_mtx = this ;
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
					if( __cols != __rows ) {
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
							matrix<value_type> temp = *this ;
							while(i < exp) {
								*this *= temp ;
								++i ;
							}
						}
					}
				} catch(int e) {
					cout << "matrix<value_type>::operator^ "
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
					if(  bSingular || (__rows != __cols) ) {
						throw -1 ;
					} else {
						lu_factorize( upper, lower, __data, __rows, __cols ) ;
					}
				} catch (int e) {
	//				cout << "matrix::lu_decomp: Only square, non-singular "
	//					 << "matrices may be decompesed into upper/lower "
	//					 << "triangular matrices. Setting determinant to "
	//					 << "zero and singularness to true."
	//					 << endl ;
					m_det = 0 ;
					bSingular = true ;
					bVerify = false ;
				}
			}

			/**
			 * Resizes matrix to have r _rows and c columns. Data
			 * is then deleted and reallocated to the new size.
			 * Data is not preserved at resizing a matrix!!
			 */
			inline void resize(const size_type& r, const size_type& c) {
				size_type N = r * c ;
				__rows = r ;
				__cols = c ;
				bVerify = true ;
				bSingular = false ;
				delete[] __data ;
				__data = new value_type[N] ;
				memset(__data, 0, N*sizeof(value_type)) ;
			}
		
			/**
			 * Swaps row a with row b.
			 */
			inline void swap_row(const size_type& r1, const size_type& r2) {
				value_type temp ;
				for(size_type i=0; i<__cols; ++i) {
					temp = __data[r1*__rows+i];
					__data[r1*__rows+i] = __data[r2*__rows+i] ;
					__data[r2*__rows+i] = temp ;
				}
				bVerify = true ;
				bSingular = false ;
			}
		
			/**
			 * Swaps column a with column b
			 */
			inline void swap_col(const size_type& c1, const size_type& c2) {
				value_type temp ;
				for(size_type i=0; i<__rows; ++i) {
					temp = __data[i*__rows+c1] ;
					__data[i*__rows+c1] = __data[i*__rows+c2] ;
					__data[i*__rows+c2] = temp ;
				}
				bVerify = true ;
				bSingular = false ;
			}
		
			/**
			 * Adds row r1 * x to row r2
			 */
			inline void add_row(const size_type& r1, 
								const size_type& r2, value_type x=1 )
			{
				for(size_type i=0; i<__cols; ++i) {
					__data[r2*__rows+i] += __data[r1*__rows+i] * x ;
				}
			}
		
			/**
			 * Adds column c1 * x to column c2
			 */
			inline void add_col(const size_type& c1, 
								const size_type& c2, value_type x=1 )
			{
				for(size_type i=0; i<__rows; ++i) {
					__data[i*__rows+c2] += __data[i*__rows+c1] * x ;
				}
			}
		
			/**
			 * Multiply a row by x
			 */
			inline void x__row(const size_type& r, value_type x) {
				for(size_type i=0; i<__cols; ++i) {
					__data[r*__rows+i] *= x ;
				}
			}

			/**
			 * Multiply a column by x
			 */
			inline void x__col(const size_type& c, value_type x) {
				for(size_type i=0; i<__rows; ++i) {
					__data[i*__rows+c] *= x ;
				}
			}
				
		/*================== Comparison Operators ==================*/
			inline bool operator== (matrix& rhs) {
				int n = memcmp( __data, rhs.__data, 
								sizeof(value_type)*sizeof(__data) ) ;
				return ( __rows == rhs.__rows &&
					 	 __cols == rhs.__cols && n == 0 ) ;
			}

			inline bool operator!= (matrix& rhs) {
				return !(*this==rhs) ;
			}

	/********************** IO Stream overloads ***********************/
	//		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

		private:
			value_type* __data ;
			size_type __rows ;
			size_type __cols ;
			bool bSingular ;
			bool bVerify ;
			value_type m_det ;


			/**
			 * Determine if the matrix is singular
			 * This function is used to determine if a matrix is singular
			 * by first looking to see if a zero _row or column exists.
			 * If one exists, the bSingular member variable is set to
			 * true and m_det is set to zero.
			 * If a zero _row/column is not found, the determinant of the
			 * matrix is then calculated and checked to be non-zero.
			 */		
			inline void singularity() {
				if( bVerify ) {

					// Only square matricies can be non-singular
					if( __rows != __cols ) {
						m_det = 0 ;
						bSingular = true ;
					}

					// check for a zero _row
					if( !bSingular ) {
						if( check_zero_row(__data, __rows, __cols) ) {
							bSingular = true ;
							m_det = 0 ;
						}
					}

					// check for a zero column
					if( !bSingular ) {
						if( check_zero_column(__data, __rows, __cols) ) {
							bSingular = true ;
							m_det = 0 ;
						}
					}

					// check for determinant equals zero and for matrices
					// of int types, determinant must be 1 or -1 otherwise
					// matrix is singular
					if( !bSingular ) {
						m_det = determinant(__data, __cols) ;
						if( !m_det ) {
							bSingular = true ;
						} else {
							if( typeid(value_type) == typeid(int) ) {
								if( m_det == 1 || m_det == -1 ) {
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

	};

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
