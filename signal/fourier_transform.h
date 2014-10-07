/**
 * @file fourier_transform.h
 */
 
#ifndef GENECIS_SIGNAL_FOURIER_TRANSFORM_H
#define GENECIS_SIGNAL_FOURIER_TRANSFORM_H

#include <cmath>
#include <complex>

namespace genecis {
namespace signal {

	class fourier_transform {
	
		typedef size_t		size_type ;
	
		public:
		
			template<class C>
			static void discrete( const C& input, C& output ) {
				typedef typename C::value_type		value_type ;
				typedef std::complex<value_type>	complex_num ;
				size_type N( input.size() ) ;
				output.resize( N ) ;
				complex_num result ;
				for(size_type k=0; k<N; ++k) {
					result = complex_num(0.0,0.0) ;
					for(size_type n=0; n<N; ++n) {
						std::complex<double> a( 0.0, -2.0*M_PI*k*n/N ) ;
						result += input[n] * std::exp(a) ;
					}
					result /= std::sqrt(N) ;
					output[k] = std::abs(result) ;
				}
			}
	
	};

}	// end of namespace signal
}	// end of namespace genecis

#endif
