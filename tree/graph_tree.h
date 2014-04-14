/**
 *	@file graph_tree.h
 */

#ifndef TREE_GRAPH_TREE_H
#define TREE_GRAPH_TREE_H

#include "graph_node.h"
#include <algorithm>
#include <iostream>

class graph_tree {

	public:
	
		void scan_tree(int home) {
			cout << "Home: " << home << endl ;
			cout << "Computing shortest travel distance to each node..." << endl ;
			char buff[64] ;
			sprintf(buff, "%4s%20s%8s", "Node", "Distance", "Path") ;
			cout << buff << endl ;
			find_path(home) ;
			for(int i=0; i<_num_nodes; ++i) {
				if( i != home ) {
					if( _tree[i]._distance < INF ) {
						sprintf(buff, "%4d%20d%3s", i, _tree[i]._distance, "" ) ;
						cout << buff ;
						for(std::vector<int>::iterator it=_tree[i]._path.begin();
								it!=_tree[i]._path.end()-1; ++it) {
							cout << " " << *it ;
						}
						cout << endl ;
					} else {
						sprintf(buff, "%4d%20s%3s", i, "No path exists", "") ;
						cout << buff << endl ;
					}
				} else {
					char buff[64] ;
					sprintf(buff, "%4d%20d%3s", i, 0, "") ;
					cout << buff << " " << i << endl ;
				}
			}
		}
	
		inline void find_path(int& start) {
			for(int i=0; i<_num_nodes; ++i) {
				_tree[i].clear() ;
			}
			_tree[start]._distance = 0 ;
			fill_n(_steps, _num_nodes, INF ) ;
			find_dist( start ) ;
		}
		
		// Constructor
		graph_tree( vector<graph_node> tree, int n ) : _tree(tree),
			_num_nodes(n)
		{
			_steps = new int[_num_nodes] ;
			fill_n(_steps, _num_nodes, INF ) ;
		}
		
		// Destructor
		~graph_tree() {
			if( _steps != NULL ) {
				delete _steps ;
			}
		}
		
	private:
	
		// Array of all the graph_nodes in the tree
		vector<graph_node> _tree ;
		int* _steps ;
		int _num_nodes ;
		
		graph_node operator[] (int n) {
			return _tree[n] ;
		}
		
		inline int smallest(int* arg) {
			int m = INF ;
			int v ;
			for(int i=0; i<_num_nodes; ++i) {
				if( arg[i] < m && !_tree[i]._visited ) {
					m = arg[i] ;
					v = i ;
				}
			}
			return v ;
		}
		
		void find_dist(int& current) {
			if( !_tree[current]._visited ) {
				int temp ;
				_tree[current]._path.push_back( current ) ;
				for(int i=0; i<_tree[current]._num_vertices; ++i) {
					int k = _tree[current]._vertex[i] ;
					if( !_tree[k]._visited ) {
						temp = _tree[current]._distance + _tree[current]._edge[i] ;
						if( temp < _steps[k] ) {
							_steps[k] = temp ;
						}
						if( temp < _tree[k]._distance ) {
							_tree[k]._distance = temp ;
							_tree[k]._path = _tree[current]._path ;
						}
					}
				}
				_tree[current]._visited = true ;
				int next = smallest(_steps) ;
				find_dist( next ) ;
			}
		}

};

#endif
