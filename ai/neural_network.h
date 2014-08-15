/**
 * @file neural_network.h
 */

#include "neuron.h"
#include "../containter/dynamic_array.h"

namespace genecis {
namespace ai {

class neural_network {

	public:
	
		/****/
		neural_network() {}
		
		/**
		 * Destructor - Deletes all memories in the neural network
		 */
		virtual ~neural_network() {
			for(dynamic_array<neuron>::iterator i=__network.begin();
					i!=__network.end(); ++i)
			{
				delete i->memory ;
			}
			delete __network ;
		}
		
	private:
	
		/**
		 * Container of the neural network of neurons.
		 */
		dynamic_array<neuron> __network ;
	
		

};

}
}
