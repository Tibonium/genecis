/**
 * @file neural_network.h
 */
#pragma once

#include <genecis/ai/neuron.h>
#include <genecis/container/dynamic_array.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(ai)

USING_NAMESPACE(container)

class neural_network {
public:

	typedef neural_network			self_type ;
	typedef dynamic_array<neuron>	container_type ;

	/**
	 * Constructor
	 */
	neural_network() {}
	
	/**
	 * Destructor
	 */
	virtual ~neural_network() {}
	
private:

	/**
	 * Container of the neural network of neurons.
	 */
	container_type _network ;

};

END_NAMESPACE
END_NAMESPACE
