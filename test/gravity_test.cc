#include <iostream>
#include "../physics/gravity.h"
#include "../math/mathematics.h"

using namespace std ;
using namespace genecis::math ;
using namespace genecis::physics ;

#define pi M_PI

int main() {

	svector* s1 = new svector() ;
	svector* s2 = new svector(1.0,pi/2.0,0.0) ;
	svector* v1 = new svector() ;
	svector* v2 = new svector(0.0,0.0,pi/100.0) ;
	svector* a1 = new svector() ;
	svector* a2 = new svector() ;
	double m1 = 1.9891e30 ;
	double m2 = 5.97219e24 ;
	double dt = 0.1 ;
	
	gravity g(m1,m2,dt,s1,s2,v1,v2,a1,a2) ;
	
	cout << "pos1: " << *(g.position1()) << endl ;
	cout << "pos2: " << *(g.position2()) << endl ;
	cout << "vel1: " << *(g.velocity2()) << endl ;
	cout << "mass1: " << g.mass1() << " kg" << endl ;
	cout << "mass2: " << g.mass2() << " kg" << endl ;
	cout << "time: " << g.time() << endl ;

}
