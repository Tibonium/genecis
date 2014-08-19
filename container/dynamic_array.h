/**
 * @file dynamic_array.h
 */

#ifndef GENECIS_CONTAINER_DYNAMIC_ARRAY
#define GENECIS_CONTAINER_DYNAMIC_ARRAY

#include "container_io.h"

namespace genecis {
namespace container {

	template<class T> class dynamic_array :
			public container_expression<dynamic_array<T> > {

		public:

			typedef dynamic_array<T>	self_type ;
			typedef std::allocator<T>	allocator_type ;
			typedef T			 		value_type ;
			typedef T*				  	pointer ;
			typedef const T*		  	const_pointer ;
			typedef ptrdiff_t		  	difference_type ;
			typedef value_type&			reference ;
			typedef const value_type&	const_reference ;
			typedef size_t  			size_type ;
			typedef pointer			  	iterator ;
			typedef const_pointer		const_iterator ;
			typedef genecis_reverse_iterator<iterator>
				reverse_iterator ;
			typedef genecis_reverse_iterator<const_iterator>
				const_reverse_iterator ;


			/**
			 * Constructor with specified size.
			 * @param size		size of array to be allocated
			 */
			dynamic_array(size_type s, value_type c=0) {
				create_storage( s ) ;
				fill_n(__begin, s, c) ;
			}
		
			/**
			 * Empty constructor
			 */
			dynamic_array() {}
		
			/**
			 * Copy constructor
			 */
			dynamic_array(const self_type& other) {
				create_storage( other.size() ) ;
				std::copy( other.__begin, other.__end, __begin ) ;
			}

			/**
			 * Class assignment operator
			 */
			void operator=(const self_type& rhs) {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
				create_storage( rhs.size() ) ;
				std::copy( rhs.__begin, rhs.__end, __begin ) ;
			}

			/**
			 * Destructor
			 */
			virtual ~dynamic_array() {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
			}

			/**
			 * Returns the maximum capacity of the data array.
			 */
			size_type size() {
				return size_type( __end - __begin ) ;
			}
		
			size_type size() const {
				return size_type( __end - __begin ) ;
			}
		
			/**
			 * Returns a pointer to the data array of the class.
			 */
			pointer data() {
				return __begin ;
			}
		
			const_pointer data() const {
				return __begin ;
			}

			/** ===== Array Operators ===== **/

			/**
			 * Concatenates two dynamic arrays and passes back a new
			 * dynamic array.
			 */
			self_type operator+(dynamic_array& rhs) {
				size_type tmp_size = size() + rhs.size() ;
				self_type tmp(tmp_size) ;
				std::copy( __begin, __end, tmp.begin() ) ;
				std::copy( rhs.begin(), rhs.end(), (tmp.begin() + size()) ) ;
				return tmp ;
			}
		
			/**
			 * Concatenates this array with the rhs into this array.
			 */
			void operator+=(dynamic_array const& rhs) {
				size_type tmp_size = size() + rhs.size() ;
				resize( tmp_size ) ;
				std::copy( rhs.begin(), rhs.end(), (__begin + size()) ) ;
			}
		
			/**
			 * Array accessor
			 * If index is out of bounds, the array with do one of two
			 * things:
			 *	1. If index is positive, _data will be expanded to that size
			 *	2. If index is negative, _data will be accessed from the end
			 *	   in reverse order.
			 */
			reference operator() (size_type index) {
				if( index > size()-1 ) {
					resize(index+1) ;
				} else if ( index < 0 ) {
					index += size() ;
				}
				return *( __begin + index ) ;
			}
		
			/**
			 * Array assignment operator
			 */
			template<size_type _index>
			void operator= (value_type c) {
				operator() (_index) = c ;
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

		private:

			/**
			 * Pointers to the data stored in the dynamic_array
			 */
			iterator __begin ;
			iterator __end ;

			/**
			 * Resizes the data array to prevent the array from going
			 * out of bounds when the index is larger then the size of
			 * the array.
			 */
			void resize(size_type new_size) {
				iterator tmp__begin ;
				iterator tmp__end ;
				allocator_type a ;
				tmp__begin = a.allocate( new_size ) ;
				tmp__end = tmp__begin + new_size ;
				std::fill_n( tmp__begin, new_size, 0 ) ;
				std::copy( __begin, __end, tmp__begin ) ;
				a.deallocate( __begin, size() ) ;
				__begin = tmp__begin ;
				__end = tmp__end ;
			}
		
			/**
			 * Allocates the storage space for the class and sets up the
			 * pointers to the beginning and end of the memory.
			 */
			void create_storage(size_type __s) {
				allocator_type a ;
				__begin = a.allocate( __s ) ;
				__end = __begin + __s ;
			}

	};

}	// end of namespace container
}	// end of namespace genecis

#endif
