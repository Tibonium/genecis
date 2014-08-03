/**
 *	@file graph.h
 */

#ifndef GENECIS_MATH_GRAPH_H
#define GENECIS_MATH_GRAPH_H

#include "graph_node.h"
#include <algorithm>
#include <iostream>

namespace genecis {
namespace math {

class graph {

	public:
	
		void scan_graph(int home) {
			cout << "Home: " << home << endl ;
			cout << "Computing shortest travel distance to each node..." << endl ;
			char buff[64] ;
			sprintf(buff, "%4s%20s%8s", "Node", "Distance", "Path") ;
			cout << buff << endl ;
			find_path(home) ;
			for(int i=0; i<_num_nodes; ++i) {
				if( i != home ) {
					if( _g[i]._distance < INF ) {
						sprintf(buff, "%4d%20d%3s", i, _g[i]._distance, "" ) ;
						cout << buff ;
						for(std::vector<int>::iterator it=_g[i]._path.begin();
								it!=_g[i]._path.end()-1; ++it) {
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
				_g[i].clear() ;
			}
			_g[start]._distance = 0 ;
			fill_n(_steps, _num_nodes, INF ) ;
			find_dist( start ) ;
		}
		
		// Constructor
		graph( vector<graph_node> g, int n ) : _g(g),
			_num_nodes(n)
		{
			_steps = new int[_num_nodes] ;
			fill_n(_steps, _num_nodes, INF ) ;
		}
		
		// Destructor
		~graph() {
			if( _steps ) {
				delete[] _steps ;
			}
		}
		
	private:
	
		// Vector of the vertices of the graph with edges
		vector<graph_node> _g ;
		int* _steps ;
		int _num_nodes ;
		
		graph_node operator[] (int n) {
			return _g[n] ;
		}
		
		inline int smallest(int* arg) {
			int m = INF ;
			int v = 0 ;
			for(int i=0; i<_num_nodes; ++i) {
				if( arg[i] < m && !_g[i]._visited ) {
					m = arg[i] ;
					v = i ;
				}
			}
			return v ;
		}
		
		void find_dist(int& current) {
			if( !_g[current]._visited ) {
				int temp ;
				_g[current]._path.push_back( current ) ;
				for(int i=0; i<_g[current]._num_vertices; ++i) {
					int k = _g[current]._vertex[i] ;
					if( !_g[k]._visited ) {
						temp = _g[current]._distance + _g[current]._edge[i] ;
						if( temp < _steps[k] ) {
							_steps[k] = temp ;
						}
						if( temp < _g[k]._distance ) {
							_g[k]._distance = temp ;
							_g[k]._path = _g[current]._path ;
						}
					}
				}
				_g[current]._visited = true ;
				int next = smallest(_steps) ;
				find_dist( next ) ;
			}
		}

};

}	// end of namespace math
}	// end of namespace genecis
#endif
