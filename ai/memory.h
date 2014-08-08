/**
 * @file memory.h
 */

#include "action.h"

namespace genecis {
namespace ai {

class memory {

	public:
	
		/**
		 * Constructor - Takes a pointer to an action obj.
		 * The memory is incharge of deleteing the action.
		 *
		 * @param a		The action obj for this memory.
		 */
		memory( action* a ) : __a {}
		
		/**
		 * Destructor - deletes the action stored in this memory.
		 */
		virtual ~memory() {
			if( __a ) {
				delete __a ;
			}
		}

	private:
	
		/**
		 * The action that is associated with this memory.
		 */
		action* __a ;
	
		
};

}
}
