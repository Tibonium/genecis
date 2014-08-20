/**
 * @file probability_mass_function.h
 */
 
#ifndef GENECIS_DISTRIBUTION_PROBABILITY_MASS_FUNCTION_H
#define GENECIS_DISTRIBUTION_PROBABILITY_MASS_FUNCTION_H

#include <cmath>
#include <algorithm>

namespace genecis {
namespace distribution {

	#define TWO_PI (2.0*M_PI)

	using namespace std ;

	/**
	 * A probability mass function is a function
	 * that defines the probability of an element,
	 * x, a discrete random variable within the
	 * sample set, S, is equal to X.
	 *   f_X(x) = Pr(X = x) = Pr({s/inS : X(s) = x})
	 * and where f_X: A /rightarrow [0,1]
	 *   /sum_{x/inA} f_X(x) = 1 
	 */
			 
	template <class SAMPLE_TYPE, class PROB_TYPE> class probability_mass_function {

		public:

			virtual PROB_TYPE probability(SAMPLE_TYPE a) = 0 ;

			//virtual ~distribution() {}	
	};

}	// end of namespace distribution
}	// end of namespace genecis
#endif
