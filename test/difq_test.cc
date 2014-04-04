#include "math/ode.h"
#include <iostream>
#include <cstdio>

using namespace std ;

int main() {

	double x = 0.1 ;
	double y ;
	double y0 = 2 ;
	double a = 10 ;
	
	ode::first_linear(y0,a,x,y) ;
	
	cout << "ode::first_linear::y = " << y << endl ;
	
	double dt = 0.1 ;
	double y01 [3] = {1,2,3} ;
	double y0_p = 3 ;
	
	ode::nth_linear(dt, y01, y0_p, 3, y) ;
	cout << "ode::nth_linear::y = " << y << endl ;
	printf("y = %2.8f\n", y) ;
	
	return (0) ;
}
