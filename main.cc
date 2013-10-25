#include <iostream>
#include "distribution/distribution.h"

using namespace std;

int main( int argc, char* argv[] ) {

	gaussian* dist = new gaussian(2,10) ;
	cout << "returned a value: " << dist->integrate(1,10) << endl;
	uniform udist(2.0,7.0) ;
	cout << "uniform dist returns (2->4): " << udist.integrate(2.0,4.0) << endl;
	return 0;
	
}
