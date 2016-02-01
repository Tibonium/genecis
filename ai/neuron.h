/**
 * @file neuron.h
 */
#pragma once

#include <genecis/ai/memory.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(ai)

enum awareness { AWAKE = 1, ASLEEP = -1 };

struct neuron {

	/**
	 * Pointer to the connecting neuron
	 */
	neuron* _n ;
	
	/**
	 * Memory that stored in this neuron.
	 */
	memory* _memory ;
	
	/**
	 * Connectiveness of this neuron with other neurons
	 */
	awareness _state ;
	
	/**
	 * The 
	 */
	double _weight ;

};

END_NAMESPACE
END_NAMESPACE
