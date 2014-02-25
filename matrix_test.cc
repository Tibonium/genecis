#include <iostream>
#include "math/matrix.h"

using namespace std ;

int main() {
	
	matrix<int> mymatx(5,5) ;
	matrix<int> omatx(5,1) ;
	for(unsigned i=0; i<mymatx.nrow(); ++i) {
		for(unsigned j=0; j<mymatx.ncol(); ++j) {
			mymatx(i,j) = i+j ;
		}
	}
	for(unsigned i=0; i<omatx.nrow(); ++i) {
		for(unsigned j=0; j<omatx.ncol(); ++j) {
			omatx(i,j) = i+j ;
		}
	}

	cout << "mymatx: " << mymatx << endl ;
	cout << "omatx: " << omatx << endl ;
	
	matrix<int>* mtx = mymatx * omatx ;
	cout << "mtx: " << *mtx << endl ;
}
