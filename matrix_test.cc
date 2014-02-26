#include <iostream>
#include "math/matrix.h"

using namespace std ;

int main() {

	matrix<int> mymatx(5,5) ;
	for(unsigned i=0; i<mymatx.nrow(); ++i) {
		for(unsigned j=0; j<mymatx.ncol(); ++j) {
			mymatx(i,j) = 5*i+j ;
		}
	}
	matrix<int> omatx(5,1) ;
	for(unsigned i=0; i<omatx.nrow(); ++i) {
		for(unsigned j=0; j<omatx.ncol(); ++j) {
			omatx(i,j) = i+j ;
		}
	}

//	bool result = typeid(double) == typeid(int) ;
//	cout << "double == int: " ;
//	cout << ((result) ? "true" : "false") << endl ;

	cout << "mymatx: " << mymatx << endl ;
	mymatx.transpose() ;
	cout << "transpose: " << mymatx << endl ;
	cout << "omatx: " << omatx << endl ;
//	omatx.transpose() ;
//	cout << "transpose: " << omatx << endl ;
//	omatx = mymatx ;
//	cout << "reassign: " << omatx << endl ;

	matrix<int> mtx = mymatx * omatx ;
	mtx.transpose() ;
	cout << "mtx: " << mtx << endl ;
	mtx *= omatx ;
	cout << "after *= mtx: " << mtx << endl ;
//	omatx *= mymatx ;
//	cout << "new omatx: " << omatx << endl ;
//	mtx = &omatx ;
//	matrix<int>* mtx = new matrix<int>(2,2) ;
//	for(unsigned i=0; i<mtx->nrow(); ++i) {
//		for(unsigned j=0; j<mtx->ncol(); ++j) {
//			(*mtx)(i,j) = i*900+j*100 ;
//		}
//	}
//	cout << "mtx: " << *mtx << endl ;
//	(*mtx)(0,0) = 2 ;
//	(*mtx)^2 ;
//	cout << "mtx^2: " << *mtx << endl ;
	
	matrix<double> dmtx(2,2) ;
	for(unsigned i=0; i<dmtx.nrow(); ++i) {
		for(unsigned j=0; j<dmtx.ncol(); ++j) {
			dmtx(i,j) = i+j*0.0234+1 ;
		}
	}
	cout << "dmtx: " << dmtx << endl ;
	
	omatx = omatx + omatx ;
	cout << "+omatx: " << omatx << endl ;
	dmtx.inverse() ;

}
