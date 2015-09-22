/**
 * @file genecis_functions.h
 */
#pragma once

#include <genecis/base/genecis_expression.h>
#include <cmath>
#include <complex>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

	template<typename E> class genecis_expression ;

/** ==================== Unary function calls ==================== **/
//	template<template<class T> class F>
//	void array_assign( G& c ) {
//        typedef F<typename G::reference> function_type ;
//        typedef typename G::size_type size_type ;
//        size_type size ( g.size () ) ;
//        for(size_type i=0; i<size; ++i)
//            function_type::use ( g (i) ) ;
//	}

	template<class T>
	struct scalar_negate {
		typedef T argument_type ;
		
		static inline
		argument_type use (argument_type t) {
			return - t ;
		}
	};

//	template<class T>
//	struct scalar_squeeze {
//		typedef T argument_type ;
//		
//		static inline
//		argument_type use (argument_type t) {
//			if( t != 0 ) return t ;
//		}
//	};

	template<class T>
	struct scalar_sqrt {
		typedef T argument_type ;
		
		static inline
		argument_type use (argument_type t) {
			return std::sqrt(t) ;
		}
	};

	template<class T>
	struct scalar_exp {
		typedef T argument_type ;
		
		static inline
		argument_type use (argument_type t) {
			return std::exp(t) ;
		}
	};

	template<class T>
	struct scalar_abs {
		typedef T argument_type ;
		
		static inline
		argument_type use (argument_type t) {
			return std::abs(t) ;
		}
	};

//	template<>
//	struct scalar_abs<std::complex<double> > {
//		typedef std::complex<double>	argument_type ;
//		typedef double			result_type ;
//		
//		static inline
//		result_type use (argument_type t) {
//			return std::abs(t) ;
//		}
//	};

	template<class T>
	struct scalar_sin {
		typedef T argument_type ;
		
		static inline
		argument_type use (argument_type t) {
			return std::sin(t) ;
		}
	};

	// Assign with expression and scalar
	template<template<class G> class F, class G, class T>
	void genecis_assign( G& g, const T& t ) {
        typedef F<G> function_type ;
        typedef typename G::size_type size_type ;
        size_type size ( g.size () ) ;
        for(size_type i=0; i<size; ++i)
            function_type::use (g (i), t) ;
	}

	template<class E>
	struct scalar_add_assign {
		typedef typename E::reference  argument1_type ;
		typedef typename E::const_reference  argument2_type ;
		typedef typename E::value_type		 result_type ;
		
		static inline
		result_type use (argument1_type t1, argument2_type t2) {
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

	template<class E>
	struct scalar_mod_assign {
		typedef typename E::reference  argument1_type ;
		typedef typename E::const_reference  argument2_type ;
		typedef typename E::value_type		 result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 %= t2 ;
		}
	};

/** ==================== Binary function calls ==================== **/
	template<template<class T1, class T2> class F, class G, class E>
	void genecis_assign( G& g, const genecis_expression<E>& e ) {
        typedef F<typename G::reference, typename E::const_reference> function_type ;
        typedef typename G::size_type size_type ;
        size_type size ( g.size () ) ;
        for(size_type i=0; i<size; ++i)
            function_type::use ( g (i), e () (i)) ;
	}

	template<class T1, class T2>
	struct scalar_assign {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		
		static inline
		void use (argument1_type t1, argument2_type t2) {
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
	struct scalar_minus {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T1  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 - t2 ;
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

	template<class T1, class T2>
	struct scalar_mod {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T1  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			return t1 % t2 ;
		}
	};

	template<class T1, class T2>
	struct scalar_find {
		typedef T1  argument1_type ;
		typedef T2  argument2_type ;
		typedef T2  result_type ;
		
		static inline
		result_type use(argument1_type t1, argument2_type t2) {
			if( t1 ) return t2 ;
			else return false ;
		}
	};

END_NAMESPACE
END_NAMESPACE
