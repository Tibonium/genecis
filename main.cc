#include <iostream>
#include "distribution/distribution.h"

using namespace std;

int main( int argc, char* argv[] ) {

	gaussian* dist = new gaussian(2,10,0.00001) ;
	cout << "returned a value: " << dist->integrate(1,10) << endl;
	uniform udist(2.0,7.0) ;
	cout << "uniform dist returns [6,4): " << udist.integrate(0.0,3.948) << endl;
	return 0;
	
}
