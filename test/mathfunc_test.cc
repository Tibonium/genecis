#include <iostream>
#include <cstring>
#include <genecis/math/math_functions.h>
#include <genecis/container/array.h>

using namespace std ;
USING_NAMESPACE(genecis::container)

int main() {

	array<int> v1(10) ;
	array<int> v2(10) ;
	array<int> r(10) ;
	
	for(size_t i=0; i<v1.size(); ++i) {
		v1(i) = i+1 ;
		v2(i) = i+1 ;
	}
	
	cout << "v1" << v1 << endl ;
	genecis::math::convolve(v1,v2,r) ;
	cout << "result" << r << endl ;
	
	cout << "34!: " << genecis::math::factorial(34) << endl ;
	cout << "11 choose 3: " << genecis::math::choose(11, 3) << endl ;
}
