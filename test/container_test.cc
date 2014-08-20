#include <sys/time.h>
#include <genecis/container/dynamic_array.h>
#include <genecis/container/array.h>

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
	
	array<double> k(5) ;
	array<double>::reverse_iterator i ;
	int j = 10 ;
	for(i=k.rbegin(); i!=k.rend(); ++i) {
		(*i) = j ;
		++j ;
	}
	cout << "k: " << k << endl ;
	
	array<double> m(k) ;
	cout << "m: " << m << endl ;
	j = 1 ;
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
	
	array<double> t = k - 5 ;
	cout << "t:" << t << endl ;
	cout << "k:" << k << endl ;
	k = abs(-k) ;
	cout << "abs(-k):" << k << endl ;
	
	int size = 100000 ;
	array<double> r(size) ;
	array<double> s(size) ;
	struct timeval time ;
    struct timezone zone ;
    int N = 10 ;
    gettimeofday( &time, &zone ) ;
	double start = time.tv_sec + time.tv_usec * 1e-6 ;
	for(int i=0; i<N; ++i) {
		t = multiply(r, s) ;
	}
	gettimeofday( &time, &zone ) ;
	double complete = time.tv_sec + time.tv_usec * 1e-6 ;
	cout << "Total time: " << (complete-start) << endl ;
}
