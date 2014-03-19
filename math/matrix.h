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
			return _nrow ;
		}

		inline size_t ncol() const {
			return _ncol ;
		}

		inline bool singular() const {
			return _singular ;
		}
		
		inline _T det() {
			if ( _verify ) {
				singularity() ;
			}
			return _det ;
		}
		
		inline _T* data() const {
			return _data ;
		}

/************************* Operators ******************************/
		/* Accessor and Assigner */
		inline _T& operator() (size_t i, size_t j) {
			_index = i * _ncol + j ;
			return _data[_index] ;
		}

		inline void operator= (_T c) {
			_verify = true ;
			_data[_index] = c ;
		}

	/*================= Matrix Scalar Operators ================*/
		inline matrix& operator* (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] *= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator*= (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] *= c ;
			}
			determinant() ;
		}

		inline matrix& operator/ (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] /= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator/= (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] /= c ;
			}
			determinant() ;
		}

		inline matrix& operator+ (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] += c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator+= (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] += c ;
			}
			determinant() ;
		}

		inline matrix& operator- (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] -= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator-= (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] -= c ;
			}
			determinant() ;
		}

		inline matrix& operator% (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] %= c ;
			}
			determinant() ;
			return *this ;
		}

		inline void operator%= (_T c) {
			for(size_t i=0; i<(_nrow*_ncol); ++i) {
				_data[i] %= c ;
			}
			determinant() ;
		}

	/*================ Matrix Matrix Operators =================*/
		inline matrix* operator* (matrix& rhs) {
			try {
				if( _ncol != rhs._nrow ) {
					throw 1;
				} else {
					matrix<_T>* temp = new matrix<_T>(_nrow,rhs._ncol) ;
					_T c = 0 ;
					for(size_t n=0; n<temp->_nrow; ++n) {
						for(size_t m=0; m<temp->_ncol; ++m) {
							for(size_t i=0; i<_ncol; ++i) {
								c += _data[n*_nrow+i] * rhs._data[i*_ncol+m] ;
							}
							temp->_data[n*_nrow+m] = c ;
							c = 0 ;
						}
					}
					return temp ;
				}
			} catch (int e) {
				cout << "matrix::operator*: A ncol(" << _ncol
					 << ") must equal B nrow(" << rhs._nrow
					 << ")." << endl ;
				exit(e) ;
			}
		}

		inline void operator*= (matrix& rhs) {
			try {
				if( _ncol != rhs._nrow ) {
					throw 1;
				} else {
					matrix<_T> temp = *this ;
					*this = temp * rhs ;
					this->_verify = true ;
					this->_singular = false ;
				}
			} catch (int e) {
				cout << "matrix::operator*=: A ncol(" << _ncol
					 << ") must equal B nrow(" << rhs._nrow
					 << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline matrix* operator+ (matrix& rhs) {
			try {
				if( _nrow != rhs._nrow || _ncol != rhs._ncol ) {
					throw 1 ;
				} else {
					matrix<_T>* temp = new matrix<_T>(_nrow,rhs._ncol) ;
					for(size_t i=0; i<_nrow; ++i) {
						for(size_t j=0; j<_ncol; ++j) {
							temp->_data[i*_nrow+j] = 
								_data[i*_nrow+j] + rhs._data[i*_nrow+j] ;
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
				if( _nrow != rhs._nrow || _ncol != rhs._ncol ) {
					throw 1 ;
				} else {
					matrix<_T> temp = *this ;
					*this = temp + rhs ;
					_verify = true ;
					_singular = false ;
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
				if( _nrow != rhs._nrow || _ncol != rhs._ncol ) {
					throw 1 ;
				} else {
					matrix<_T>* temp = new matrix<_T>(_nrow,rhs._ncol) ;
					for(size_t i=0; i<_nrow; ++i) {
						for(size_t j=0; j<_ncol; ++j) {
							temp->_data[i*_nrow+j] = 
								_data[i*_nrow+j] - rhs._data[i*_nrow+j] ;
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
				if( _nrow != rhs._nrow || _ncol != rhs._ncol ) {
					throw 1 ;
				} else {
					matrix<_T> temp = *this ;
					*this = temp - rhs ;
					_verify = true ;
					_singular = false ;
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
			matrix<_T>* temp = new matrix<_T>(_ncol,_nrow) ;
			for(size_t i=0; i<_nrow; ++i) {
				for(size_t j=0; j<_ncol; ++j) {
					temp->_data[j*_nrow+i] = _data[i*_nrow+j] ;
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
			m_trans.resize(_ncol, _nrow) ;
			for(size_t i=0; i<_nrow; ++i) {
				for(size_t j=0; j<_ncol; ++j) {
					m_trans->_data[j*_nrow+i] = _data[i*_nrow+j] ;
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
				if( _singular || _det == 0 ) {
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
				if( _ncol != _nrow ) {
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
				if( _nrow != _ncol ) {
					throw -1 ;
				} else {
					upper.resize(_nrow, _ncol) ;
					lower.resize(_nrow, _ncol) ;
					for(size_t i=0; i<_nrow; ++i) {
						for(size_t j=0; j<_ncol; ++j) {
							if( i == 0 ) upper._data[i*_nrow+j] = _data[i*_nrow+j] ;
							if( i == j ) lower._data[i*_nrow+j]= 1 ;
							if( (i != 0) && (j == 0) ) {
								lower._data[i*_nrow+j] = _data[i*_nrow] / upper._data[0] ;
							}
							if( (j >= i) && (i != 0) ) {
								_T temp = 0 ;
								for(size_t k=0; k<=i-1; ++k) {
									temp +=
										lower._data[i*_nrow+k] * upper._data[k*_nrow+j] ;
								}
								upper._data[i*_nrow+j] = _data[i*_nrow+j] - temp ;
							}
							if( (j < i) && (j != 0) ) {
								_T temp = 0 ;
								for(size_t k=0; k<=j-1; ++k) {
									temp +=
										lower._data[i*_nrow+k] * upper._data[k*_nrow+j] ;
								}
								lower._data[i*_nrow+j] =
									(_data[i*_nrow+j] - temp) / upper._data[j*_nrow+j] ;
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
				_det = 0 ;
				_singular = true ;
				_verify = false ;
			}
		}

		/**
		 * Resizes matrix to have r rows and c columns. Data
		 * is then deleted and reallocated to the new size.
		 * Data is not preserved at resizing a matrix!!
		 */
		inline void resize(const size_t& r, const size_t& c) {
			size_t N = r * c ;
			_nrow = r ;
			_ncol = c ;
			_verify = true ;
			_singular = false ;
			delete[] _data ;
			_data = new _T[N] ;
			memset(_data, 0, N*sizeof(_T)) ;
		}
		
		/**
		 * Swaps row a with row b.
		 */
		inline void swap_row(const size_t& r1, const size_t& r2) {
			_T temp ;
			for(size_t i=0; i<_ncol; ++i) {
				temp = _data[r1*_nrow+i];
				_data[r1*_nrow+i] = _data[r2*_nrow+i] ;
				_data[r2*_nrow+i] = temp ;
			}
			_verify = true ;
			_singular = false ;
		}
		
		/**
		 * Swaps column a with column b
		 */
		inline void swap_col(const size_t& c1, const size_t& c2) {
			_T temp ;
			for(size_t i=0; i<_nrow; ++i) {
				temp = _data[i*_nrow+c1] ;
				_data[i*_nrow+c1] = _data[i*_nrow+c2] ;
				_data[i*_nrow+c2] = temp ;
			}
			_verify = true ;
			_singular = false ;
		}
		
		/**
		 * Adds row r1 * x to row r2
		 */
		inline void add_row(const size_t& r1, 
							const size_t& r2, _T x=1 )
		{
			for(size_t i=0; i<_ncol; ++i) {
				_data[r2*_nrow+i] += _data[r1*_nrow+i] * x ;
			}
		}
		
		/**
		 * Adds column c1 * x to column c2
		 */
		inline void add_col(const size_t& c1, 
							const size_t& c2, _T x=1 )
		{
			for(size_t i=0; i<_nrow; ++i) {
				_data[i*_nrow+c2] += _data[i*_nrow+c1] * x ;
			}
		}
		
		/**
		 * Multiply a row by x
		 */
		inline void x_row(const size_t& r, _T x) {
			for(size_t i=0; i<_ncol; ++i) {
				_data[r*_nrow+i] *= x ;
			}
		}

		/**
		 * Multiply a column by x
		 */
		inline void x_col(const size_t& c, _T x) {
			for(size_t i=0; i<_nrow; ++i) {
				_data[i*_nrow+c] *= x ;
			}
		}
				
	/*================== Comparison Operators ==================*/
		inline bool operator== (matrix& rhs) {
			int n = memcmp( _data, rhs._data, 
						    sizeof(_T)*sizeof(_data) ) ;
			return ( _nrow == rhs._nrow &&
				 	 _ncol == rhs._ncol && n == 0 ) ;
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
			_nrow(nrow), _ncol(ncol),
			_singular(false), _verify(true)
		{
			size_t N = _nrow * _ncol ;
			_data = new _T[N] ;
			memset(_data, 0, N * sizeof(_T)) ;
		}

		/**
		 * Copy Constructor
		 */
		matrix(matrix& rhs) :
			_nrow(rhs._nrow), _ncol(rhs._ncol),
			_singular(rhs._singular), _verify(false),
			_det(rhs._det)
		{
			size_t N = _nrow * _ncol ;			
			_data = new _T[N] ;
			memcpy(_data, rhs._data, N * sizeof(_T)) ;
		}

		/**
		 * Assign Constructor
		 */
		inline matrix* operator= (matrix& rhs) {
			_nrow = rhs._nrow ;
			_ncol = rhs._ncol ;
			_verify = rhs._verify ;
			_singular = rhs._singular ;
			_det = rhs._det ;
			delete _data ;
			_data = rhs._data ;
			return this ;
		}
		
		/**
		 * Destructor
		 */
		~matrix() {
			delete[] _data ;
		}

/********************** IO Stream overloads ***********************/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

	private:
		_T* _data ;
		size_t _nrow ;
		size_t _ncol ;
		size_t _index ;
		bool _singular ;
		bool _verify ;
		_T _det ;


		/**
		 * Determine if the matrix is singular
		 * This function is used to determine if a matrix is singular
		 * by first looking to see if a zero row or column exists.
		 * If one exists, the _singular member variable is set to
		 * true and _det is set to zero.
		 * If a zero row/column is not found, the determinant of the
		 * matrix is then calculated and checked to be non-zero.
		 */		
		inline void singularity() {
			if( _verify ) {

				if( _nrow != _ncol ) {
					_det = 0 ;
					_singular = true ;
				}

				// check for a zero row
				if( !_singular ) {
					for(size_t i=0; i<_nrow; ++i) {
						bool _zero = false ;
						if( _data[i*_nrow+0] == 0 ) {
							for(size_t j=1; j<_ncol; ++j) {
								if( _data[i*_nrow+j] != 0 ) {
									_zero = false ;
									break ;
								} else {
									_zero = true ;
								}
							}
						}
						if( _zero ) {
							_singular = true ;
							_det = 0 ;
							break ;
						}
					}
				}

				// check for a zero column
				if( !_singular ) {
					for(size_t i=0; i<_ncol; ++i) {
						bool _zero = false ;
						if( _data[i] == 0 ) {
							for(size_t j=1; j<_nrow; ++j) {
								if( _data[j*_nrow+i] == 0 ) {
									_zero = true ;
								} else {
									_zero = false ;
									break ;
								}
							}
						}
						if( _zero ) {
							_singular = true ;
							_det = 0 ;
							break ;
						}
					}
				}

				// check for determinant equals zero and for matrices
				// of int types, determinant must be 1 or -1 otherwise
				// matrix is singular
				if( !_singular ) {
					determinant() ;
					_T zero = _det ;
					if( zero == 0 ) {
						_singular = true ;
					} else {
						if( typeid(_T) == typeid(int) ) {
							if( zero == 1 || zero == -1 ) {
								_singular = false ;
							} else {
								_singular = true ;
							}
						} else {
							_singular = false ;
						}
					}
				}
				
				_verify = false ;
			}
		}

		/**
		 * Calculates the determinant of the matrix. If the determinant
		 * is returned as zero, _singular flag is set to true. 
		 * Otherwise it is set to true. In both cases the _verify
		 * flag is then set to false.
		 */
		inline void determinant() {
			_det = determinant(_data, _ncol) ;
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
	os << "\nrows: " << output._nrow << "   det:   " << output.det() 
	   << "\ncols: " << output._ncol ;
	if( output._singular ) {
		os << "   singular" << endl ;
	} else {
		os << "   non-singular" << endl ;
	}
	for(size_t i=0; i<output._nrow; ++i) {
		os << "| " ;
		for(size_t j=0; j<output._ncol; ++j) {
			char buf[32];
            _T data = output._data[i*output._nrow+j];
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
