/**
 * @file thread.h
 * wrapper for pthread.h
 */

#ifndef GENECIS_BASE_THREAD_H
#define GENECIS_BASE_THREAD_H

#include <pthread.h>
#include <iostream>

namespace genecis {
namespace base {

	size_t func_call ;

	int __thread_count ;

	template<typename _T>
	void* call( void* __obj ) ;

	template<typename _T> class thread {

		public:
	
			typedef _T			derived_type ;
			typedef size_t		size_type ;
	
			// Constructor
			thread() {
				__thread_count = 0 ;
			}
		
			// Destructor
			virtual ~thread() {
				cout << "All threads are finished." << endl ;
				pthread_exit(NULL) ;
			}
		
			void run( pthread_t* t, void* obj ) {
				++__thread_count ;
				pthread_create( t, NULL, call<derived_type>, obj ) ;
			}
		
			void setFunction_call( size_type __f ) {
				func_call = __f ;
			}
		
			int isFinished() {
				return !( __thread_count == 0 ) ;
			}
	
		protected:
	
			pthread_mutex_t __key ;

	};

	template<typename _T>
	void* call( void* __obj ) {
		_T* obj = (_T*) __obj ;
		obj->function_call( func_call ) ;
		--__thread_count ;
		pthread_exit(NULL) ;
	}

}	// end of namespace base
}	// end of namespace genecis
#endif
