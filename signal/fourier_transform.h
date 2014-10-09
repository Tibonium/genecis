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
		
			/**
			 * Produces the Discrete Fourier-transform of a data set
			 * using the radix-2 Cooley-Tukey algorithm. Takes a real
			 * data set and returns a complex set.
			 *
			 * X_k = \Sum_{m=0}^{N/2-1} x_{2m}*e^{\frac{-2\pi i}{N} (2m)k}
			 *		+ \Sum_{m=0}^{N/2-1} x_{2m+1}*e^{\frac{-2\pi i}{N} (2m+1)k}
			 *
			 * @param input		input signal
			 * @param output	DFT of input signal
			 */
			template<class R, class C>
			static void discrete( const R& input, C& output ) {
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
					output[k] = result ;
				}
			}
			
			/**
			 * Produces the Inverse Discrete Fourier-transform of a
			 * data set using the radix-2 Cooley-Tukey algorithm.
			 * Takes a complex set of data and returns a real set.
			 *
			 * x_k = \frac{1}{N} \left(
			 *		\Sum_{m=0}^{N/2-1} X_{2m}*e^{\frac{2\pi i}{N} (2m)k}
			 *	 + \Sum_{m=0}^{N/2-1} X_{2m+1}*e^{\frac{2\pi i}{N} (2m+1)k} \right)
			 *
			 * @param input		DFT of a signal
			 * @param output	Inverse DFT of the signal
			 */
			template<class C, class R>
			static void inverse( const C& input, R& output ) {
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
					result /= N ;
					output[k] = std::abs(result) ;
				}
			}
			
			/**
			 * Converts an array of complex numbers to an array of
			 * reals. This is implemented because currently the
			 * container_expression has yet to implement this
			 * capability. In the furture this will be removed when
			 * the container_expression class has this capability.
			 */
			template<class Cplx, class Real>
			static void convert_real( const Cplx& input, Real& output ) {
				typedef typename Cplx::size_type	size_type ;
				size_type s( input.size() ) ;
				for(size_type i=0; i<s; ++i)
					output(i) = std::abs(input(i)) ;
			}
	
	};

}	// end of namespace signal
}	// end of namespace genecis

#endif
