/**
 * @file dynamic_array.h
 */

#ifndef GENECIS_CONTAINER_DYNAMIC_ARRAY_H
#define GENECIS_CONTAINER_DYNAMIC_ARRAY_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>

namespace genecis {
namespace container {

using namespace std ;

template<class _T>
class dynamic_array {

	public:
		/**
		 * Constructor with specified size.
		 * @param size		size of array to be allocated
		 */
		dynamic_array(size_t size) : __size(size) {
			__data = new _T[__size] ;
			memset( __data, 0, size*sizeof(_T) ) ;
		}
		
		/**
		 * Default constructor, intializes array size to default_size
		 */
		dynamic_array() : __size(DEFAULT_SIZE) {
			__data = new _T[__size] ;
			memset( __data, 0, __size*sizeof(_T) ) ;
		}
		
		/**
		 * Copy constructor
		 */
		dynamic_array(dynamic_array const& other) {
			__size = other.size() ;
			__data = new _T[__size] ;
			memcpy( __data, other.data(), __size*sizeof(_T) ) ;
		}

		/**
		 * Destructor
		 */
		virtual ~dynamic_array() {
			if( __data ) {
				delete[] __data ;
				__data = NULL ;
			}
		}

		/**
		 * Returns the maximum capacity of the data array.
		 */
		int size() {
			return __size ;
		}
		
		int size() const {
			return __size ;
		}
		
		/**
		 * Returns a pointer to the data array of the class.
		 */
		_T* data() {
			return __data ;
		}
		
		_T* data() const {
			return __data ;
		}
		
		/**
		 * Returns a string of the array in the format of:
		 * [ e1, e2, e3, ... ]
		 */
		string str() const {
			string s = "[ " ;
			for(size_t i=0; i<__size; ++i) {
				ostringstream o ;
				if ( i != 0 ) s += ", " ;
				o << __data[i] ;
				s += o.str() ;
			}
			s += " ]" ;
			return s ;
		}

		/** ===== Array Operators ===== **/

		/**
		 * Concatenates two dynamic arrays and passes back a new
		 * dynamic array.
		 */
		dynamic_array operator+(dynamic_array& rhs) {
			int temp_size = __size + rhs.size() ;
			dynamic_array<_T>* temp = new dynamic_array<_T>(temp_size) ;
			for(size_t i=0; i<__size; ++i) {
				(*temp)(i) = (*this)(i) ; 
			}
			for(int i=__size; i<temp_size; ++i) {
				(*temp)(i) = rhs(i-__size) ;
			}
			return (*temp) ;
		}
		
		/**
		 * Concatenates this array with the rhs into this array.
		 */
		void operator+=(dynamic_array const& rhs) {
			int temp_size = __size + rhs.size() ;
			dynamic_array<_T>* temp = new dynamic_array<_T>(temp_size) ;
			for(size_t i=0; i<__size; ++i) {
				(*temp)(i) = (*this)(i) ; 
			}
			for(int i=__size; i<temp_size; ++i) {
				(*temp)(i) = rhs(i-__size) ;
			}
			delete[] __data ;
			__size = temp_size ;
			__data = temp->data() ;
		}
		
		/**
		 * Class assignment operator
		 */
		void operator=(dynamic_array const& rhs) {
			delete[] __data ;
			__size = rhs.size() ;
			__data = new _T[__size] ;
			memcpy( __data, rhs.data(), __size*sizeof(_T) ) ;
		}
		
		/**
		 * Array accessor
		 * If index is out of bounds, the array with do one of two
		 * things:
		 *	1. If index is positive, _data will be expanded to that size
		 *	2. If index is negative, _data will be accessed from the end
		 *	   in reverse order.
		 */
		_T& operator() (size_t index) {
			if( index > __size-1 ) {
				resize(index+1) ;
			} else if ( index < 0 ) {
				index += __size ;
			}
			return __data[index] ;
		}
		
		/**
		 * Array assignment operator
		 */
		template<size_t _index>
		void operator= (_T c) {
			__data[_index] = c ;
		}

	private:
		/**
		 * Default array size for default constructor
		 */
		static const int DEFAULT_SIZE = 5 ;

		/**
		 * Maximum size of the array
		 */
		size_t __size ;
		
		/**
		 * Pointer to the data stored in the dynamic_array
		 */
		_T* __data ;
		
		/**
		 * Resizes the data array to prevent the array from going
		 * out of bounds when the index is larger then the size of
		 * the array.
		 */
		void resize(const int& new_size) {
			_T* n_data = new _T[new_size] ;
			memset( n_data, 0, new_size*sizeof(_T) ) ;
			memcpy( n_data, __data, __size*sizeof(_T) ) ;
			delete[] __data ;
			__data = n_data ;
			__size = new_size ;
		}

};

}	// end of namespace container
}	// end of namespace genecis

#endif
