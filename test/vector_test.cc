#include <iostream>
#include <cmath>
#include "../math/mathematics.h"

using namespace std ;
using namespace genecis::math ;

int main() {

	cout << "\t\t***svector Test section***" << endl ;
	svector myvec( 5.0, 15.0, 3.0, true ) ;
	svector otrvec( 3.0, 22.0, -20.0, true ) ;
	cout << myvec << endl ;
	cout << "The two vectors...." 
		<< "\nmyvec" << myvec
		<< "\notrvec" << otrvec ;
	( myvec != otrvec ) ? cout << " are not equal." << endl : 
		cout << " are equal." << endl ;
		
	cout << "The inner product of these two vectors is: "
		<< myvec.dot(otrvec) << endl ;
		
	cout << "The cross product is: "
		<< *(myvec.cross(otrvec)) << endl ;
		
	cout << "(myvec < otrvec) is " ;
	(myvec < otrvec) ? cout << "true." << endl :
		cout << "false." << endl ;
	
	cout << "maginutde of myvec: " << myvec.magnitude() << endl ;
	myvec.norm() ;
	cout << "norm of myvec: " << myvec << endl ;
	cout << "magnitude of the norm of myvec: " << myvec.magnitude() << endl ;
	
	cout << "\t\t***bvector Test section***" << endl ;
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

//	ovector<double> omni(1.0,2.0,3.0,i,j,k) ;
//	cout << "omni" << omni << endl ;

	double r1 = 1.0 ;
	double t1 = M_PI / 2.0 ;
	double p1 = 0.0 ;
	svector s1(r1,t1,p1) ;
	
	double r2 = 1.0 ;
	double t2 = M_PI / 2.0 ;
	double p2 = M_PI / 2.0 ;
	svector s2(r2,t2,p2) ;
	
	cout << "s1" << s1 << endl ;

	cout << "s2" << s2 << endl ;
		 
	svector* s3 = s1+s2 ;
	cout << "s1+s2" << *s3 << endl ;
	
	delete s3 ;
	
	s3 = s1-s2 ;
	cout << "s1-s2" << *s3 << endl ;
	
	svector* c = s1.cross(s2) ;
	cout << "c" << *c << endl ;

	delete c ;
	delete s3 ;
}
