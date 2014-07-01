/**
 * @file graph_node.h
 */
 
#ifndef GENECIS_MATH_GRAPH_NODE_H
#define GENECIS_MATH_GRAPH_NODE_H

#include <cstdio>
#include <vector>

namespace genecis {
namespace math {

#define INF 1048576 	// 2^20

using namespace std ;

class graph_node {

	public:
		
		int _id ;
		int _num_vertices ;
		int* _vertex ;
		int* _edge ;
		int _distance ;
		bool _visited ;
		vector<int> _path ;
		
		void clear() {
			_distance = INF ;
			_visited = false ;
		}
		
		graph_node(int id, int n, int* v, int* d) :
			_id(id), _num_vertices(n)
		{
			if( _num_vertices == 0 ) {
				_vertex = NULL ;
				_edge = NULL ;
			} else {
				_vertex = v ;
				_edge = d ;
			}
		}
		
		graph_node() {
			if( _vertex != NULL ) {
				delete _vertex ;
			}
			if( _edge != NULL ) {
				delete _edge ;
			}
		}

};

}	// end of namespace math
}	// end of namespace genecis
#endif
