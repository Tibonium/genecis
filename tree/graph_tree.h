/**
 *	@file graph_tree.h
 */

#ifndef TREE_GRAPH_TREE_H
#define TREE_GRAPH_TREE_H

#include "graph_node.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std ;

class graph_tree {

	public:
	
		void scan_tree(int home) {
			cout << "Home: " << home << endl ;
			cout << "Computing shortest travel distance to each node..." << endl ;
			char buff[64] ;
			sprintf(buff, "%4s%20s%8s", "Node", "Distance", "Path") ;
			cout << buff << endl ;
			for(int i=0; i<_num_nodes; ++i) {
				if( i != home ) {
					vector<int> o = find_path(home, i) ;
					if( _tree[i]._steps < 1000 ) {
						sprintf(buff, "%4d%20d%3s", i, _tree[i]._steps, "" ) ;
						cout << buff ;
						for(unsigned k=0; k<o.size(); ++k) {
							cout << " " << o[k] ;
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
	
		vector<int> find_path(int start, int finish) {
			vector<int> path ;
			int n = _tree[finish]._num_neighbors ;
			if( n != 0 ) {
				for(int i=0; i<_num_nodes; ++i) {
					_tree[i].clear() ;
				}
				find_dist(start, finish, path) ;
			}
			return path ;
		}
		
		graph_tree( graph_node* tree, int n ) : _tree(tree),
			_num_nodes(n)
		{}
		
		~graph_tree() {}
		
	private:
	
		// Array of all the graph_nodes in the tree
		graph_node* _tree ;
		int _num_nodes ;
		
		graph_node operator[] (int n) {
			return _tree[n] ;
		}
		
		void find_dist(int& current, int& end, vector<int>& path) {
			if( current != end ) {
				int n = _tree[current]._num_neighbors ;
				int temp ;
				int small = 999 ;
				int p ;
				for(int i=0; i<n; ++i) {
					int k = _tree[current]._neighborhood[i] ;
					if( !_tree[k]._checked ) {
						if( _tree[k]._steps > 999 ) {
							_tree[k]._steps = _tree[current]._distance[i] ;
						} else {
							temp = _tree[current]._steps + _tree[current]._distance[i] ;
							_tree[k]._steps = min(_tree[k]._steps, temp) ;
						}
						if( _tree[current]._distance[i] < small ) {
							small = _tree[current]._distance[i] ;
							p = _tree[current]._neighborhood[i] ;
						}
					}
				}
				_tree[current]._checked = true ;
				path.push_back( current ) ;
				find_dist(p, end, path) ;
			}
		}

};

#endif
