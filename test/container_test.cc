#include "../container/dynamic_array.h"

using namespace genecis::container ;

int main() {
	
	dynamic_array<int> a ;
	string s = a.str() ;
	cout << s << endl ;
	for(int i=0; i<a.size(); ++i) {
		a(i) = i + 1 ;
	}
	a(10) = 10 ;
	s = a.str() ;
	cout << s << endl ;
	
}
