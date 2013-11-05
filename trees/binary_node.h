/**
 * @file binary_node.h
 * Simple node structure class for binary trees
 */
 
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

template <typename _T> class binary_node {

	public:
	
		_T key_value ;
		node<_T>* left ;
		node<_T>* right ;

};

#endif
