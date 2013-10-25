/**
 * @file integrate.h
 */
 
#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <cmath>

#define TWO_PI (2.0*M_PI)

class integrate {

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
