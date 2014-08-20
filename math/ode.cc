/**
 *	@file ode.cc
 *  main class for solving ordinary differential equations
 */

#include <genecis/math/ode.h>
#include <iostream>

using namespace genecis::math ;

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

/**
 * Simple first order Runge-Kutta Method using the middle point
 * approximation.
 */
void ode::rk1( double dt, double* y0, double& y ) {
	y = y0[0] + 0.5 * dt * y0[1] ;
}

void ode::rk2( double dt, double* y0, double& y ) {
	double k1, k2 ;
	double h = 2.0 / 3.0 ;
	double yt1 [2] = {y0[0], y0[1]} ;
	ode::rk1( dt, yt1, k1 ) ;
	double yt2 [2] = {y0[0]+k1*h, y0[1]} ;
	ode::rk1( dt+h, yt2, k2 ) ;
	y = y0[0] + dt * ( 0.25 * k1 + 0.75 * k2 ) ;
}

void ode::rk3( double dt, double* y0, double* y1, double& y )
{
//	double k1, k2, k3 ;
//	y = ;
}

void ode::rk4(double dt, double* y0, double* y1, double* y2, 
	double& y)
{
//	double k1, k2, k3, k4 ;
//	y = ;
}

/**
 * Recursive engine to produce the nth approximation of the 
 * first-order Runge-Kutta result
 */
void ode::nth_linear( double dt, double* y0, double y0_p,
	unsigned n, double& y )
{	
	double y_prime = nth_order( dt, y0, y0_p, n ) ;
	
	double yt [2] = {y0[0], y_prime} ;
	rk1( dt, yt, y) ;
}

double ode::nth_order( double dt, double* y0, double y0_p, unsigned n )
{
	double result ;
	double* y0_n = new double[n-1] ;
	
	for(unsigned i=1; i<n; ++i) {
		y0_n[i-1] = y0[i] ;
	}
	
	if( n == 1 ) {
		delete y0_n ;
		double yt [2] = {y0[0], y0_p} ;
		rk1( dt, yt, result) ;
		return result ;
	} else {
		nth_linear( dt, y0_n, y0_p, n-1, result) ;
	}
	return result ;
}
