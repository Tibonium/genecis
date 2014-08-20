/**
 * @file distribution_model.h
 */
 
#ifndef GENECIS_DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H
#define GENECIS_DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H

#include <cmath>
#include <algorithm>

namespace genecis {
namespace distribution {

	#define TWO_PI (2.0*M_PI)

	using namespace std ;

	template <class T> class probability_density_function {

		public:
		
			typedef T		value_type ;

			/**
			 * Function call that takes an interval of [a,b)
			 * and returns the probability/integral on that
			 * interval.
			 */
			virtual value_type
			probability(value_type a, value_type b) = 0 ;

			//virtual ~distribution() {}	
	};

}	// end of namespace distribution
}	// end of namespace genecis
#endif
