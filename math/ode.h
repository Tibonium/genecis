/**
 *	@file ode.h
 */
 
#ifndef GENECIS_MATH_ODE_H
#define GENECIS_MATH_ODE_H

class ode {

	public:
	
		static void first_linear( double y0, double a, double x, double& y ) ;
		
		static void second_linear( double a, double b, double c, 
			double x0, double x0_p, double& y ) ;
			
		/**
		 * First-order Runge-Kutta method using the middle point
		 * approximation.
		 */
		static void rk1( double dt, double* y0, double& y ) ;
		
		static void rk2( double dt, double* y0, double& y ) ;
		
		static void rk3( double dt, double* y0, double* y1, double& y ) ;
		
		static void rk4(double dt, double* y0, double* y1, double* y2, 
			double& y) ;
		
		/**
		 * Recursive engie that produces the nth approximation of the
		 * successive first-order Runge-Kutta approximations.
		 */
		static void nth_linear( double dt, double* y0, double y0_p,
			 unsigned n, double& y ) ;

	private:
	
		/**
		 * Recursive driver for the nth_linear ODE solver engine, which
		 * approximates the value using an nth-order Runge-Kutta method.
		 */
		static double nth_order( double dt, double* y0,
			double y0_p, unsigned n ) ;

};

#endif
