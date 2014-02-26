#include <iostream>
#include "math/matrix.h"

using namespace std ;

int main() {
	
	matrix<int> mymatx(5,5) ;
	matrix<int> omatx(5,1) ;
	for(unsigned i=0; i<mymatx.nrow(); ++i) {
		for(unsigned j=0; j<mymatx.ncol(); ++j) {
			mymatx(i,j) = 5*i+j ;
		}
	}
	for(unsigned i=0; i<omatx.nrow(); ++i) {
		for(unsigned j=0; j<omatx.ncol(); ++j) {
			omatx(i,j) = i+j ;
		}
	}
	
	cout << "mymatx: " << mymatx << endl ;
	mymatx.transpose() ;
	cout << "transpose: " << mymatx << endl ;
	cout << "omatx: " << omatx << endl ;
//	omatx.transpose() ;
//	cout << "transpose: " << omatx << endl ;
//	omatx = mymatx ;
//	cout << "reassign: " << omatx << endl ;
	
//	matrix<int>* mtx = mymatx * omatx ;
//	mtx = &omatx ;
//	omatx.transpose() ;
//	mtx *= omatx.transpose() ;
//	omatx *= mymatx ;
//	mtx = &omatx ;
	matrix<int>* mtx = new matrix<int>(2,2) ;
	for(unsigned i=0; i<mtx->nrow(); ++i) {
		for(unsigned j=0; j<mtx->ncol(); ++j) {
			(*mtx)(i,j) = i+j ;
		}
	}
	cout << "mtx: " << *mtx << endl ;
//	(*mtx)(0,0) = 2 ;
	(*mtx)^2 ;
	cout << "mtx^2: " << *mtx << endl ;
}
