/**
 * @file sample_rate.h
 */

#ifndef GENECIS_SIGNAL_SAMPLE_RATE_H
#define GENECIS_SIGNAL_SAMPLE_RATE_H

#include <genecis/container/array.h>

namespace genecis {
namespace signal {

	class sample_rate {
	
		typedef size_t		size_type ;
	
		public:
		
			/**
			 * Takes an input signal and upsamples it by the impulse function,
			 * using the following formula:
			 *
			 *		y[j+nL] = \Sum_{k=0}^{K} x[n-k]*h[j+kL], j = 0,1,...L-1
			 *
			 * where h is the impulse response, K is the largest value of k
			 * for which h[j+kl] is non-zero, y is the upsampled signal, 
			 * x is the original signal and L is the upsample factor.
			 *
			 * @param input		signal to be upsampled
			 * @param impulse	impulse response
			 * @param L			upsample factor
			 * @param output	upsampled signal
			 */
			template<class C>
			static void upsample( const C& input, const C& impulse,
								  const size_type L, C& output )
			{
				typedef typename C::value_type		value_type ;
				value_type result ;
				size_type input_size( input.size()-1 ) ;
				size_type impulse_size( impulse.size()-1 ) ;
				output.resize( input_size*L ) ;
				size_type output_size( output.size() ) ;
				for(size_type n=0; n<output_size; ++n) {
					if( n % L == 0 ) {
						result = input[n/L] ;
					} else {
						for(size_type j=0; j<L; ++j) {
							result = 0 ;
							for(size_type k=0; k<impulse_size; ++k) {
								result += input[input_size-k] * impulse[j+k] ;
							}
						}
					}
					output[n] = result ;
				}
			}
		
			/**
			 * Takes an input signal and down samples it by the impulse function,
			 * using the following formula:
			 *
			 *		y[n] = \Sum_{k=0}^{K}-1 x[nM-k]*h[k]
			 *
			 * where h is the impulse response, K is the length of h, 
			 * M is the decimate factor, y is the downsampled signal
			 * and x is the original signal.
			 *
			 * @param input		signal to be downsampled
			 * @param impulse	impulse response
			 * @param M			decimate factor
			 * @param output	decimated signal
			 */
			template<class C>
			static void decimate( const C& input, const C& impulse,
								  const size_type M, C& output )
			{
				typedef typename C::value_type		value_type ;
				value_type result ;
				size_type input_size( input.size()/M ) ;
				size_type impulse_size( impulse.size() ) ;
				output.resize( input_size ) ;
				for(size_type n=0; n<input_size; ++n) {
					result = 0 ;
					for(size_type k=0; k<impulse_size; ++k) {
						result += input[n*M-k] * impulse[k] ;
					}
					output(n) = result ;
				}
			}
	
	};

}	// end of namespace signal
}	// end of namespace genecis

#endif
