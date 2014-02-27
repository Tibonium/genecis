/**
 * @file binary_node.h
 * Simple node structure class for binary trees
 */
 
#ifndef TREE_BINARY_NODE_H
#define TREE_BINARY_NODE_H

template <typename _T> class binary_node {

	public:
	
		_T key_value ;
		binary_node<_T>* left ;
		binary_node<_T>* right ;

};

#endif
