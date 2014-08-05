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
#include <map>

namespace genecis {
namespace math {

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
		graph_array( const char* filename ) ;
		
		/**
		 * Construct a graph_array from a vector of arc_pairs
		 */
		graph_array( const vector<arc_pair>& graph, int nvertices, int nedges ) ;
		
		/**
		 * Destructor
		 */
		virtual ~graph_array() ;
		
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
		void show_path( const int& target ) ;
		
		/**
		 * Displays the distance from target to home.
		 */
		void show_distance( const int& target ) ;
		
		/**
		 * Finds the shortest path from home to all other nodes in
		 * the graph.
		 */
		void scan_graph( const size_t& home ) ;

		/**
		 * Formated output to standard out
		 */
		friend ostream& operator<< ( ostream& os, const graph_array& graph ) {
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
		}
	
	private:
	
		int* _first_vertex ;
		int* _second_vertex ;
		int* _weight ;
		size_t _num_vertices ;
		size_t _num_edges ;
		map<int,int*> _unvisited ;
		vector<int> _distance ;
		vector<vector<int> > _path ;

		/**
		 * Recursive formula to find the shortest path length from
		 * the home node to all other nodes in the graph.
		 */
		void find_path( const int& current ) ;

		/**
		 * Finds the node in the graph with the smallest
		 * path distance.
		 */
		int find_smallest() ;

		/**
		 * Creates the graph from a vector of arc_pairs.
		 * The arc_pairs are split into the new format of
		 * _first_vertex, _second_vertex, and _weight following 
		 * as such :
		 *
		 * **How to split things up**
		 */
		void generate_graph( vector<arc_pair> g ) ;
		
		/**
		 * Creates a vector of arc_pairs from a file, which are then
		 * used to construct the arrays in the graph_array class.
		 */
		void create_graph( const char* filename ) ;

};

}	// end of namespace math
}	// end of namespace genecis
#endif
