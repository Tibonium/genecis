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
	
		typedef _T						value_type ;
		typedef _T *					pointer ;
		typedef ptrdiff_t				difference_type ;
		typedef _T &					reference ;
		typedef const _T &				const_reference ;
		typedef size_t					size_type ;
		typedef pointer 				iterator ;
		typedef const pointer			const_iterator ;
		typedef pointer					reverse_iterator ;
		typedef const pointer			const_reverse_iterator ;
	
		/**
		 * Constructs an array of type _T with size specificed and
		 * fills the array with the value c or zeros.
		 */
		array(size_type s, const value_type& c=0)
				: __size(s)
		{
			__data = new value_type[__size] ;
			fill_n(__data, __size, c) ;
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
		
	/**** Iterators ****/
		/**
		 * Provides a pointer to the beginning of the data stored
		 * in this class.
		 */
		iterator begin() {
			return &__data[0] ;
		}
		
		/**
		 * Provides a pointer to the end of the data stored in this
		 * class 
		 */
		iterator end() {
			return &__data[__size] ;
		}
		
		/**
		 * Provides a const pointer to the beginning of the data
		 * stored in this class 
		 */
		const_iterator begin() const {
			return &__data[0] ;
		}
		
		/**
		 * Provides a const pointer to the end of the data stored
		 * in this class 
		 */
		const_iterator end() const {
			return &__data[__size] ;
		}
		
		/**
		 * Provides a pointer to the end of the data stored in this
		 * class 
		 */
		reverse_iterator rbegin() {
			return &__data[__size] ;
		}
		
		/**
		 * Provides a pointer to the beginning of the data
		 * stored in this class 
		 */
		reverse_iterator rend() {
			return &__data[0] ;
		}
		
		/**
		 * Provides a const pointer to the end of the data stored
		 * in this class 
		 */
		const_reverse_iterator rbegin() const {
			return &__data[__size] ;
		}
		
		/**
		 * Provides a const pointer to the beginning of the data
		 * stored in this class 
		 */
		const_reverse_iterator rend() const {
			return &__data[0] ;
		}

		/**
		 * Returns the number of elements in the data array
		 */
		size_type size() {
			return __size ;
		}

		size_type size() const {
			return __size ;
		}

		/**
		 * Returns a pointer to the data array in the class
		 */
		value_type* data() {
			return __data ;
		}

		value_type* data() const {
			return __data ;
		}
		
		/**
		 * Element accessor
		 */
		value_type& operator() (size_type t) {
			return __data[t] ;
		}
		
		value_type& operator() (size_type t) const {
			return __data[t] ;
		}
		
		/**
		 * Element assignment
		 */
		template<int _index>
		void operator= (value_type c) {
			__data[_index] = c ;
		}
		
		/**
		 * Output format
		 */
		friend std::ostream& operator<< <>
			(std::ostream& os, array& a) ;
	
	private:
		// Data array
		value_type* __data ;
		// size of array
		size_type __size ;

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
