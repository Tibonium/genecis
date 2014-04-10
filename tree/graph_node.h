/**
 * @file graph_node.h
 */
 
#ifndef TREE_GRAPH_NODE_H
#define TREE_GRAPH_NODE_H

#include <cstdio>

class graph_node {

	public:
		
		int _identity ;
		int _num_neighbors ;
		int* _neighborhood ;
		int* _distance ;
		int _steps ;
		bool _checked ;
		
		void clear() {
			_steps = 1000 ;
			_checked = false ;
		}
		
		graph_node(int id, int n, int* nh, int* d) :
			_identity(id), _num_neighbors(n)
		{
			if( _num_neighbors == 0 ) {
				_neighborhood = NULL ;
				_distance = 0 ;
			} else {
				_neighborhood = nh ;
				_distance = d ;
			}
		}

};

#endif
