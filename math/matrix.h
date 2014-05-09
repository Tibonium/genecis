/**
 * @file new matrix class
 */

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <typeinfo>

using namespace std ;

template<class _T> class matrix ;

template<class _T>
std::ostream& operator<< (std::ostream& os, matrix<_T>& output) ;

template<class _T> class matrix {

		typedef matrix<_T> self_type ;

	public:
		inline size_t nrow() const {
			return m_nrow ;
		}

		inline size_t ncol() const {
			return m_ncol ;
		}

		inline bool singular() const {
			return bSingular ;
		}
		
		inline _T det() {
			if ( bVerify ) {
				singularity() ;
			}
			return m_det ;
		}
		
		inline _T* data() const {
			return pData ;
		}

/************************* Operators ******************************/
		/* Accessor and Assigner */
		inline _T& operator() (size_t i, size_t j) {
			m_index = i * m_ncol + j ;
			return pData[m_index] ;
		}

		inline void operator= (_T c) {
			bVerify = true ;
			pData[m_index] = c ;
		}

	/*================= Matrix Scalar Operators ================*/
		inline matrix& operator* (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] *= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator*= (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] *= c ;
			}
			determinant() ;
		}

		inline matrix& operator/ (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] /= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator/= (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] /= c ;
			}
			determinant() ;
		}

		inline matrix& operator+ (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] += c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator+= (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] += c ;
			}
			determinant() ;
		}

		inline matrix& operator- (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] -= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator-= (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] -= c ;
			}
			determinant() ;
		}

		inline matrix& operator% (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] %= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator%= (_T c) {
			for(size_t i=0; i<(m_nrow*m_ncol); ++i) {
				pData[i] %= c ;
			}
			determinant() ;
		}

	/*================ Matrix Matrix Operators =================*/
		inline matrix* operator* (matrix& rhs) {
			try {
				if( m_ncol != rhs.m_nrow ) {
					throw 1;
				} else {
					matrix<_T>* temp = new matrix<_T>(m_nrow,rhs.m_ncol) ;
					_T c = 0 ;
					for(size_t n=0; n<temp->m_nrow; ++n) {
						for(size_t m=0; m<temp->m_ncol; ++m) {
							for(size_t i=0; i<m_ncol; ++i) {
								c += pData[n*m_nrow+i] * rhs.pData[i*m_ncol+m] ;
							}
							temp->pData[n*m_nrow+m] = c ;
							c = 0 ;
						}
					}
					return temp ;
				}
			} catch (int e) {
				cout << "matrix::operator*: A ncol(" << m_ncol
					 << ") must equal B nrow(" << rhs.m_nrow
					 << ")." << endl ;
				exit(e) ;
			}
		}

		inline void operator*= (matrix& rhs) {
			try {
				if( m_ncol != rhs.m_nrow ) {
					throw 1;
				} else {
					matrix<_T> temp = *this ;
					*this = temp * rhs ;
					this->bVerify = true ;
					this->bSingular = false ;
				}
			} catch (int e) {
				cout << "matrix::operator*=: A ncol(" << m_ncol
					 << ") must equal B nrow(" << rhs.m_nrow
					 << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline matrix* operator+ (matrix& rhs) {
			try {
				if( m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol ) {
					throw 1 ;
				} else {
					matrix<_T>* temp = new matrix<_T>(m_nrow,rhs.m_ncol) ;
					for(size_t i=0; i<m_nrow; ++i) {
						for(size_t j=0; j<m_ncol; ++j) {
							temp->pData[i*m_nrow+j] = 
								pData[i*m_nrow+j] + rhs.pData[i*m_nrow+j] ;
						}
					}
					return temp ;
				}
			} catch (int e) {
				cout << "matrix::operator+: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << rhs << endl ;
				exit(e) ;
			}
		}
		
		inline void operator+= (matrix& rhs) {
			try {
				if( m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol ) {
					throw 1 ;
				} else {
					matrix<_T> temp = *this ;
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
		
		inline matrix* operator- (matrix& rhs) {
			try {
				if( m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol ) {
					throw 1 ;
				} else {
					matrix<_T>* temp = new matrix<_T>(m_nrow,rhs.m_ncol) ;
					for(size_t i=0; i<m_nrow; ++i) {
						for(size_t j=0; j<m_ncol; ++j) {
							temp->pData[i*m_nrow+j] = 
								pData[i*m_nrow+j] - rhs.pData[i*m_nrow+j] ;
						}
					}
					return temp ;
				}
			} catch (int e) {
				cout << "matrix::operator-: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << rhs << endl ;
				exit(e) ;
			}
		}
		
		inline void operator-= (matrix& rhs) {
			try {
				if( m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol ) {
					throw 1 ;
				} else {
					matrix<_T> temp = *this ;
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
			matrix<_T>* temp = new matrix<_T>(m_ncol,m_nrow) ;
			for(size_t i=0; i<m_nrow; ++i) {
				for(size_t j=0; j<m_ncol; ++j) {
					temp->pData[j*m_nrow+i] = pData[i*m_nrow+j] ;
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
			m_trans.resize(m_ncol, m_nrow) ;
			for(size_t i=0; i<m_nrow; ++i) {
				for(size_t j=0; j<m_ncol; ++j) {
					m_trans->pData[j*m_nrow+i] = pData[i*m_nrow+j] ;
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
					matrix<_T>* inv_mtx = this ;
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
				if( m_ncol != m_nrow ) {
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
						matrix<_T> temp = *this ;
						while(i < exp) {
							*this *= temp ;
							++i ;
						}
					}
				}
			} catch(int e) {
				cout << "matrix<_T>::operator^ "
					<< "only valid for square matrices." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		inline void lu_decomp(matrix& upper, matrix& lower) {
			try {
				if( m_nrow != m_ncol ) {
					throw -1 ;
				} else {
					upper.resize(m_nrow, m_ncol) ;
					lower.resize(m_nrow, m_ncol) ;
					for(size_t i=0; i<m_nrow; ++i) {
						for(size_t j=0; j<m_ncol; ++j) {
							if( i == 0 ) upper.pData[i*m_nrow+j] = pData[i*m_nrow+j] ;
							if( i == j ) lower.pData[i*m_nrow+j]= 1 ;
							if( (i != 0) && (j == 0) ) {
								lower.pData[i*m_nrow+j] = pData[i*m_nrow] / upper.pData[0] ;
							}
							if( (j >= i) && (i != 0) ) {
								_T temp = 0 ;
								for(size_t k=0; k<=i-1; ++k) {
									temp +=
										lower.pData[i*m_nrow+k] * upper.pData[k*m_nrow+j] ;
								}
								upper.pData[i*m_nrow+j] = pData[i*m_nrow+j] - temp ;
							}
							if( (j < i) && (j != 0) ) {
								_T temp = 0 ;
								for(size_t k=0; k<=j-1; ++k) {
									temp +=
										lower.pData[i*m_nrow+k] * upper.pData[k*m_nrow+j] ;
								}
								lower.pData[i*m_nrow+j] =
									(pData[i*m_nrow+j] - temp) / upper.pData[j*m_nrow+j] ;
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
			m_nrow = r ;
			m_ncol = c ;
			bVerify = true ;
			bSingular = false ;
			delete[] pData ;
			pData = new _T[N] ;
			memset(pData, 0, N*sizeof(_T)) ;
		}
		
		/**
		 * Swaps row a with row b.
		 */
		inline void swap_row(const size_t& r1, const size_t& r2) {
			_T temp ;
			for(size_t i=0; i<m_ncol; ++i) {
				temp = pData[r1*m_nrow+i];
				pData[r1*m_nrow+i] = pData[r2*m_nrow+i] ;
				pData[r2*m_nrow+i] = temp ;
			}
			bVerify = true ;
			bSingular = false ;
		}
		
		/**
		 * Swaps column a with column b
		 */
		inline void swap_col(const size_t& c1, const size_t& c2) {
			_T temp ;
			for(size_t i=0; i<m_nrow; ++i) {
				temp = pData[i*m_nrow+c1] ;
				pData[i*m_nrow+c1] = pData[i*m_nrow+c2] ;
				pData[i*m_nrow+c2] = temp ;
			}
			bVerify = true ;
			bSingular = false ;
		}
		
		/**
		 * Adds row r1 * x to row r2
		 */
		inline void add_row(const size_t& r1, 
							const size_t& r2, _T x=1 )
		{
			for(size_t i=0; i<m_ncol; ++i) {
				pData[r2*m_nrow+i] += pData[r1*m_nrow+i] * x ;
			}
		}
		
		/**
		 * Adds column c1 * x to column c2
		 */
		inline void add_col(const size_t& c1, 
							const size_t& c2, _T x=1 )
		{
			for(size_t i=0; i<m_nrow; ++i) {
				pData[i*m_nrow+c2] += pData[i*m_nrow+c1] * x ;
			}
		}
		
		/**
		 * Multiply a row by x
		 */
		inline void x_row(const size_t& r, _T x) {
			for(size_t i=0; i<m_ncol; ++i) {
				pData[r*m_nrow+i] *= x ;
			}
		}

		/**
		 * Multiply a column by x
		 */
		inline void x_col(const size_t& c, _T x) {
			for(size_t i=0; i<m_nrow; ++i) {
				pData[i*m_nrow+c] *= x ;
			}
		}
				
	/*================== Comparison Operators ==================*/
		inline bool operator== (matrix& rhs) {
			int n = memcmp( pData, rhs.pData, 
						    sizeof(_T)*sizeof(pData) ) ;
			return ( m_nrow == rhs.m_nrow &&
				 	 m_ncol == rhs.m_ncol && n == 0 ) ;
		}

		inline bool operator!= (matrix& rhs) {
			return !(*this==rhs) ;
		}

/******************** Constructor/Destructors *********************/
		/**
		 * Main  Constructor
		 * Creates an NxM matrix from a basic array
		 * Defaults to a 1x1 matrix
		 */
		matrix(size_t nrow=1, size_t ncol=1) : 
			m_nrow(nrow), m_ncol(ncol),
			bSingular(false), bVerify(true)
		{
			size_t N = m_nrow * m_ncol ;
			pData = new _T[N] ;
			memset(pData, 0, N * sizeof(_T)) ;
		}

		/**
		 * Copy Constructor
		 */
		matrix(matrix& rhs) :
			m_nrow(rhs.m_nrow), m_ncol(rhs.m_ncol),
			bSingular(rhs.bSingular), bVerify(false),
			m_det(rhs.m_det)
		{
			size_t N = m_nrow * m_ncol ;			
			pData = new _T[N] ;
			memcpy(pData, rhs.pData, N * sizeof(_T)) ;
		}

		/**
		 * Assign Constructor
		 */
		inline matrix* operator= (matrix& rhs) {
			m_nrow = rhs.m_nrow ;
			m_ncol = rhs.m_ncol ;
			bVerify = rhs.bVerify ;
			bSingular = rhs.bSingular ;
			m_det = rhs.m_det ;
			delete pData ;
			pData = rhs.pData ;
			return this ;
		}
		
		/**
		 * Destructor
		 */
		virtual ~matrix() {
			if(pData) {
				delete pData ;
				pData = NULL ;
			}
		}

/********************** IO Stream overloads ***********************/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

	private:
		_T* pData ;
		size_t m_nrow ;
		size_t m_ncol ;
		size_t m_index ;
		bool bSingular ;
		bool bVerify ;
		_T m_det ;


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

				if( m_nrow != m_ncol ) {
					m_det = 0 ;
					bSingular = true ;
				}

				// check for a zero row
				if( !bSingular ) {
					for(size_t i=0; i<m_nrow; ++i) {
						bool _zero = false ;
						if( pData[i*m_nrow+0] == 0 ) {
							for(size_t j=1; j<m_ncol; ++j) {
								if( pData[i*m_nrow+j] != 0 ) {
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
					for(size_t i=0; i<m_ncol; ++i) {
						bool _zero = false ;
						if( pData[i] == 0 ) {
							for(size_t j=1; j<m_nrow; ++j) {
								if( pData[j*m_nrow+i] == 0 ) {
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
					_T zero = m_det ;
					if( zero == 0 ) {
						bSingular = true ;
					} else {
						if( typeid(_T) == typeid(int) ) {
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
			m_det = determinant(pData, m_ncol) ;
		}
		
		inline _T determinant(const _T* data, const size_t& n) {
			_T result = 0 ;
			_T* temp = new _T[n*n] ;
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

template <class _T>
inline std::ostream& operator<< (std::ostream& os, matrix<_T>& output) {
	os << "\nrows: " << output.m_nrow << "   det:   " << output.det() 
	   << "\ncols: " << output.m_ncol ;
	if( output.bSingular ) {
		os << "   singular" << endl ;
	} else {
		os << "   non-singular" << endl ;
	}
	for(size_t i=0; i<output.m_nrow; ++i) {
		os << "| " ;
		for(size_t j=0; j<output.m_ncol; ++j) {
			char buf[32];
            _T data = output.pData[i*output.m_nrow+j];
            if( typeid(_T) == typeid(int) ) {
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

#endif
