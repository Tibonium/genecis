#include <ctime>
#include <cstdlib>
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

	typedef double				value_type ;
	typedef complex<value_type>	complex_num ;
	typedef array<complex_num>	container_cplx ;
	typedef array<value_type>	container_real ;
	typedef size_t				size_type ;

	size_type N = 100 ;
	
	value_type sig[100] ;
	srand(time(0)) ;
	for(size_type i=0; i<N; ++i) {
		sig[i] = std::sin(30*2*M_PI*i/100) + rand()%2 - 1/2 ;
	}

	container_real input( sig, N ) ;
	container_real impulse ;
	container_cplx output ;

	fourier_transform::discrete( input, output ) ;

	impulse.resize( N ) ;
	fourier_transform::convert_real( output, impulse ) ;
	cout << "real dft sig:" << impulse << endl ;
	cout << "input signal:" << input << endl ;
//	cout << "dft signal:" << output << endl ;
//	
//	fourier_transform::inverse( output, impulse ) ;
//	cout << "inverse dft signal:" << impulse << endl ;
	
}
