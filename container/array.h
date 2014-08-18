/**
 * @file array.h
 */

#ifndef GENECIS_CONTAINER_ARRAY
#define GENECIS_CONTAINER_ARRAY

#include "container_io.h"

namespace genecis {
namespace container {

	template<class _T>
	class array : public container_expression<array, _T> {

		public:
	
			typedef array<_T>								 					self_type ;
			typedef std::allocator<_T>  					 					allocator_type ;
			typedef typename container_expression<array,_T>::value_type			value_type ;
			typedef typename container_expression<array,_T>::pointer			pointer ;
			typedef typename container_expression<array,_T>::const_pointer		const_pointer ;
			typedef typename container_expression<array,_T>::difference_type	difference_type ;
			typedef typename container_expression<array,_T>::reference			reference ;
			typedef typename container_expression<array,_T>::const_reference	const_reference ;
			typedef typename container_expression<array,_T>::size_type  		size_type ;
			typedef typename container_expression<array,_T>::iterator			iterator ;
			typedef typename container_expression<array,_T>::const_iterator		const_iterator ;
			typedef typename container_expression<array,_T>::reverse_iterator	reverse_iterator ;
			typedef typename container_expression<array,_T>::reverse_iterator 	const_reverse_iterator ;

			/**
			 * Empty constructor
			 */
			array() : __begin(0), __end(0) {}

			/**
			 * Constructs an array of type _T with size specificed and
			 * fills the array with the value c or zeros.
			 */
			array(size_type s, const value_type& c=0) {
				create_storage( s ) ;
				std::fill_n(__begin, s, c) ;
			}
		
			/**
			 * Copy constructor
			 */
			array(array<value_type>& other) {
				this->create_storage( other.size() ) ;
				std::copy( other.begin(), other.end(), __begin ) ;
			}
		
			/**
			 * Assignment operator
			 */
			void operator=(array<value_type>& rhs) {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
				this->create_storage( rhs.size() ) ;
				std::copy( rhs.begin(), rhs.end(), __begin ) ;
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

}	// end namespace container
}	// end namespace genecis

#endif
