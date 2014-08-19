#include "../container/dynamic_array.h"
#include "../container/array.h"

using namespace genecis::container ;
using namespace std ;

int main() {
	
	dynamic_array<int> a(5) ;
	dynamic_array<int> b(5) ;
	for(size_t i=0; i<a.size(); ++i) {
		a(i) = i + 1 ;
		b(i) = i + 1 ;
	}
	cout << "a: " << a << endl ;
	cout << "b: " << b << endl ;
	dynamic_array<int> c = a + b ;
	cout << "c: " << c << endl ;
	a(10) = 10 ;
	cout << "a: " << a << endl ;
	
	array<int> k(5) ;
	array<int>::reverse_iterator i ;
	int j = 10 ;
	for(i=k.rbegin(); i!=k.rend(); ++i) {
		(*i) = j ;
		++j ;
	}
	cout << "k: " << k << endl ;
	
	array<int> m(k) ;
	cout << "m: " << m << endl ;
	j = 50 ;
	for(i=m.rbegin(); i!=m.rend(); ++i) {
		(*i) = j ;
		++j ;
	}
	cout << "m:" << m << endl ;
	k = m ;
	cout << "k: " << k << endl ;
	
	k += 5 ;
	cout << "k+5:" << k << endl ;
	k -= 10 ;
	cout << "k-10:" << k << endl ;
	k *= 10 ;
	cout << "k*7:" << k << endl ;
	k /= 2 ;
	cout << "k/2:" << k << endl ;
	
	array<int> t = k + m ;
	cout << "k+m:" << t << endl ;
}
