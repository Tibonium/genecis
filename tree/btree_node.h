/**
 * @file btree_node.h
 */
 
#ifndef GENECIS_TREE_BTREE_NODE_H
#define GENECIS_TREE_BTREE_NODE_H

template <class _type, int _size> class btree_node {

	private:
	
		int num_keys ;
		_type key_ring[_size-1] ;
		btree_node<_type,_size>* child[_size] ;
	
}

#endif
