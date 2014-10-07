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

template<class Cplx, class Real>
void convert_real( const Cplx& input, Real& output ) {
	typedef typename Cplx::size_type	size_type ;
	size_type s( input.size() ) ;
	for(size_type i=0; i<s; ++i)
		output(i) = std::abs(input(i)) ;
}

int main() {

	typedef complex<double>		value_type ;
	typedef array<value_type>	container ;
	typedef size_t				size_type ;

	size_type N = 10 ;
	
	value_type sig[10] ;
	for(size_type i=0; i<N; ++i) {
		sig[i] = (i<5) ? value_type(1,0) : value_type(0,0) ;
	}

	container input( sig, N ) ;
	container impulse ;
	container output ;

	fourier_transform::discrete( input, output ) ;
	
	array<double> r(output.size()) ;

	cout << "input signal:" << input << endl ;
	cout << "dft signal:" << output << endl ;
	convert_real( output, r ) ;
	cout << "real signal:" << r << endl ;
	
	fourier_transform::inverse( output, impulse ) ;
	cout << "inverse dft signal:" << impulse << endl ;
	convert_real( impulse, r ) ;
	cout << "real inverse signal:" << r << endl ;
	
}
