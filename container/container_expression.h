/**
 * @file container_express.h
 */
 
#ifndef GENECIS_CONTAINER_CONTAINER_EXPRESSION_H
#define GENECIS_CONTAINER_CONTAINER_EXPRESSION_H

#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <genecis/base/genecis_expression.h>
#include <genecis/base/genecis_reverse_iterator.h>
#include <genecis/base/genecis_functions.h>

using namespace genecis::base ;

namespace genecis {
namespace container {

	template<class E>
	class container_expression : public genecis_expression<E> {
		public:
			typedef E	expression_type ;
			
			// Expression accessors
			const expression_type& operator() () const {
				return *static_cast<const expression_type*> (this) ;
			}
			
			expression_type& operator() () {
				return *static_cast<expression_type*> (this) ;
			}

	};

	// Unary array, operation(a)
	template<class E, class F>
	class array_unary :
		public container_expression<array_unary<E,F> >
	{
	
		public:
		
			typedef E		expression_type ;
			typedef F		function_type ;
			typedef typename E::value_type		value_type ;
			typedef typename E::size_type		size_type ;
		    typedef value_type 					reference ;
		    typedef const reference 			const_reference ;
			typedef array_unary<E,F>		self_type ;

			// Constructor
			explicit
			array_unary( const expression_type& e ) : __e(e) {}

			// Size
			size_type size() const {
				return expression().size() ;
			}

			// Element accessor
			const_reference operator() (size_type t) const {
				return function_type::use( __e(t) ) ;
			}

		private:

			expression_type __e ;

			// Expression accessor
			const expression_type& expression() const {
				return __e ;
			}

			/** Iterators NOTE: NOT yet implemented
			typedef typename E::iterator		iterator ;
			typedef typename E::const_iterator	const_iterator ;
			typedef typename E::reverse_iterator	reverse_iterator ;
			typedef typename E::const_reverse_iterator const_reverse_iterator ;
			 // Provides a pointer to the beginning of the data stored
			 // in this class.
			iterator begin() {
				return expression().begin() ;
			}

			 // Provides a pointer to the end of the data stored in this
			 // class
			iterator end() {
				return expression().end() ;
			}

			 // Provides a const pointer to the beginning of the data
			 // stored in this class 
			const_iterator begin() const {
				return expression().begin() ;
			}

			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_iterator end() const {
				return expression().end() ;
			}
		
			 // Provides a pointer to the end of the data stored in this
			 // class 
			reverse_iterator rbegin() {
				return expression().rbegin() ;
			}

			 // Provides a pointer to the beginning of the data
			 // stored in this class 
			reverse_iterator rend() {
				return expression().rend() ;
			}
		
			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_reverse_iterator rbegin() const {
				return expression().rbegin() ;
			}
		
			const_reverse_iterator rend() const {
				return expression().rend() ;
			}
			*/
	};

	template<class E, class F>
	struct array_unary_traits {
		typedef array_unary<E,F>	expression_type ;
		typedef typename E::self_type	result_type ;
	};

	// (-a)[i] = - a[i] 
	template<class E>
	typename array_unary_traits<E, scalar_negate<typename E::value_type> >::result_type
	operator- (const container_expression<E>& e) {
		typedef typename array_unary_traits<E,
				scalar_negate<typename E::value_type> >::expression_type expression_type ;
		return expression_type( e() ) ;
	}

	// sqrt(a)[i] = sqrt(a[i]) 
	template<class E>
	typename array_unary_traits<E, scalar_sqrt<typename E::value_type> >::result_type
	sqrt (const container_expression<E>& e) {
		typedef typename array_unary_traits<E,
				scalar_sqrt<typename E::value_type> >::expression_type expression_type ;
		return expression_type( e() ) ;
	}

	// exp(a)[i] = exp(a[i]) 
	template<class E>
	typename array_unary_traits<E, scalar_exp<typename E::value_type> >::result_type
	exp (const container_expression<E>& e) {
		typedef typename array_unary_traits<E,
				scalar_exp<typename E::value_type> >::expression_type expression_type ;
		return expression_type( e() ) ;
	}

