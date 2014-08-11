#include "../container/dynamic_array.h"
#include "../container/array.h"

using namespace genecis::container ;

int main() {
	
	dynamic_array<int> a ;
	dynamic_array<int> b ;
	for(int i=0; i<a.size(); ++i) {
		a(i) = i + 1 ;
		b(i) = i + 1 ;
	}
	cout << a.str() << endl ;
	cout << b.str() << endl ;
	dynamic_array<int> c = a + b ;
	cout << c.str() << endl ;
	a(10) = 10 ;
	cout << a.str() << endl ;
	
	array<int> k(5) ;
	array<int>::reverse_iterator i=k.rbegin() ;
	for(unsigned j=0; j<k.size(); ++j) {
		(*--i) = j+10 ;
//		i-- ;
	}
	cout << k << endl ;
	
}
