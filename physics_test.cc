#include <iostream>
#include "physics/svector.h"

using namespace std ;

int main() {

	svector myvec( 1231.4, 15.0, 3.0 ) ;
	svector otrvec( 14950.2, 22.1, -20.4 ) ;
	cout << myvec << endl ;
	cout << "The two vectors...." 
		<< "\nmyvec" << myvec
		<< "\notrvec" << otrvec ;
	( myvec != otrvec ) ? cout << " are not equal." << endl : 
		cout << " are equal." << endl ;
		
	cout << "The inner product of these two vectors is: "
		<< myvec.dot(otrvec) << endl ;
		
	cout << "The cross product is: "
		<< myvec.cross(otrvec) << endl ;
		
	cout << "(myvec < otrvec) is " ;
	(myvec < otrvec) ? cout << "true." << endl :
		cout << "false." << endl ;
	
	cout << "norm of myvec " << myvec.norm() << endl ;
	return 0 ;
}