	// abs(a)[i] = abs(a[i]) 
	template<class E>
	typename array_unary_traits<E, scalar_abs<typename E::value_type> >::result_type
	abs (const container_expression<E>& e) {
		typedef typename array_unary_traits<E,
				scalar_abs<typename E::value_type> >::expression_type expression_type ;
		return expression_type( e() ) ;
	}
	
	// Binary array, operation(a, b)
	template<class E1, class E2, class F>
	class array_binary :
		public container_expression<array_binary<E1,E2,F> >
	{
	
		public:
		
			typedef E1		expression1_type ;
			typedef E2		expression2_type ;
			typedef F		function_type ;
			typedef typename F::result_type		value_type ;
			typedef typename E1::size_type		size_type ;
		    typedef value_type 					reference ;
		    typedef const reference 			const_reference ;
			typedef array_binary<E1,E2,F>		self_type ;

			// Constructor
			explicit
			array_binary( const expression1_type& e1, const expression2_type& e2 )
				: __e1(e1), __e2(e2) {}

			// Size
			size_type size() const {
				return expression1().size() ;
			}

			// Element accessor
			const_reference operator() (size_type t) const {
				return function_type::use( __e1(t), __e2(t) ) ;
			}

		private:

			expression1_type __e1 ;
			expression2_type __e2 ;

			// Expression accessor
			const expression1_type& expression1() const {
				return __e1 ;
			}

			const expression2_type& expression2() const {
				return __e2 ;
			}

			/** Iterators NOTE: NOT yet implemented
			typedef typename E1::iterator		iterator ;
			typedef typename E1::const_iterator	const_iterator ;
			typedef typename E1::reverse_iterator	reverse_iterator ;
			typedef typename E1::const_reverse_iterator const_reverse_iterator ;
			 // Provides a pointer to the beginning of the data stored
			 // in this class.
			iterator begin() {
				return expression1().begin() ;
			}

			 // Provides a pointer to the end of the data stored in this
			 // class
			iterator end() {
				return expression1().end() ;
			}

			 // Provides a const pointer to the beginning of the data
			 // stored in this class 
			const_iterator begin() const {
				return expression1().begin() ;
			}

			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_iterator end() const {
				return expression1().end() ;
			}
		
			 // Provides a pointer to the end of the data stored in this
			 // class 
			reverse_iterator rbegin() {
				return expression1().rbegin() ;
			}

			 // Provides a pointer to the beginning of the data
			 // stored in this class 
			reverse_iterator rend() {
				return expression1().rend() ;
			}
		
			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_reverse_iterator rbegin() const {
				return expression1().rbegin() ;
			}
		
			const_reverse_iterator rend() const {
				return expression1().rend() ;
			}
			*/
	};
	
	template<class E1, class E2, class F>
	struct array_binary_traits {
		typedef array_binary<E1,E2,F>	expression_type ;
		typedef typename E1::self_type	result_type ;
	};
	
	// (a + b)[i] = a[i] + b[i]
	template<class E1, class E2>
	typename array_binary_traits<E1, E2,
			scalar_add<typename E1::value_type,typename E2::value_type> >::result_type
	operator+ (const container_expression<E1>& e1, const container_expression<E2>& e2) {
	typedef typename array_binary_traits<E1, E2,
			scalar_add<typename E1::value_type,typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}

	// (a - b)[i] = a[i] - b[i]
	template<class E1, class E2>
	typename array_binary_traits<E1, E2,
			scalar_minus<typename E1::value_type,typename E2::value_type> >::result_type
	operator- (const container_expression<E1>& e1, const container_expression<E2>& e2) {
	typedef typename array_binary_traits<E1, E2,
			scalar_minus<typename E1::value_type,typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}

