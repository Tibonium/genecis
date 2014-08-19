/**
 * @file container_traits.h
 */
 
#ifndef GENECIS_CONTAINER_CONTAINER_TRAITS_H
#define GENECIS_CONTAINER_CONTAINER_TRAITS_H

#include "../base/genecis_reverse_iterator.h"

using namespace genecis::base ;

template<class T>
struct container_traits {

	typedef std::allocator<T>   					 allocator_type ;
	typedef T										 value_type ;
	typedef value_type *						 	 pointer ;
	typedef const pointer							 const_pointer ;
	typedef ptrdiff_t								 difference_type ;
	typedef value_type							 	 reference ;
	typedef const reference							 const_reference ;
	typedef size_t									 size_type ;
	typedef value_type *							 iterator ;
	typedef const value_type *						 const_iterator ;
	typedef genecis_reverse_iterator<iterator>		 reverse_iterator ;
	typedef genecis_reverse_iterator<const_iterator> const_reverse_iterator ;

};

#endif
