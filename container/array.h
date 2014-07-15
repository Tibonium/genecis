/**
 * @file array.h
 */

#ifndef GENECIS_CONTAINER_ARRAY_H
#define GENECIS_CONTAINER_ARRAY_H

#include <iostream>

namespace genecis {
namespace container {

template <class _T> class array ;

template <class _T> std::ostream&
operator<< (std::ostream& os, array<_T>& a) ;

template <class _T>
class array {

	public:
	
		// Constructor
		array(size_t t) {
			_a = new _T[t] ;
			memset(_a, 0, t) ;
			_s = t ;
		}
		
		// Destructor
		~array() {
			if( _a ) {
				delete[] _a ;
				_a = NULL ;
			}
		}

		inline size_t size() {
			return _s ;
		}
		
		inline _T& operator() (size_t t) {
			return _a[t] ;
		}
		
		template<typename _index>
		inline void operator= (_T c) {
			_a[_index] = c ;
		}
		
	friend std::ostream& operator<< <>
		(std::ostream& os, array& a) ;
	
	private:
		_T* _a ;
		size_t _s ;
};

template <class _T>
inline std::ostream& operator<< 
	(std::ostream& os, array<_T>& a)
{
	os << "[" << a.size() << "]: {" ;
	for(size_t i=0; i<a.size(); ++i) {
		os << a(i) ;
		(i!=(a.size()-1)) ? os << "," :
			os << "}" ;
	}
	return os ;
}

}	// end namespace container
}	// end namespace genecis

#endif
