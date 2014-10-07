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
				typedef typename C::value_type::value_type		value_type ;
				typedef typename C::value_type					complex_num ;
				size_type N( input.size() ) ;
				size_type half_N( N/2 ) ;
				output.resize( N ) ;
				complex_num result ;
				value_type r = -2.0*M_PI/N ;
				for(size_type k=0; k<N; ++k) {
					result = complex_num(0.0,0.0) ;
					for(size_type m=0; m<half_N; ++m) {
						complex_num even( 0.0, r*k*(2*m) ) ;
						complex_num odd( 0.0, r*k*(2*m+1) ) ;
						result += input[2*m] * std::exp(even) ;
						result += input[2*m+1] * std::exp(odd) ;
					}
					result /= std::sqrt(N) ;
					output[k] = result ;
				}
			}
			
			template<class C>
			static void inverse( const C& input, C& output ) {
				typedef typename C::value_type::value_type		value_type ;
				typedef typename C::value_type					complex_num ;
				size_type N( input.size() ) ;
				size_type half_N( N/2 ) ;
				output.resize( N ) ;
				complex_num result ;
				value_type r = 2.0*M_PI/N ;
				for(size_type k=0; k<N; ++k) {
					result = complex_num(0.0,0.0) ;
					for(size_type m=0; m<half_N; ++m) {
						complex_num even( 0.0, r*k*(2*m) ) ;
						complex_num odd( 0.0, r*k*(2*m+1) ) ;
						result += input[2*m] * std::exp(even) ;
						result += input[2*m+1] * std::exp(odd) ;
					}
					result /= std::sqrt(N) ;
					output[k] = result ;
				}
			}
	
	};

}	// end of namespace signal
}	// end of namespace genecis

#endif
