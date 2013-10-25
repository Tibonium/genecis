/**
 * @file distribution_model.h
 */
 
#ifndef DISTRIBUTION_DISTRIBUTION_MODEL_H
#define DISTRIBUTION_DISTRIBUTION_MODEL_H

#include <cmath>
#include <algorithm>

#define TWO_PI (2.0*M_PI)

using namespace std ;

class distribution_model {

	public:

		/**
		 * Function call that takes an interval of [a,b)
		 * and returns the probability/integral on that
		 * interval.
		 */
		virtual double integrate(double a, double b) = 0 ;

		//virtual ~distribution() {}	
};

#endif
