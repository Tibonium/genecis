/**
 * @file memory.h
 */
#pragma once

#include <genecis/container/array.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(ai)

USING_NAMESPACE(container)

/**
 * TODO: This has yet to be created
 */
class action ;

class memory {
public:

	typedef memory		self_type ;
	typedef array<action*>		list_type ;

	/**
	 * Constructor
	 */
	memory() {
		_action_list = new list_type ;
	}
	
	/**
	 * Destructor - deletes the action stored in this memory.
	 */
	virtual ~memory() {
		if( _action_list ) {
			delete _action_list ;
		}
	}

private:

	/**
	 * The action that is associated with this memory.
	 */
	array<action*> _action_list ;
	
};

END_NAMESPACE
END_NAMESPACE
