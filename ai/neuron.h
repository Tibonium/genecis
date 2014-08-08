/**
 * @file neuron.h
 */

#include "memory.h"

namespace genecis {
namespace ai {

enum awareness { AWAKE = 1, ASLEEP = -1 }

struct neuron {

	/**
	 * Pointer to the connecting neuron
	 */
	neuron* __n ;
	
	/**
	 * Memory that stored in this neuron.
	 */
	memory* __memory ;
	
	/**
	 * Connectiveness of this neuron with other neurons
	 */
	awareness __state ;
	
	/**
	 * The 
	 */
	double __weight ;

};

}	// end of namespace ai
}	// end of namesapce genecis


