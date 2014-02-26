/**
 * @file new matrix class
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std ;

template<class _type> class matrix ;

template<class _type>
std::ostream& operator<< (std::ostream& os, matrix<_type>& output) ;

template<class _type> class matrix {

		typedef matrix<_type> self_type ;
	private:
		unsigned _nrow ;
		unsigned _ncol ;
		unsigned _index ;
		_type* _data ;

	public:
		/** Member Functions **/
		inline unsigned nrow() {
			return _nrow ;
		}
		
		inline unsigned ncol() {
			return _ncol ;
		}
		
		inline _type* data() {
			return _data ;
		}

		/****************** ===Operators=== ***********************/
		/* Accessor and Assigner */
		inline _type& operator() (unsigned i, unsigned j) {
			_index = i * _ncol + j ;
			return _data[_index] ;
		}

		inline void operator= (_type value) {
			_data[_index] = value ;
		}
		
		/* Scalar Operators */
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
		
		/* Matrix Operators */
		inline matrix<_type>* operator* (matrix<_type>& other) {
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
					return temp ;
				}
			} catch (int e) {
				cout << "Matrices cannot be multiplied.  "
				     << "A ncol(" << _ncol << ") must equal B nrow("
					<< other.nrow() << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline void operator*= (matrix<_type>& other) {
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
					*this = *temp ;
				}
			} catch (int e) {
				cout << "Matrices cannot be multiplied.  "
				     << "A ncol(" << _ncol << ") must equal B nrow("
					<< other.nrow() << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline void transpose() {
			matrix<_type>* temp = new matrix<_type>(_ncol,_nrow) ;
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					(*temp)(j,i) = (*this)(i,j) ;
				}
			}
			*this = *temp ;
		}

		inline void operator^ (int exp) {
			try {
				if(_ncol != _nrow) {
					throw 1 ;
				} else {
					if(exp < 0) {
						if(exp == -1) {
							cout << "take inverse of function" << endl ;
						} else {
							cout << "do some other negative power > 1" << endl ;
						}
					} else if(exp == 0) {
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
		
		/* Comparison Operators */
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
		
		/**
		 * Constructor
		 * Creates an NxM matrix from a basic array
		 * Defaults to a 1x1 matrix
		 */
		matrix(unsigned nrow=1, unsigned ncol=1) : 
			_nrow(nrow), _ncol(ncol) 
		{
			size_t N = _nrow * _ncol ;
			_data = new _type[N] ;
		}
		
		/**
		 * Copy Constructor
		 */
		matrix(matrix<_type>& other) :
			_nrow(other.nrow()), _ncol(other.ncol())
		{
			size_t N = _nrow * _ncol ;			
			_data = new _type[N] ;
			memcpy(_data, other.data(), N * sizeof(_type)) ;
		}
		
		/**
		 * Other Copy constructor
		 */
		inline matrix<_type>& operator= (matrix<_type>& other) {
			_nrow = other.nrow() ;
			_ncol = other.ncol() ;
			_data = other.data() ;
			return *this ;
		}

		/** IO Stream overloads **/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

};

template <class _type>
inline std::ostream& operator<< (std::ostream& os, matrix<_type>& output) {
	os << "[" << output.nrow() << "," << output.ncol() << "]: {" ;
	for(unsigned i=0; i<output.nrow(); ++i) {
		os << "[" ;
		for(unsigned j=0; j<output.ncol(); ++j) {
			os << output(i,j) ;
			(j!=output.ncol()-1) ? os << " " : os << "" ;
		}
		os << "]" ;
		(i!=output.nrow()-1) ? os << "," : os << "}" ;
	}
	return os ;
}

#endif
