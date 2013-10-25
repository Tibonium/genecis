/**
 * @file distribution.h
 */
 
#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cmath>

#define TWO_PI (2.0*M_PI)

class distribution {

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