	// (a * b)[i] = a[i] * b[i]
	template<class E1, class E2>
	typename array_binary_traits<E1, E2,
			scalar_multiply<typename E1::value_type,typename E2::value_type> >::result_type
	multiply (const container_expression<E1>& e1, const container_expression<E2>& e2) {
	typedef typename array_binary_traits<E1, E2,
			scalar_multiply<typename E1::value_type,typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}

	// (a / b)[i] = a[i] / b[i]	
	template<class E1, class E2>
	typename array_binary_traits<E1, E2,
			scalar_divide<typename E1::value_type,typename E2::value_type> >::result_type
	divide (const container_expression<E1>& e1, const container_expression<E2>& e2) {
	typedef typename array_binary_traits<E1, E2,
			scalar_divide<typename E1::value_type,typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}

	// Left scalar array, operation(s,a)
	template<class E, class T, class F>
	class array_scalar1 :
		public container_expression<array_scalar1<E,T,F> >
	{
	
		public:
		
			typedef E		expression_type ;
			typedef F		function_type ;
			typedef T		value_type ;
			typedef typename E::size_type		size_type ;
		    typedef value_type 					reference ;
		    typedef const reference 			const_reference ;
			typedef array_scalar1<E,T,F>		self_type ;

			// Constructor
			explicit
			array_scalar1( const expression_type& e, const T& s )
				: __e(e), __s(s) {}

			// Size
			size_type size() const {
				return expression().size() ;
			}

			// Element accessor
			const_reference operator() (size_type t) const {
				return function_type::use( __e(t), __s ) ;
			}

		private:

			expression_type __e ;
			value_type __s ;

			// Expression accessor
			const expression_type& expression() const {
				return __e ;
			}

			/** Iterators NOTE: NOT yet implemented
			typedef typename E::iterator		iterator ;
			typedef typename E::const_iterator	const_iterator ;
			typedef typename E::reverse_iterator	reverse_iterator ;
			typedef typename E::const_reverse_iterator const_reverse_iterator ;
			 // Provides a pointer to the beginning of the data stored
			 // in this class.
			iterator begin() {
				return expression().begin() ;
			}

			 // Provides a pointer to the end of the data stored in this
			 // class
			iterator end() {
				return expression().end() ;
			}

			 // Provides a const pointer to the beginning of the data
			 // stored in this class 
			const_iterator begin() const {
				return expression().begin() ;
			}

			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_iterator end() const {
				return expression().end() ;
			}
		
			 // Provides a pointer to the end of the data stored in this
			 // class 
			reverse_iterator rbegin() {
				return expression().rbegin() ;
			}

			 // Provides a pointer to the beginning of the data
			 // stored in this class 
			reverse_iterator rend() {
				return expression().rend() ;
			}
		
			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_reverse_iterator rbegin() const {
				return expression().rbegin() ;
			}
		
			const_reverse_iterator rend() const {
				return expression().rend() ;
			}
			*/
	};

	template<class E, class T, class F>
	struct array_scalar1_traits {
		typedef array_scalar1<E,T,F>	expression_type ;
		typedef typename E::self_type	result_type ;
	};

