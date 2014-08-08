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
	
		/**
		 * Constructs an array of type _T with size specificed and
		 * fills the array with the value c or zeros.
		 */
		array(size_t t, const _T& c=0) {
			_a = new _T[t] ;
			fill_n(_a, t, c) ;
			_s = t ;
		}
		
		/**
		 * Destructor
		 */
		virtual ~array() {
			if( _a ) {
				delete[] _a ;
				_a = NULL ;
			}
		}

		/**
		 * Returns the number of elements in the data array
		 */
		size_t size() const {
			return _s ;
		}

		/**
		 * Returns a pointer to the data array in the class
		 */
		_T* data() const {
			return _a ;
		}
		
		/**
		 * Element accessor
		 */
		_T& operator() (size_t t) {
			return _a[t] ;
		}
		
		/**
		 * Element assignment
		 */
		template<int _index>
		void operator= (_T c) {
			_a[_index] = c ;
		}
		
		/**
		 * Output format
		 */
		friend std::ostream& operator<< <>
			(std::ostream& os, array& a) ;
	
	private:
		// Data array
		_T* _a ;
		// size of array
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
