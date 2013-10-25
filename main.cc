#include <iostream>
#include "distribution/gaussian.h"

using namespace std;

int main( int argc, char* argv[] ) {

	gaussian dist(2,10) ;
	cout << "returned a value: " << dist.integrate(1,10) << endl;
	return 0;
	
}
