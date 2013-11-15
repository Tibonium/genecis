#include <iostream>
#include "math/mathematics.h"

using namespace std ;

int main() {

	cout << "***svector Test section***" << endl ;
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
	
	cout << "***bvector Test section***" << endl ;
	bvector i( 1.0, 0.0, 0.0 ) ;
	bvector j( 0.0, 1.0, 0.0 ) ;
	bvector k( 0.0, 0.0, 1.0 ) ;
	
	cout << "The dot products are..." << endl ;
	cout << "i dot i: " << i.dot(i) << endl ;
	cout << "i dot j: " << i.dot(j) << endl ;
	cout << "i dot k: " << i.dot(k) << endl ;
	cout << "j dot j: " << j.dot(j) << endl ;
	cout << "j dot k: " << j.dot(k) << endl ;
	cout << "k dot k: " << k.dot(k) << endl ;
	
	cout << "The cross products are..." << endl ;
	cout << "i cross i: " << i.cross(i) << endl ;
	cout << "i cross j: " << i.cross(j) << endl ;
	cout << "i cross k: " << i.cross(k) << endl ;
	cout << "j cross i: " << j.cross(i) << endl ;
	cout << "j cross j: " << j.cross(j) << endl ;
	cout << "j cross k: " << j.cross(k) << endl ;
	cout << "k cross i: " << k.cross(i) << endl ;
	cout << "k cross j: " << k.cross(j) << endl ;
	cout << "k cross k: " << k.cross(k) << endl ;
	
	return 0 ;
}
