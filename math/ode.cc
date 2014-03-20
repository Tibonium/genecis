/**
 *	@file ode.cc
 *  main class for solving ordinary differential equations
 */

#include "ode.h"

/**
 * Solves ODEs of the form:
 * 		y'(x) = a, y(x0) = y0
 */
void ode::first_linear( double y0, double a, double x, double& y)
{
	y = y0 + a*x ;
}

/**
 * Solves ODEs of the form:
 * 		ax'' + bx' + cx = 0, x(0) = x0 and x'(0) = x0'
 */
void ode::second_linear( double a, double b, double c, 
			double x0, double x0_p, double& y )
{
	y = b + a*x0 ;
}
