/**
 * @file memory_manager.h
 */

#ifndef GENECIS_BASE_MEMORY_MANAGER_H
#define GENECIS_BASE_MEMORY_MANAGER_H

#include <cstddef>

namespace genecis {
namespace base {

template<typename _T, typename _Alloc=std::allocator<_T> >
class memory_manager {

	protected:
	
		typedef _T		value_type ;
		typedef size_t		size_type ;
		typedef ptrdiff_t	difference_type ;
		typedef _T*		iterator ;
		typedef _T&		reference ;
		typedef _Alloc		allocator_type ;
	
		// Creates a memory block
		iterator get_mem( iterator __first, size_type __n ) {
			__first = mem_mng.allocate( __n ) ;
			return ( __first + __n ) ;
		}
		
		// Frees a memory block
		void free_mem( iterator __first, size_type __n ) {
			mem_mng.deallocate( __first, __n ) ;
		}
	
	private:
	
		allocator_type mem_mng ;

};

}
}

#endif
