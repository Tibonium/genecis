/**
 *	@file ode.h
 */
 
#ifndef MATH_ODE_H
#define MATH_ODE_H

class ode {

	public:
	
		static void first_linear( double y0, double a, double x, double& y ) ;
		
		static void second_linear( double a, double b, double c, 
			double x0, double x0_p, double& y ) ;

};

#endif
