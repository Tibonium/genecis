/**
 * @file sample_rate.h
 */

#ifndef GENECIS_SIGNAL_SAMPLE_RATE_H
#define GENECIS_SIGNAL_SAMPLE_RATE_H

#include <genecis/container/

namespace genecis {
namespace signal {

	class sample_rate {
	
		template<class C>
		static void up_sample( const C& input, C& output ) ;
		
		template<class C>
		static void down_sample( const C& input, C& output ) ;
	
	};

}	// end of namespace signal
}	// end of namespace genecis

#endif
