/**
 * @file binary_node.h
 * Simple node structure class for binary trees
 */
 
#ifndef GENECIS_TREE_BINARY_NODE_H
#define GENECIS_TREE_BINARY_NODE_H

template <typename _T> class binary_node {

	public:
	
		_T key_value ;
		binary_node<_T>* left ;
		binary_node<_T>* right ;

};

#endif
