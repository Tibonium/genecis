/**
 * @file uniform.h
 */
 
#ifndef GENECIS_DISTRIBUTION_UNIFORM_H
#define GENECIS_DISTRIBUTION_UNIFORM_H

#include <genecis/distribution/probability_density_function.h>

/**
 * The continuous uniform distribution or rectangular
 * distribution is a family of symmetric probability
 * distributions such that for each member of the family,
 * all intervals of the same length on the distribution's
 * support are equally probable. The support is defined by
 * the two parameters, a and b, which are its minimum and
 * maximum values.
 */

namespace genecis {
namespace distribution {

	class uniform :
		public probability_density_function<double> {
		
		public:
		
			typedef double			value_type ;
	
			///constructor
			uniform( value_type lower, value_type upper ) :
			__lower(lower), __upper(upper) {
				__norm = 1.0 / ( __upper - __lower ) ;
			}
			
			// Empty constructor
			uniform() {} ;
			
			virtual ~uniform() {} ;
			
			virtual value_type probability(value_type a, value_type b) {
				value_type low = min( __upper, max(a, __lower) ) ;
				value_type high = max( __lower, min(b, __upper) ) ;
				value_type result = ( high - low ) * __norm ;
				return result ;
			}

		private:
	
			value_type __lower ;
			value_type __upper ;
			value_type __norm ;

	};

}	// end of namespace distribution
}	// end of namespace genecis

#endif
