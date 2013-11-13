/**
 * @file btree_node.h
 */
 
#ifndef TREES_BTREE_NODE_H
#define TREES_BTREE_NODE_H

template <class _type, int _size> class btree_node {

	private:
	
		int num_keys ;
		_type key_list[_size-1] ;
		btree_node<_type,_size>* child[_size] ;
	
}

#endif
