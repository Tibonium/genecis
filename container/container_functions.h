/**
 * @file container_functions.h
 */

#ifndef GENECIS_CONTAINER_CONTAINER_FUNCTIONS_H
#define GENECIS_CONTAINER_CONTAINER_FUNCTIONS_H

#include "container_expression.h"

namespace genecis {
namespace container {

template<typename E> class container_expression ;

	// Unary assign
	template<template<class C> class F, class C, class T>
	void array_assign( C& c, const T& t ) {
        typedef F<C> function_type ;
        typedef typename C::size_type size_type ;
        size_type size( c.size () ) ;
        for(size_type i=0; i<size; ++i)
            function_type::use(c (i), t) ;
	}

	template<class E>
	struct scalar_add_assign {
		typedef typename E::reference  argument1_type ;
		typedef typename E::const_reference  argument2_type ;
		typedef typename E::value_type		 result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 += t2 ;
		}
	};
	
	template<class E>
	struct scalar_multiply_assign {
		typedef typename E::reference  argument1_type ;
		typedef typename E::const_reference  argument2_type ;
		typedef typename E::value_type		 result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 *= t2 ;
		}
	};
	
	template<class E>
	struct scalar_divide_assign {
		typedef typename E::reference  argument1_type ;
		typedef typename E::const_reference  argument2_type ;
		typedef typename E::value_type		 result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 /= t2 ;
		}
	};

	// binary function calls
	template<template<class T1, class T2> class F, class C, class E>
	void array_assign( C& c, const container_expression<E>& e ) {
        typedef F<typename C::reference, typename E::const_reference> function_type ;
        typedef typename C::size_type size_type ;
        size_type size( c.size () ) ;
        for(size_type i=0; i<size; ++i)
            function_type::use( c(i), e() (i)) ;
	}

	template<class T1, class T2>
	struct scalar_assign {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		
		static inline
		void use(argument1_type t1, argument2_type t2) {
			t1 = t2 ;
		}
	};

	template<class T1, class T2>
	struct scalar_add {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T1  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 + t2 ;
		}
	};
	
	template<class T1, class T2>
	struct scalar_multiply {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T1  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 * t2 ;
		}
	};
	
	template<class T1, class T2>
	struct scalar_divide {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T1  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 / t2 ;
		}
	};

}	// end of namespace container
}	// end of namespace genecis

#endif
