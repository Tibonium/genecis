/**
 * @file new matrix class
 */

#ifndef GENECIS_MATH_MATRIX
#define GENECIS_MATH_MATRIX

#include <genecis/container/array.h>
#include <genecis/math/matrix_io.h>
#include <genecis/math/matrix_operations.h>

using namespace genecis::container ;

namespace genecis {
namespace math {

	using namespace std ;

	template<class T> class matrix :
		public matrix_expression<matrix<T> > {

		public:

			typedef matrix<T> 		self_type ;
			typedef array<T>		container_type ;
			typedef T				value_type ;
			typedef size_t			size_type ;
			typedef T *				pointer ;
			typedef T &				reference ;
			typedef const T &		const_reference ;
			typedef pointer			iterator ;
			typedef const pointer	const_iterator ;

	/******************** Constructor/Destructors *********************/
			/**
			 * Main  Constructor
			 * Creates an NxM matrix from a basic array
			 * Defaults to a 1x1 matrix
			 */
			matrix(size_type rows=1, size_type cols=1) : 
				__rows(rows), __cols(cols),
				__singular(false), __verify(true),
				__diagonal(false)
			{
				size_type N = __rows * __cols ;
				__data = container_type(N) ;
			}

			/**
			 * Copy Constructor
			 */
			template<class M>
			matrix(matrix_expression<M> const& rhs) {
				__rows = rhs().rows() ;
				__cols = rhs().cols() ;
				__verify = true ;
				__singular = false ;
				__diagonal = false ;
				__data = rhs().data() ;
			}
		
			/**
			 * Destructor
			 */
			virtual ~matrix() {}

			inline size_type rows() const {
				return __rows ;
			}

			inline size_type cols() const {
				return __cols ;
			}

			inline bool singular() const {
				return __singular ;
			}
		
			inline value_type det() {
				if ( __verify ) {
					singularity() ;
				}
				return __determinent ;
			}
		
			inline bool verify() const {
				return __verify ;
			}
			
			inline bool diagonal() const {
				return __diagonal ;
			}

			inline void diagonal(bool state) {
				__diagonal = state ;
				__verify = !state ;
			}

			inline container_type data() const {
				return __data ;
			}

	/************************* Operators ******************************/
			/* Accessor and Assigner */
			// m(i,j) = __data( i*__col + j )
			inline reference operator() (size_type i, size_type j) {
				return __data( i * __cols + j ) ;
			}

			inline const_reference operator() (size_type i, size_type j) const {
				return __data( i * __cols + j ) ;
			}

			template<size_type _index>
			inline void operator= (value_type c) {
				__verify = true ;
				(*this)(_index) = c ;
			}

		/*================= Matrix Scalar Operators ================*/
			inline void operator*= (value_type c) {
				__data *= c ;
				__determinent *= pow(c,__rows) ; ;
			}

			inline void operator/= (value_type c) {
				__data /= c ;
				__determinent /= pow(c,__rows) ; ;
			}

			inline void operator+= (value_type c) {
				__data += c ;
				__determinent = determinant( *this ) ;
			}

			inline void operator-= (value_type c) {
				__data -= c ;
				__determinent = determinant( *this ) ;
			}

			inline void operator%= (value_type c) {
				__data %= c ;
				__determinent = determinant( *this ) ;
			}

		/*================ Matrix Matrix Operators =================*/
			self_type operator* (const self_type& rhs) {
				self_type tmp ;
				tmp.__rows = rhs.rows() ;
				tmp.__cols = rhs.cols() ;
				tmp.__data = multiply((*this).__data, rhs.__data) ;
				return tmp ;
			}
		
			inline void operator*= (matrix& rhs) {
				try {
					if( __cols != rhs.__rows ) {
						throw 1;
					} else {
						matrix<value_type> temp = *this ;
						*this = temp * rhs ;
						this->__verify = true ;
						this->__singular = false ;
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
						__verify = true ;
						__singular = false ;
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
						__verify = true ;
						__singular = false ;
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
					if( __singular || __determinent == 0 ) {
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
			template<class M>
			inline void lu_decomp(matrix_expression<M>& upper, matrix_expression<M>& lower) {
				try {
					if(  __singular || (__rows != __cols) ) {
						throw -1 ;
					} else {
						lu_factorize( upper, lower, *this ) ;
					}
				} catch (int e) {
	//				cout << "matrix::lu_decomp: Only square, non-singular "
	//					 << "matrices may be decompesed into upper/lower "
	//					 << "triangular matrices. Setting determinant to "
	//					 << "zero and singularness to true."
	//					 << endl ;
					__determinent = 0 ;
					__singular = true ;
					__verify = false ;
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
				__verify = true ;
				__singular = false ;
				__data = container_type(N) ;
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
				__verify = true ;
				__singular = false ;
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
				__verify = true ;
				__singular = false ;
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
			container_type __data ;
			size_type __rows ;
			size_type __cols ;
			bool __singular ;
			bool __verify ;
			bool __diagonal ;
			value_type __determinent ;


			/**
			 * Determine if the matrix is singular
			 * This function is used to determine if a matrix is singular
			 * by first looking to see if a zero _row or column exists.
			 * If one exists, the __singular member variable is set to
			 * true and __determinent is set to zero.
			 * If a zero _row/column is not found, the determinant of the
			 * matrix is then calculated and checked to be non-zero.
			 */		
			inline void singularity() {
				if( __verify ) {

					// Only square matricies can be non-singular
					if( __rows != __cols ) {
						__determinent = 0 ;
						__singular = true ;
					}

					// check for a zero _row
					if( !__singular ) {
						if( check_zero_row( data(), __rows, __cols) ) {
							__singular = true ;
							__determinent = 0 ;
						}
					}

					// check for a zero column
					if( !__singular ) {
						if( check_zero_column( data(), __rows, __cols) ) {
							__singular = true ;
							__determinent = 0 ;
						}
					}

					// check for determinant equals zero and for matrices
					// of int types, determinant must be 1 or -1 otherwise
					// matrix is singular
					if( !__singular ) {
						__determinent = determinant( *this ) ;
						if( !__determinent ) {
							__singular = true ;
						} else {
							if( typeid(value_type) == typeid(int) ) {
								if( __determinent == 1 || __determinent == -1 ) {
									__singular = false ;
								} else {
									__singular = true ;
								}
							} else {
								__singular = false ;
							}
						}
					}
				
					__verify = false ;
				}
			}

	};

}	// end of namespace math
}	// end of namespace genecis
#endif
