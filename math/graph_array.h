/**
 * @file graph_array.h
 */

#ifndef GENECIS_MATH_GRAPH_ARRAY_H
#define GENECIS_MATH_GRAPH_ARRAY_H

#include "arc_pair_compare.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace genecis {
namespace math{

#define INF 99999999

class graph_array {

	public:
	
		/**
		 * Construct a graph_array from a file
		 * --File format--
		 * -Comment lines begin with a 'c'
		 * -The first non-comment line must be the problem line
		 *		with n and m as the number of nodes and arcs, respectively.
		 * -The following lines are the arc descriptors, (a U V W) where
		 *		U is the tail node ID and V is the head node ID, with
		 *		W as the weight of the arc.
		 */
		graph_array( const char* filename ) {
			create_graph( filename ) ;
		}
		
		/**
		 * Construct a graph_array from a vector of arc_pairs
		 */
		graph_array( const vector<arc_pair>& graph,
				     int nvertices, int nedges ) :
			_num_vertices(nvertices),
			_num_edges(nedges),
			_distance(nvertices),
			_visited(nvertices),
			_path(nvertices)
		{
			generate_graph( graph ) ;
		}
		
		/**
		 * Destructor
		 */
		virtual ~graph_array() {
			if( _first_vertex ) {
				delete[] _first_vertex ;
			}
			if( _second_vertex ) {
				delete[] _second_vertex ;
			}
			if( _weight ) {
				delete[] _weight ;
			}
		}
		
		friend ostream& operator<< ( ostream& os, const graph_array& graph ) ;
		
		/** Getter for the number of edges and vertices **/
		size_t numberOfVertices() const {
			return _num_vertices ;
		}
		
		size_t numberOfEdges() const {
			return _num_edges ;
		}
		
		/**
		 * Displays the path taken to the target location from
		 * home, that produces the shortest path.
		 */
		void show_path( const int& target ) {
			if ( _distance[target] < INF && _distance[target] > 1e-20 ) {
				vector<int> target_path = _path[target] ;
				cout << "Path: " ;
				for(vector<int>::iterator it=target_path.begin(); 
					it!=target_path.end(); ++it)
				{
					cout << (*it) ;
					if ( it!=target_path.end()-1 ) cout << " " ;
				}
				cout << endl ;
			} else if ( _distance[target] == INF ) {
				cout << "No path to target exists." << endl ;
			}
		}
		
		/**
		 * Displays the distance from target to home.
		 */
		void show_distance( const int& target ) {
			if( _distance[target] != INF && _distance[target] > 1e-20 ) {
				cout << "Distance: " << _distance[target] << endl ;
			} else if ( _distance[target] < 1e-20  && _distance[target] != INF ) {
				cout << "Home node, Distance: " << _distance[target] << endl ;
			}
		}
		
		/**
		 * Finds the shortest path from home to all other nodes in
		 * the graph.
		 */
		void scan_graph( const size_t& home ) {
				// clear all of the paths and put the home node on
				// as the first node in the path
			for(vector<vector<int> >::iterator it=_path.begin();
					it!=_path.end(); ++it )
			{
				it->clear() ;
			}
			for(size_t i=0;	i<_distance.size(); ++i) {
				_distance[i] = INF ;
			}
			for(size_t i=0; i<_visited.size(); ++i) {
				_visited[i] = false ;
			}
			_distance[home] = 0 ;
			find_path( home ) ;
		}
	
	private:
	
		int* _first_vertex ;
		int* _second_vertex ;
		int* _weight ;
		size_t _num_vertices ;
		size_t _num_edges ;
		vector<int> _distance ;
		vector<bool> _visited ;
		vector<vector<int> > _path ;

