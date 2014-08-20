#include <genecis/math/math_vector.h>

using namespace std ;
using namespace genecis::math ;

int main() {

	cout << "\t\t***svector Test section***" << endl ;
	svector<double> myvec( 5.0, 15.0, 3.0, true ) ;
	svector<double> otrvec( 3.0, 22.0, -20.0, true ) ;
	cout << myvec << endl ;
	cout << "The two vectors...." 
		<< "\nmyvec" << myvec
		<< "\notrvec" << otrvec ;
	( myvec != otrvec ) ? cout << " are not equal." << endl : 
		cout << " are equal." << endl ;
		
	cout << "The inner product of these two vectors is: "
		<< myvec.dot(otrvec) << endl ;
	
	svector<double> st = myvec.cross(otrvec) ;
	cout << "The cross product is: "
		<< st << endl ;
		
	cout << "(myvec < otrvec) is " ;
	(myvec < otrvec) ? cout << "true." << endl :
		cout << "false." << endl ;
	
	cout << "maginutde of myvec: " << myvec.magnitude() << endl ;
	myvec.norm() ;
	cout << "norm of myvec: " << myvec << endl ;
	cout << "magnitude of the norm of myvec: " << myvec.magnitude() << endl ;
	
	cout << "\t\t***bvector Test section***" << endl ;
	bvector<double> i( 1.0, 0.0, 0.0 ) ;
	bvector<double> j( 0.0, 1.0, 0.0 ) ;
	bvector<double> k( 0.0, 0.0, 1.0 ) ;
	cout << "i" << i << endl ;
	cout << "j" << j << endl ;
	cout << "k" << k << endl ;
	
	cout << "The dot products are..." << endl ;
	cout << "i dot i: " << i.dot(i) << endl ;
	cout << "i dot j: " << i.dot(j) << endl ;
	cout << "i dot k: " << i.dot(k) << endl ;
	cout << "j dot j: " << j.dot(j) << endl ;
	cout << "j dot k: " << j.dot(k) << endl ;
	cout << "k dot k: " << k.dot(k) << endl ;
	
	cout << "The cross products are..." << endl ;
	bvector<double> t = i.cross(i) ;
	cout << "i cross i: " << t << endl ;
	t = i.cross(j) ;
	cout << "i cross j: " << t << endl ;
	t = i.cross(k) ;
	cout << "i cross k: " << t << endl ;
	t = j.cross(i) ;
	cout << "j cross i: " << t << endl ;
	t = j.cross(j) ;
	cout << "j cross j: " << t << endl ;
	t = j.cross(k) ;
	cout << "j cross k: " << t << endl ;
	t = k.cross(i) ;
	cout << "k cross i: " << t << endl ;
	t = k.cross(j) ;
	cout << "k cross j: " << t << endl ;
	t = k.cross(k) ;
	cout << "k cross k: " << t << endl ;
	t = i + j ;
	cout << "i+j: " << t << endl ;
	t = i-j ;
	cout << "i-j: " << t << endl ;

//	ovector<double> omni(1.0,2.0,3.0,i,j,k) ;
//	cout << "omni" << omni << endl ;

	double r1 = 1.0 ;
	double t1 = M_PI / 2.0 ;
	double p1 = 0.0 ;
	svector<double> s1(r1,t1,p1) ;
	
	double r2 = 1.0 ;
	double t2 = M_PI / 2.0 ;
	double p2 = M_PI / 2.0 ;
	svector<double> s2(r2,t2,p2) ;
	
	cout << "s1" << s1 << endl ;

	cout << "s2" << s2 << endl ;
		 
	svector<double> s3 = s1+s2 ;
	cout << "s1+s2" << s3 << endl ;
	
	s3 = s1-s2 ;
	cout << "s1-s2" << s3 << endl ;
	
	svector<double> c = s1.cross(s2) ;
	cout << "c" << c << endl ;
	c = c - 2 ;
	cout << "c-2" << c << endl ;
	
	cvector<double> myc ;
	cout << "myc" << myc << endl ;

}
