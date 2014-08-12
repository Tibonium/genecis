/**
 * @file array.h
 */

#ifndef GENECIS_CONTAINER_ARRAY_H
#define GENECIS_CONTAINER_ARRAY_H

#include <iostream>
#include <cstddef>
#include "../base/genecis_reverse_iterator.h"

namespace genecis {
namespace container {

using namespace genecis::base ;

template <class _T> class array ;

template <class _T> std::ostream&
operator<< (std::ostream& os, array<_T>& a) ;

template<class _T> class array {

	public:
	
		typedef array<_T>			self_type ;
		typedef std::allocator<_T>  allocator_type ;
		typedef _T					value_type ;
		typedef _T *				pointer ;
		typedef const _T *			const_pointer ;
		typedef ptrdiff_t			difference_type ;
		typedef _T &				reference ;
		typedef const _T &			const_reference ;
		typedef size_t				size_type ;
		typedef value_type*		iterator ;
		typedef const value_type*		const_iterator ;
		typedef genecis_reverse_iterator<iterator>	reverse_iterator ;
		typedef genecis_reverse_iterator<const_iterator> const_reverse_iterator ;
	
		/**
		 * Constructs an array of type _T with size specificed and
		 * fills the array with the value c or zeros.
		 */
		array(size_type s, const value_type& c=0) {
			create_storage( s ) ;
			fill_n(__begin, s, c) ;
		}
		
		/**
		 * Destructor
		 */
		virtual ~array() {
			allocator_type d ;
			d.deallocate( __begin, size() ) ;
		}
		
	/**** Iterators ****/
		/**
		 * Provides a pointer to the beginning of the data stored
		 * in this class.
		 */
		iterator begin() {
			return iterator( __begin ) ;
		}
		
		/**
		 * Provides a pointer to the end of the data stored in this
		 * class 
		 */
		iterator end() {
			return iterator( __end ) ;
		}
		
		/**
		 * Provides a const pointer to the beginning of the data
		 * stored in this class 
		 */
		const_iterator cbegin() const {
			return const_iterator( begin() ) ;
		}
		
		/**
		 * Provides a const pointer to the end of the data stored
		 * in this class 
		 */
		const_iterator cend() const {
			return const_iterator( end() ) ;
		}
		
		/**
		 * Provides a pointer to the end of the data stored in this
		 * class 
		 */
		reverse_iterator rbegin() {
			return reverse_iterator( end() ) ;
		}
		
		/**
		 * Provides a pointer to the beginning of the data
		 * stored in this class 
		 */
		reverse_iterator rend() {
			return reverse_iterator( begin() ) ;
		}
		
		/**
		 * Provides a const pointer to the end of the data stored
		 * in this class 
		 */
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator( end() ) ;
		}
		
		/**
		 * Provides a const pointer to the beginning of the data
		 * stored in this class 
		 */
		const_reverse_iterator crend() const {
			return const_reverse_iterator( begin() ) ;
		}

		/**
		 * Returns the number of elements in the data array
		 */
		size_type size() {
			return size_type( __end - __begin ) ;
		}

		size_type size() const {
			return size_type( __end - __begin ) ;
		}

		/**
		 * Returns a pointer to the beginning of the stored data
		 * in the class
		 */
		pointer data() {
			return __begin ;
		}

		const_pointer data() const {
			return __begin ;
		}
		
		/**
		 * Element accessor
		 */
		reference operator() (size_type t) {
			return *( __begin + t ) ;
		}
		
		const_reference operator() (size_type t) const {
			return *( __begin + t ) ;
		}
		
		/**
		 * Element assignment
		 */
		template<int _index>
		void operator= (value_type c) {
			*( __begin + _index ) = c ;
		}
		
		/**
		 * Output format
		 */
		friend std::ostream& operator<< <>
			(std::ostream& os, array& a) ;
	
	private:
		// begin and end of the data stored in this class
		iterator __begin ;
		iterator __end ;
		
		void create_storage(size_type __n) {
			allocator_type tmp ;
			__begin = tmp.allocate( __n ) ;
			__end = __begin + __n ;
		}

};

template <class _T>
inline std::ostream& operator<< (std::ostream& os, array<_T>& a)
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
