#include <iostream>
#include <cmath>
#include <genecis/container/array.h>
#include <genecis/signal/sample_rate.h>
#include <genecis/signal/fourier_transform.h>

using namespace genecis::container ;
using namespace genecis::signal ;
using namespace std ;

double sinc( double x ) {
	double result = 1 ;
	if( x != 0 ) result = sin(x) / x ;
	return result ;
}

int main() {

	typedef double		value_type ;
	typedef array<value_type>	container ;
	typedef size_t				size_type ;

//	size_type factor = 5 ;
	size_type N = 100 ;
	
	value_type sig[100] ;
	for(size_type i=0; i<N; ++i) {
		sig[i] = (i<50) ? 1 : 0 ;
	}
//	value_type imp[] = { sinc(-10), sinc(-8), sinc(-6), sinc(-4), 
//						 sinc(-2), sinc(0), sinc(2), sinc(4),
//						 sinc(6), sinc(8) } ;

	container input( sig, N ) ;
//	container impulse( imp, N ) ;
	container output ;
	
//	cout << "impulse:" << impulse << endl ;
	
//	sample_rate::upsample( input, impulse, factor, output ) ;
	fourier_transform::discrete( input, output ) ;
	
	cout << "input signal:" << input << endl ;
	cout << "dft signal:" << output << endl ;
	
}
