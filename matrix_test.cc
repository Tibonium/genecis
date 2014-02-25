#include <iostream>
#include "math/matrix.h"

using namespace std ;

int main() {
	
	matrix<int> mymatx(5,5) ;
	for(unsigned i=0; i<mymatx.nrow(); ++i) {
		for(unsigned j=0; j<mymatx.ncol(); ++j) {
			mymatx(i,j) = i+j ;
		}
	}	
	
	cout << "my matrix is: " << mymatx << endl ;
}
