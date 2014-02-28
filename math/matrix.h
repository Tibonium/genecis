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

template<class _type> class matrix ;

template<class _type>
std::ostream& operator<< (std::ostream& os, matrix<_type>& output) ;

template<class _type> class matrix {

		typedef matrix<_type> self_type ;

	public:
		inline unsigned nrow() {
			return _nrow ;
		}

		inline unsigned ncol() {
			return _ncol ;
		}

		inline bool singular() {
			return _singular ;
		}
		
		inline _type det() {
			if ( _verify ) {
				singularity() ;
			}
			return _det ;
		}
		
		inline _type* data() {
			return _data ;
		}

/************************* Operators ******************************/
		/* Accessor and Assigner */
		inline _type& operator() (unsigned i, unsigned j) {
			_index = i * _ncol + j ;
			return _data[_index] ;
		}

		inline void operator= (_type value) {
			_verify = true ;
			_data[_index] = value ;
		}

	/*================= Matrix Scalar Operators ================*/
		inline matrix<_type>& operator* (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] *= value ;
				}
			}
			return *this ;
		}

		inline void operator*= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] *= value ;
				}
			}
		}

		inline matrix<_type>& operator/ (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] /= value ;
				}
			}
			return *this ;
		}

		inline void operator/= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] /= value ;
				}
			}
		}

		inline matrix<_type>& operator+ (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] += value ;
				}
			}
			return *this ;
		}

		inline void operator+= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] += value ;
				}
			}
		}

		inline matrix<_type>& operator- (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] -= value ;
				}
			}
			return *this ;
		}

		inline void operator-= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] -= value ;
				}
			}
		}

		inline matrix<_type>& operator% (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] %= value ;
				}
			}
			return *this ;
		}

		inline void operator%= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] %= value ;
				}
			}
		}

	/*================ Matrix Matrix Operators =================*/
		inline matrix<_type>& operator* (matrix<_type>& other) {
			try {
				if( _ncol != other.nrow() ) {
					throw 1;
				} else {
					matrix<_type>* temp = new matrix<_type>(_nrow,other.ncol()) ;
					_type value = 0 ;
					for(unsigned n=0; n<temp->nrow(); ++n) {
						for(unsigned m=0; m<temp->ncol(); ++m) {
							for(unsigned i=0; i<_ncol; ++i) {
								value += (*this)(n,i) * other(i,m) ;
							}
							(*temp)(n,m) = value ;
							value = 0 ;
						}
					}
					return *temp ;
				}
			} catch (int e) {
				cout << "matrix::operator*: A ncol(" << _ncol
					 << ") must equal B nrow(" << other.nrow()
					 << ")." << endl ;
				exit(e) ;
			}
		}

		inline void operator*= (matrix<_type>& other) {
			try {
				if( _ncol != other.nrow() ) {
					throw 1;
				} else {
					matrix<_type> temp = *this ;
					*this = temp * other ;
					this->_verify = true ;
					this->singularity() ;
				}
			} catch (int e) {
				cout << "matrix::operator*=: A ncol(" << _ncol
					 << ") must equal B nrow(" << other.nrow()
					 << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline matrix<_type>& operator+ (matrix<_type>& other) {
			try {
				if( _nrow != other.nrow() || _ncol != other.ncol() ) {
					throw 1 ;
				} else {
					matrix<_type>* temp = new matrix<_type>(_nrow,other.ncol()) ;
					for(unsigned i=0; i<_nrow; ++i) {
						for(unsigned j=0; j<_ncol; ++j) {
							(*temp)(i,j) = (*this)(i,j) + other(i,j) ;
						}
					}
					return *temp ;
				}
			} catch (int e) {
				cout << "matrix::operator+: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << other << endl ;
				exit(e) ;
			}
		}
		
		inline void operator+= (matrix<_type>& other) {
			try {
				if( _nrow != other.nrow() || _ncol != other.ncol() ) {
					throw 1 ;
				} else {
					matrix<_type> temp = *this ;
					*this = temp + other ;
					_verify = true ;
				}
			} catch (int e) {
				cout << "matrix::operator+=: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << other << endl ;
				exit(e) ;
			}
		}
		
		inline void operator/ (matrix<_type>& other) {
			cout << "matrix::operator/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		inline void operator/= (matrix<_type>& other) {
			cout << "matrix::operator=/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		/**
		 * Mutates the matrix into its transpose.
		 */
		inline void transpose() {
			matrix<_type>* temp = new matrix<_type>(_ncol,_nrow) ;
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					(*temp)(j,i) = (*this)(i,j) ;
				}
			}
			*this = *temp ;
			temp->_data = NULL ;
			delete temp ;
		}
		
		/**
		 * Mutates the passed in matrix into the transpose of the
		 * matrix that called this function. The calling matrix
		 * remains unaltered.
		 */
		inline void transpose(matrix<_type>& m_trans) {
			m_trans.resize(_ncol, _nrow) ;
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					m_trans(j,i) = (*this)(i,j) ;
				}
			}
		}
		
		/**
		 * Mutates the calling matrix into its inverse, if it exists.
		 * Otherwise an exit status is passed and the program ends.
		 */
		inline matrix<_type>& inverse() {
			try {
				singularity() ;
				if( _singular || _det == 0 ) {
					throw 1 ;
				} else {
					matrix<_type>* inv_mtx = this ;
					cout << "something" << endl ;
					return *inv_mtx ;
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
						matrix<_type> temp = *this ;
						while(i < exp) {
							*this *= temp ;
							++i ;
						}
					}
				}
			} catch(int e) {
				cout << "matrix<_type>::operator^ "
					<< "only valid for square matrices." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		inline void lu_decomp(matrix<_type>& upper, matrix<_type>& lower) {
			try {
				if( _nrow != _ncol ) {
					throw -1 ;
				} else {
					upper.resize(_nrow, _ncol) ;
					lower.resize(_nrow, _ncol) ;
					for(unsigned i=0; i<_nrow; ++i) {
						for(unsigned j=0; j<_ncol; ++j) {
							if( i == 0 ) upper(i,j) = (*this)(i,j) ;
							if( i == j ) lower(i,j) = 1 ;
							if( (i != 0) && (j == 0) ) {
								lower(i,j) = (*this)(i,0) / upper(0,0) ;
							}
							if( (j >= i) && (i != 0) ) {
								_type temp = 0 ;
								for(unsigned k=0; k<i-1; ++k) {
									temp += lower(i,k) * upper(k,j) ;
								}
								upper(i,j) = (*this)(i,j) - temp ;
							}
							if( (j < i) && (j != 0) ) {
								_type temp = 0 ;
								for(unsigned k=0; k<j-1; ++k) {
									temp += lower(i,k) * upper(k,j) ;
								}
								lower(i,j) = ((*this)(i,j) - temp) / upper(j,j) ;
							}
						}
					}
					cout << "matrix::lu_decomp: Decompose the matrix into "
						 << "an upper and lower triangular matrix."
						 << endl ;
				}
			} catch (int e) {
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
		inline void resize(const unsigned& r, const unsigned& c) {
			size_t N = r * c ;
			this->_nrow = r ;
			this->_ncol = c ;
			delete this->_data ;
			this->_data = new _type[N] ;
			memset(this->_data, 0, N*sizeof(_type)) ;
		}
		
		/**
		 * Swaps row a with row b.
		 */
		inline void swap_row(const unsigned& r1, const unsigned& r2) {
			_type temp ;
			for(unsigned i=0; i<_ncol; ++i) {
				temp = (*this)(r1,i) ;
				(*this)(r1,i) = (*this)(r2,i) ;
				(*this)(r2,i) = temp ;
			}
		}
		
		/**
		 * Swaps column a with column b
		 */
		inline void swap_col(const unsigned& c1, const unsigned& c2) {
			_type temp ;
			for(unsigned i=0; i<_nrow; ++i) {
				temp = (*this)(i,c1) ;
				(*this)(i,c1) = (*this)(i,c2) ;
				(*this)(i,c2) = temp ;
			}
		}
		
		/**
		 * Adds row r1 * x to row r2
		 */
		inline void add_row(const unsigned& r1, 
							const unsigned& r2, _type x=1 )
		{
			for(unsigned i=0; i<_ncol; ++i) {
				(*this)(r2,i) += (*this)(r1,i) * x ;
			}
		}
		
		/**
		 * Adds column c1 * x to column c2
		 */
		inline void add_col(const unsigned& c1, 
							const unsigned& c2, _type x=1 )
		{
			for(unsigned i=0; i<_nrow; ++i) {
				(*this)(i,c2) += (*this)(i,c1) * x ;
			}
		}
		
		/**
		 * Multiply a row by x
		 */
		inline void x_row(const unsigned& r, _type x) {
			for(unsigned i=0; i<_ncol; ++i) {
				(*this)(r,i) *= x ;
			}
		}

		/**
		 * Multiply a column by x
		 */
		inline void x_col(const unsigned& c, _type x) {
			for(unsigned i=0; i<_nrow; ++i) {
				(*this)(i,c) *= x ;
			}
		}
				
	/*================== Comparison Operators ==================*/
		inline bool operator== (matrix<_type>& other) {
			int n = memcmp( _data, other.data(), 
						    sizeof(_type)*sizeof(_data) ) ;
			if ( _nrow == other.nrow() &&
				 _ncol == other.ncol() && n == 0 )
			{
				return true ;
		 	} else {
		 		return false ;
		 	}
		}

		inline bool operator!= (matrix<_type>& other) {
			return !(*this==other) ;
		}

/******************** Constructor/Destructors *********************/
		/**
		 * Main  Constructor
		 * Creates an NxM matrix from a basic array
		 * Defaults to a 1x1 matrix
		 */
		matrix(unsigned nrow=1, unsigned ncol=1) : 
			_nrow(nrow), _ncol(ncol)
		{
			size_t N = _nrow * _ncol ;
			_data = new _type[N] ;
			memset(_data, 0, N * sizeof(_type)) ;
//			if( _nrow != _ncol ) {
//				_singular = true ;
//				_det = 0 ;
//				_verify = false ;
//			} else {
//				_verify = true ;
//			}
		}

		/**
		 * Copy Constructor
		 */
		matrix(matrix<_type>& other) :
			_nrow(other.nrow()), _ncol(other.ncol()),
			_singular(other.singular()), _det(other.det())
		{
			size_t N = _nrow * _ncol ;			
			_data = new _type[N] ;
			_verify = false ;
			memcpy(_data, other.data(), N * sizeof(_type)) ;
		}

		/**
		 * Assign Constructor
		 */
		inline matrix<_type>& operator= (matrix<_type>& other) {
			_nrow = other.nrow() ;
			_ncol = other.ncol() ;
			_verify = true ;
			_singular = false ;
			delete _data ;
			_data = other.data() ;
			return *this ;
		}
		
		/**
		 * Destructor
		 */
		~matrix<_type>() {
			if( _data != NULL ) {
				delete _data ;
			}
		}

/********************** IO Stream overloads ***********************/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

	private:
		unsigned _nrow ;
		unsigned _ncol ;
		unsigned _index ;
		bool _singular ;
		bool _verify ;
		_type _det ;
		_type* _data ;


		/**
		 * Determine if the matrix is singular
		 * This function is used to determine if a matrix is singular
		 * by first looking to see if a zero row or column exists.
		 * If one exists, the _singular member variable is set to
		 * true and _det is set to zero.
		 * If a zero row/column is not found, the determinant of the
		 * matrix is then calculated and checked to be non-zero.
		 *
		 * This function only checks for singular-ness when either
		 * a data value is altered, such as populating a matrix
		 */		
		inline void singularity() {
			if( _verify ) {

				if( _nrow != _ncol ) {
					_det = 0 ;
					_singular = true ;
				}

				// check for a zero row
				if( !_singular ) {
					for(unsigned i=0; i<_nrow; ++i) {
						bool _zero = false ;
						if( (*this)(i,0) == 0 ) {
							for(unsigned j=1; j<_ncol; ++j) {
								if( (*this)(i,j) != 0 ) {
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
					for(unsigned i=0; i<_ncol; ++i) {
						bool _zero = false ;
						if( (*this)(0,i) == 0 ) {
							for(unsigned j=1; j<_nrow; ++j) {
								if( (*this)(j,i) == 0 ) {
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
					_type zero = _det ;
					if( zero == 0 ) {
						_singular = true ;
					} else {
						if( typeid(_type) == typeid(int) ) {
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
		
		inline _type determinant(const _type* data, const unsigned& n) {
			_type result = 0 ;
			_type* temp = new _type[n*n] ;
			if( n == 1 ) {
				delete temp ;
				return data[0] ;
			} else if( n == 2 ) {
				delete temp ;
				return (data[0]*data[3]-data[1]*data[2]) ;
			} else {
				for(unsigned p=0; p<n; ++p) {
					unsigned h = 0 ;
					unsigned k = 0 ;
					for(unsigned i=1; i<n; ++i) {
						for(unsigned j=0; j<n; ++j) {
							if( j == p ) continue ;
							temp[h*n+k] = data[i*n+j] ;
							++k ;
							if( k == n ) { ++h ; k = 0 ;}
						}
					}
					result += data[0+p]*pow(-1,p)*determinant(temp, n-1) ;
				}
				delete temp ;
				return result ;
			}
		}

};

template <class _type>
inline std::ostream& operator<< (std::ostream& os, matrix<_type>& output) {
	os << "\nrows: " << output.nrow() << "   det:   " << output.det() 
	   << "\ncols: " << output.ncol() ;
	if( output._singular ) {
		os << "   singular" << endl ;
	} else {
		os << "   non-singular" << endl ;
	}
	for(unsigned i=0; i<output.nrow(); ++i) {
		os << "| " ;
		for(unsigned j=0; j<output.ncol(); ++j) {
			char buf[32];
            _type data = output(i,j);
            if( typeid(_type) == typeid(int) ) {
            	if( data >= 1e5 ) {
            		sprintf(buf, "%1.1e ", (double)data) ;
            	} else {
        			sprintf(buf, "%7d ", (int)data) ;
        		}
            } else {
            	if( (abs(data) >= 1e10) || (abs(data) <= 1e-4) ) {
            		sprintf(buf, "%10.3e ", (double)data) ;
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
