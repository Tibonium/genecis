/**
 * @file cumulative_distribution_function.h
 */
 
#ifndef GENECIS_DISTRIBUTION_CUMULATIVE_DISTRIBUTION_FUNCTION_H
#define GENECIS_DISTRIBUTION_CUMULATIVE_DISTRIBUTION_FUNCTION_H

#include <cmath>
#include <algorithm>

#define TWO_PI (2.0*M_PI)

using namespace std ;

class cumulative_distribution_function {

	public:

		virtual double probability(double x) = 0 ;

		//virtual ~distribution() {}	
};

#endif