		/**
		 * Creates the graph from a vector of arc_pairs.
		 * The arc_pairs are split into the new format of
		 * _first_vertex, _second_vertex, and _weight following 
		 * as such :
		 *
		 * **How to split things up**
		 */
		void generate_graph( vector<arc_pair> g ) {
			stable_sort( g.begin(), g.end(), compareSecondVertex() ) ;
			stable_sort( g.begin(), g.end(), compareFirstVertex() ) ;
			_first_vertex = new int[_num_vertices] ;
			_second_vertex = new int[_num_edges] ;
			_weight = new int[_num_edges] ;
			for(size_t i=0; i<_num_edges; ++i) {
				_second_vertex[i] = g[i].second_node() ;
				_weight[i] = g[i].weight() ;
			}
			int index_range = 0 ;
			_first_vertex[0] = index_range ;
			int current = g[0].first_node() ;
			int prev ;
			for(size_t i=1; i<_num_vertices; ++i) {
				for(size_t j=index_range; j<_num_edges; ++j) {
					prev = current ;
					current = g[j].first_node() ;
					if ( prev != current ) break ;
					++index_range ;
				}
				_first_vertex[i] = index_range ;
			}
		}
		
		/**
		 * Creates a vector of arc_pairs from a file, which are then
		 * used to construct the arrays in the graph_array class.
		 */
		void create_graph( const char* filename ) {
			try {
				ifstream file( filename ) ;
				if ( file ) {
					vector<arc_pair> set ;
					string line ;
					int u ;
					int v ;
					int w ;
					char header[2] ;
					int counter = 0 ;
						// get the first line of the file
						// then skip all lines with comments
					getline( file, line ) ;
					while( line.at(0) == 'c' ) {
						getline( file, line ) ;
					}
						// this line should have information about
						// the number of edges and nodes
					if( line.at(0) == 'p' && line.at(4) == ' ' ) {
						char p ;
						char sp[2] ;
						stringstream ss(line) ;
						ss >> p >> sp >> _num_vertices >> _num_edges ;
					}
						// grab all of the arc_pairs from the file
					while( getline(file, line) ) {
						if( line.at(0) == 'a' && line.at(1) == ' ' ) {
							if ( counter % 10000 == 0 ) {
								cout << "Reading arc pair# " << counter << endl ;
							}
							stringstream ss(line) ;
							ss >> header >> u >> v >> w ;
							arc_pair p( u, v, w ) ;
							set.push_back( p ) ;
							counter++ ;
						}
					}
					set.push_back( arc_pair() ) ;			// adds the zero vertex and weight
					++_num_vertices ;
					++_num_edges ;
					generate_graph( set ) ;
				} else {
					throw -1 ;
				}
			} catch ( int e ) {
				cout << "Unable to open file: " << filename << endl ;
				exit(e) ;
			}
			_distance.resize( _num_vertices ) ;
			_visited.resize( _num_vertices ) ;
			_path.resize( _num_vertices ) ;
		}
		
		/**
		 * Recursive formula to find the shortest path length from
		 * the home node to all other nodes in the graph.
		 */
		void find_path( const int& current ) {
			if ( !_visited[current] ) {
				_visited[current] = true ;
				size_t index_min = _first_vertex[current] ;
				size_t index_max = _first_vertex[current+1] ;
				int temp_distance ;
				for(size_t i=index_min; i<index_max; ++i) {
					int k = _second_vertex[i] ;
					if ( !_visited[k] ) {
						temp_distance = _distance[current] + _weight[i] ;
						if ( temp_distance < _distance[k] ) {
							_distance[k] = temp_distance ;
							_path[k] = _path[current] ;
							_path[k].push_back( current ) ;
						}
					}
				}
				for(size_t i=index_min; i<index_max; ++i) {
					int k = _second_vertex[i] ;
					find_path( k ) ;
				}
			}
		}

};

ostream& operator<< ( ostream& os, const graph_array& graph ) {
	os << "Arc pair format: ( first node, second node, weight )" << endl ;
	for(size_t i=0; i<graph.numberOfVertices(); ++i) {
		for(int j=graph._first_vertex[i]; j<graph._first_vertex[i+1]; ++j) {
			os << "( "
			   << i << " "
			   << graph._second_vertex[j] << " "
			   << graph._weight[j] << " )"
			   << endl ;
	   }
	}
	return os ;
};

}	// end of namespace math
}	// end of namespace genecis
#endif
