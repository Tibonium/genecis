/**
 * @file functional_logic.h
 */
 
#ifndef GENECIS_MATH_FUNCTIONAL_LOGIC_H
#define GENECIS_MATH_FUNCTIONAL_LOGIC_H

#include <genecis/math/set.h>

namespace genecis {
namespace math {

	template <class T1, class T2>
	class functional_logic {
		
		public:
		
			typedef functional_logic<T1,T2>				self_type ;
			typedef set<T1>								domain_type ;
			typedef set<T2>								codomain_type ;
			typedef typename domain_type::size_type		size_type ;
			typedef typename domain_type::value_type	domain_value_type ;
			typedef typename domain_type::reference		domain_reference ;
			typedef typename domain_type::iterator		domain_iterator ;
			typedef typename codomain_type::value_type	codomain_value_type ;
			typedef typename codomain_type::reference	codomain_reference ;
			typedef typename codomain_type::iterator	codomain_iterator ;
		
			/**
			 * Constructor
			 */
			functional_logic( const domain_type& domain,
							  const codomain_type& codomain,
							  const domain_type& x,
							  const codomain_type& y )
				: __domain(domain),
				  __codomain(codomain),
				  __x(x), __y(y)
			{}
			
			/**
			 * Destructor
			 */
			virtual ~functional_logic() {}
			
			/**
			 * Valid function
			 *
			 * In modern mathematics,[3] a function is defined by
			 * its set of inputs, called the domain; a set containing
			 * the set of outputs, and possibly additional elements,
			 * as members, called its codomain; and the set of all
			 * input-output pairs, called its graph.
			 */
			inline
			bool isValid() {
				return __domain.isSubset(__x)
					&& __codomain.isSubset(__y) ;
			}
			
			/**
			 * Injective
			 *
			 * In mathematics, an injective function or injection or
			 * one-to-one function is a function that preserves
			 * distinctness: it never maps distinct elements of its
			 * domain to the same element of its codomain. In other
			 * words, every element of the function's codomain is
			 * the image of at most one element of its domain.
			 */
			bool isInjective() {
				if( !isValid() ) return false ;
				return (__x.uniqueElements()
					&& __y.uniqueElements()) ;
			}
			
			/**
			 * Surjective
			 *
			 * In mathematics, a function f from a set X to a set Y
			 * is surjective (or onto), or a surjection, if every
			 * element y in Y has a corresponding element x in X
			 * such that f(x) = y.
			 */
			bool isSurjective() {
				return __x.size() == __y.size() ;
			}
			
			/**
			 * Bijective
			 *
			 * In mathematics, a bijection (or bijective function or
			 * one-to-one correspondence) is a function between the
			 * elements of two sets, where every element of one set
			 * is paired with exactly one element of the other set,
			 * and every element of the other set is paired with
			 * exactly one element of the first set. There are no
			 * unpaired elements. In formal mathematical terms, a
			 * bijective function f: X → Y is a one to one and onto
			 * mapping of a set X to a set Y.
			 */
			bool isBijective() {
				return isSurjective() && isInjective() ;
			}
			
			/**
			 * Fancy format for standard output
			 */
			void print() {
				std::cout << "The Function is: " << std::endl ;
				for(size_type i=0; i<__x.size(); ++i) {
					std::cout << "f(" << __x(i) << ") = "
						 << __y(i) << std::endl ;
				}
			}
		
		private:
		
			domain_type		__domain ;
			codomain_type	__codomain ;
			domain_type		__x ;
			codomain_type	__y ;

	};

}	// end of namespace math
}	// end of namespace genecis

#endif
