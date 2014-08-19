/**
 * @file array.h
 */

#ifndef GENECIS_CONTAINER_ARRAY
#define GENECIS_CONTAINER_ARRAY

#include "container_io.h"

namespace genecis {
namespace container {

	template<class T>
	class array : public container_expression<array<T> > {

		public:
	
			typedef array<T>			self_type ;
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
			array(self_type& a) {
				this->create_storage( a.size() ) ;
				std::copy( a.begin(), a.end(), __begin ) ;
			}
			
			template<typename A>
			array(const container_expression<A>& a) {
				create_storage( a().size() ) ;
				array_assign<scalar_assign>(*this, a) ;
			}
		
			/**
			 * Assignment operator
			 */
			void operator=(const self_type& a) {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
				this->create_storage( a.size() ) ;
				std::copy( a.begin(), a.end(), __begin ) ;
			}
			 
			template<typename A>
			void operator=(const container_expression<A>& a) {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
				this->create_storage( a().size() ) ;
				std::copy( a().begin(), a().end(), __begin ) ;
			}
		
			/**
			 * Destructor
			 */
			virtual ~array() {
				allocator_type d ;
				d.deallocate( __begin, size() ) ;
				__begin = NULL ;
				__end = NULL ;
			}
		
		/**** Iterators ****/
			/**
			 * Provides a pointer to the beginning of the data stored
			 * in this class.
			 */
			iterator begin() {
				return __begin ;
			}
		
			/**
			 * Provides a pointer to the end of the data stored in this
			 * class 
			 */
			iterator end() {
				return __end ;
			}
		
			/**
			 * Provides a const pointer to the beginning of the data
			 * stored in this class 
			 */
			const_iterator begin() const {
				return __begin ;
			}
		
			/**
			 * Provides a const pointer to the end of the data stored
			 * in this class 
			 */
			const_iterator end() const {
				return __end ;
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
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator( end() ) ;
			}
		
			/**
			 * Provides a const pointer to the beginning of the data
			 * stored in this class 
			 */
			const_reverse_iterator rend() const {
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
				operator() (_index) = c ;
			}
			
			array& operator+= (const value_type& c) {
				array_assign<scalar_add_assign> (*this, c) ;
				return (*this) ;
			}

			array& operator-= (const value_type& c) {
				return operator+=(-c) ;
			}

			array& operator*= (const value_type& c) {
				array_assign<scalar_multiply_assign> (*this, c) ;
				return (*this) ;
			}
			
			array& operator/= (const value_type& c) {
				array_assign<scalar_divide_assign> (*this, c) ;
				return (*this) ;
			}

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
