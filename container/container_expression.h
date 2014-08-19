/**
 * @file container_express.h
 */
 
#ifndef GENECIS_CONTAINER_CONTAINER_EXPRESSION_H
#define GENECIS_CONTAINER_CONTAINER_EXPRESSION_H

#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include "../base/genecis_reverse_iterator.h"
#include "container_functions.h"

namespace genecis {
namespace container {

	using namespace genecis::base ;

	template<class E>
	class container_expression {
		public:
			typedef E										 expression_type ;
			
			// Expression accessors
			const expression_type& operator() () const {
				return *static_cast<const expression_type*> (this) ;
			}
			
			expression_type& operator() () {
				return *static_cast<expression_type*> (this) ;
			}

	};
	
	template<class E1, class E2, class F>
	class array_binary :
		public container_expression<array_binary<E1,E2,F> >
	{
	
		public:
		
			typedef array_binary<E1,E2,F>		self_type ;
			typedef E1					expression1_type ;
			typedef E2					expression2_type ;
			typedef F					function_type ;
			typedef typename F::result_type		value_type ;
			typedef typename E1::size_type	size_type ;
		    typedef value_type 				reference ;
		    typedef const reference 		const_reference ;
			typedef typename E1::iterator		iterator ;
			typedef typename E1::const_iterator	const_iterator ;
			typedef typename E1::reverse_iterator	reverse_iterator ;
			typedef typename E1::const_reverse_iterator const_reverse_iterator ;
			
			// Constructor
			explicit
			array_binary( const expression1_type& e1, const expression2_type& e2 )
				: __e1(e1), __e2(e2) {}

			// Size
			size_type size() const {
				return expression1().size() ;
			}
			
			// Iterators
			/**
			 * Provides a pointer to the beginning of the data stored
			 * in this class.
			 */
			iterator begin() {
				return expression1().begin() ;
			}
		
			/**
			 * Provides a pointer to the end of the data stored in this
			 * class 
			 */
			iterator end() {
				return expression1().end() ;
			}
		
			/**
			 * Provides a const pointer to the beginning of the data
			 * stored in this class 
			 */
			const_iterator begin() const {
				return expression1().begin() ;
			}
		
			/**
			 * Provides a const pointer to the end of the data stored
			 * in this class 
			 */
			const_iterator end() const {
				return expression1().end() ;
			}
		
			/**
			 * Provides a pointer to the end of the data stored in this
			 * class 
			 */
			reverse_iterator rbegin() {
				return expression1().rbegin() ;
			}
		
			/**
			 * Provides a pointer to the beginning of the data
			 * stored in this class 
			 */
			reverse_iterator rend() {
				return expression1().rend() ;
			}
		
			/**
			 * Provides a const pointer to the end of the data stored
			 * in this class 
			 */
			const_reverse_iterator rbegin() const {
				return expression1().rbegin() ;
			}
		
			const_reverse_iterator rend() const {
				return expression1().rend() ;
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
	};
	
	template<class E1, class E2, class F>
	struct array_binary_traits{
		typedef array_binary<E1,E2,F>	expression_type ;
		typedef typename E1::self_type	result_type ;
	};
	
	template<class E1, class E2>
	typename array_binary_traits<E1, E2,
			scalar_add<typename E1::value_type,typename E2::value_type> >::result_type
	operator+ (const container_expression<E1>& e1, const container_expression<E2>& e2) {
	typedef typename array_binary_traits<E1, E2,
			scalar_add<typename E1::value_type,typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}

}	// end of namespace container
}	// end of namespace genecis

#endif
