/**
 * @file distribution_model.h
 */
 
#ifndef DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H
#define DISTRIBUTION_PROBABILITY_DENSITY_FUNCTION_H

#include <cmath>
#include <algorithm>

#define TWO_PI (2.0*M_PI)

using namespace std ;

class probability_density_function {

	public:

		/**
		 * Function call that takes an interval of [a,b)
		 * and returns the probability/integral on that
		 * interval.
		 */
		virtual double probability(double a, double b) = 0 ;

		//virtual ~distribution() {}	
};

#endif
