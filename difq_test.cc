#include "math/ode.h"
#include <iostream>

using namespace std ;

int main() {

	double x = 0.1 ;
	double y ;
	double y0 = 2 ;
	double a = 10 ;
	
	ode::first_linear(y0,a,x,y) ;
	
	cout << "y: " << y << endl ;
	
	return (0) ;
}
