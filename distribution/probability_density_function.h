/**
 * @file distribution_model.h
 */
 
#ifndef GENECIS_DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H
#define GENECIS_DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H

#include <cmath>
#include <algorithm>

#define TWO_PI (2.0*M_PI)

using namespace std ;

template <class _TYPE> class probability_density_function {

	public:

		/**
		 * Function call that takes an interval of [a,b)
		 * and returns the probability/integral on that
		 * interval.
		 */
		virtual _TYPE probability(double a, double b) = 0 ;

		//virtual ~distribution() {}	
};

#endif