	// (s + a)[i] = s + a[i] 
	template<class E, class T>
	typename array_scalar1_traits<E, T, scalar_add<typename E::value_type, T> >::result_type
	operator+ (const T& s, const container_expression<E>& e) {
		typedef typename array_scalar1_traits<E, T,
				scalar_add<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (s - a)[i] = s - a[i] 
	template<class E, class T>
	typename array_scalar1_traits<E, T, scalar_minus<T, typename E::value_type> >::result_type
	operator- (const T& s, const container_expression<E>& e) {
		typedef typename array_scalar1_traits<E, T,
				scalar_minus<T, typename E::value_type> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (s * a)[i] = s * a[i] 
	template<class E, class T>
	typename array_scalar1_traits<E, T, scalar_multiply<typename E::value_type, T> >::result_type
	operator* (const T& s, const container_expression<E>& e) {
		typedef typename array_scalar1_traits<E, T,
				scalar_multiply<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (s / a)[i] = s / a[i] 
	template<class E, class T>
	typename array_scalar1_traits<E, T, scalar_divide<typename E::value_type, T> >::result_type
	operator/ (const T& s, const container_expression<E>& e) {
		typedef typename array_scalar1_traits<E, T,
				scalar_divide<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// Right scalar array, operation(a,s)
	template<class E, class T, class F>
	class array_scalar2 :
		public container_expression<array_scalar2<E,T,F> >
	{
	
		public:
		
			typedef E		expression_type ;
			typedef F		function_type ;
			typedef T		value_type ;
			typedef typename E::size_type		size_type ;
		    typedef value_type 					reference ;
		    typedef const reference 			const_reference ;
			typedef array_scalar2<E,T,F>		self_type ;

			// Constructor
			explicit
			array_scalar2( const expression_type& e, const T& s )
				: __e(e), __s(s) {}

			// Size
			size_type size() const {
				return expression().size() ;
			}

			// Element accessor
			const_reference operator() (size_type t) const {
				return function_type::use( __s, __e(t) ) ;
			}

		private:

			expression_type __e ;
			value_type __s ;

			// Expression accessor
			const expression_type& expression() const {
				return __e ;
			}

			/** Iterators NOTE: NOT yet implemented
			typedef typename E::iterator		iterator ;
			typedef typename E::const_iterator	const_iterator ;
			typedef typename E::reverse_iterator	reverse_iterator ;
			typedef typename E::const_reverse_iterator const_reverse_iterator ;
			 // Provides a pointer to the beginning of the data stored
			 // in this class.
			iterator begin() {
				return expression().begin() ;
			}

			 // Provides a pointer to the end of the data stored in this
			 // class
			iterator end() {
				return expression().end() ;
			}

			 // Provides a const pointer to the beginning of the data
			 // stored in this class 
			const_iterator begin() const {
				return expression().begin() ;
			}

			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_iterator end() const {
				return expression().end() ;
			}
		
			 // Provides a pointer to the end of the data stored in this
			 // class 
			reverse_iterator rbegin() {
				return expression().rbegin() ;
			}

			 // Provides a pointer to the beginning of the data
			 // stored in this class 
			reverse_iterator rend() {
				return expression().rend() ;
			}
		
			 // Provides a const pointer to the end of the data stored
			 // in this class 
			const_reverse_iterator rbegin() const {
				return expression().rbegin() ;
			}
		
			const_reverse_iterator rend() const {
				return expression().rend() ;
			}
			*/
	};

	template<class E, class T, class F>
	struct array_scalar2_traits {
		typedef array_scalar2<E,T,F>	expression_type ;
		typedef typename E::self_type	result_type ;
	};

	// (a + s)[i] = a[i] + s 
	template<class E, class T>
	typename array_scalar2_traits<E, T, scalar_add<typename E::value_type, T> >::result_type
	operator+ (const container_expression<E>& e, const T& s) {
		typedef typename array_scalar2_traits<E, T,
				scalar_add<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (a - s)[i] = a[i] - s 
	template<class E, class T>
	typename array_scalar2_traits<E, T, scalar_minus<typename E::value_type, T> >::result_type
	operator- (const container_expression<E>& e, const T& s) {
		typedef typename array_scalar2_traits<E, T,
				scalar_minus<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (a * s)[i] = a[i] * s 
	template<class E, class T>
	typename array_scalar2_traits<E, T, scalar_multiply<typename E::value_type, T> >::result_type
	operator* (const container_expression<E>& e, const T& s) {
		typedef typename array_scalar2_traits<E, T,
				scalar_multiply<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}
			
	// (a / s)[i] = a[i] / s 
	template<class E, class T>
	typename array_scalar2_traits<E, T, scalar_divide<typename E::value_type, T> >::result_type
	operator/ (const container_expression<E>& e, const T& s) {
		typedef typename array_scalar2_traits<E, T,
				scalar_divide<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

}	// end of namespace container
}	// end of namespace genecis

#endif
