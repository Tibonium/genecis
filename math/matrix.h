/**
 * @file new matrix class
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
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
		matrix(const matrix& other) :
			_nrow(other.nrow), _ncol(other.ncol)
		{
			size_t N = _nrow * _ncol ;			
			_data = new _type[N] ;
			memcpy(_data, other.data, N * sizeof(_type)) ;
		}

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
