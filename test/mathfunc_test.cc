#include <iostream>
#include <cstring>
#include "../math/math_functions.h"
#include "../container/array.h"

using namespace std ;
using namespace genecis ;

int main() {

	container::array<int> v1(10) ;
	container::array<int> v2(10) ;
	container::array<int> r(10) ;
	
	for(size_t i=0; i<v1.size(); ++i) {
		v1(i) = i+1 ;
		v2(i) = i+1 ;
	}
	
	cout << "v1" << v1 << endl ;
//	math::math_functions::convolve(v1,v2,r) ;
//	cout << "result" << r << endl ;
	
	return 0 ;
}
