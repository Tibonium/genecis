/**
 * @file avl_node.h
 */
 
#ifndef TREES_AVL_NODE_H
#define TREES_AVL_NODE_H

template <class _type> class avl_node {

	public:
	
		_type key ;
		char balance ;
		avl_node<_type>* left ;
		avl_node<_type>* right ;
		avl_node<_type>* parent ;

};

#endif
