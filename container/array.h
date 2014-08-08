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
		array(size_t s, const _T& c=0) {
			__data = new _T[s] ;
			fill_n(__data, s, c) ;
			__size = s ;
		}
		
		/**
		 * Destructor
		 */
		virtual ~array() {
			if( __data ) {
				delete[] __data ;
				__data = NULL ;
			}
		}

		/**
		 * Returns the number of elements in the data array
		 */
		size_t size() {
			return __size ;
		}

		size_t size() const {
			return __size ;
		}

		/**
		 * Returns a pointer to the data array in the class
		 */
		_T* data() {
			return __data ;
		}

		_T* data() const {
			return __data ;
		}
		
		/**
		 * Element accessor
		 */
		_T& operator() (size_t t) {
			return __data[t] ;
		}
		
		_T& operator() (size_t t) const {
			return __data[t] ;
		}
		
		/**
		 * Element assignment
		 */
		template<int _index>
		void operator= (_T c) {
			__data[_index] = c ;
		}
		
		/**
		 * Output format
		 */
		friend std::ostream& operator<< <>
			(std::ostream& os, array& a) ;
	
	private:
		// Data array
		_T* __data ;
		// size of array
		size_t __size ;
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
