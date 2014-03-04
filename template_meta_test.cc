#include <iostream>
#include <sys/time.h>

using namespace std ;

template<int n>
struct factorial {
	enum { value = n + factorial<n-1>::value };
};

template<>
struct factorial<1> {
	enum { value = 1 };
};

static int factl(int n) {
	if( n == 0 || n == 1 ) return 1 ;
	return n + factl(n-1) ;
}

int main() {

	int max = 1024 ;
	int value = 0 ;

	cout << "Starting speed test" << endl ;
	struct timeval time ;
    struct timezone zone ;
    gettimeofday( &time, &zone ) ;
    double start = time.tv_sec + time.tv_usec * 1e-6 ;
    
    value = factorial<1024>::value ;
    
	gettimeofday( &time, &zone ) ;
    double complete = time.tv_sec + time.tv_usec * 1e-6 ;
    cout << "Complete...time: " << (complete-start) << endl ;
    cout << max << "!: " << value << endl ;

	cout << "Starting speed test" << endl ;
    gettimeofday( &time, &zone ) ;
    start = time.tv_sec + time.tv_usec * 1e-6 ;
    
    value = factl(max) ;
    
	gettimeofday( &time, &zone ) ;
    complete = time.tv_sec + time.tv_usec * 1e-6 ;
    cout << "Complete...time: " << (complete-start) << endl ;
    cout << max << "!: " << value << endl ;

}
