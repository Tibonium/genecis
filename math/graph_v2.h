/**
 *	@file graph_v2.h
 */

#ifndef GENECIS_MATH_GRAPH_V2_H
#define GENECIS_MATH_GRAPH_V2_H

#include <algorithm>
#include <iostream>
#include <map>

namespace genecis {
namespace math {

class graph_v2 {

	public:

		/**
		 * Construct a graph from a map
		 */
		graph_v2( map<int,map>int,int> > g ) : _g(g),
			_num_nodes(_g.size())
		{
			_steps = new int[_num_nodes] ;
			fill_n(_steps, _num_nodes, INF ) ;
		}
		
		/**
		 * Construct a graph from a file
		 */
		graph_v2( const char* filename ) {
			load_graph( filename ) ;
			_num_nodes = _g.size() ;
			_steps = new int[_num_nodes] ;
			fill_n(_steps, _num_nodes, INF ) ;
		}
		
		// Destructor
		virtual ~graph_v2() {
			if( _steps ) {
				delete[] _steps ;
			}
		}
	
		/**
		 * Scan the entire graph and produce the shortest path
		 * to each node starting from home.
		 */
		void scan_graph( int home, bool print=true ) {
			cout << "Home: " << home << endl ;
			cout << "Computing shortest travel distance to each vertex..." << endl ;
			char buff[64] ;
			sprintf(buff, "%4s%20s%8s", "Vertex", "Distance", "Path") ;
			cout << buff << endl ;
			find_path( home ) ;
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
	
		inline void find_path( int& start ) {
			for(int i=0; i<_num_nodes; ++i) {
				_g[i].clear() ;
			}
			_g[start]._distance = 0 ;
			fill_n(_steps, _num_nodes, INF ) ;
			find_dist( start ) ;
		}
		
	private:
	
		/**
		 * Member variables
		 */
		map<int,map<int,int> > _g ;
		int* _steps ;
		int _num_nodes ;
		
		/**
		 * Find the shortest distance from this vertex to
		 * all of its neighbors.
		 */
		inline int smallest( int* arg ) {
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
		
		/**
		 * Recurrsively searches and finds the shortest distance
		 * to each neighbor vertex from this vertex.
		 */
		void find_dist( int& current ) {
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
		
		/**
		 * loads the graph from a file
		 * see graph.txt for correct format of file
		 */
		bool load_graph( const char* filename ) {
			ifstream file( filename ) ;
			int nodes, a, b, v, e ;
			char c ;
				// get the number of nodes
			search_entry( file, nodes ) ;
			while( true ) {
				string line ;
					// find ID
				getline(file, line) ;
				search_entry( file, a ) ;
				if( file.eof() ) break ;
		
					// find the number of nodes for this ID
				getline(file, line) ;
				search_entry( file, b ) ;
				if( file.eof() ) break ;
				if( b != 0 ) {
					int v ;
					int e ;

					getline(file, line) ;
					for(int j=0; j<b; ++j) {
							// vertex
						file >> v ;
							// weight from ID to vertex
						search_entry( file, e ) ;
						_g[a][v] = e ;
						if( file.eof() ) break ;
					}
				}
			}
		}
		
		/**
		 * find the next value on the line
		 */
		void search_entry( fstream& f, int& entry ) {
			char c ;
			while( true ) {
				c = f.peek() ;
				if( isspace(c) ) break ;
				f.get() ;
			}
			f >> entry ;
		}

};

}	// end of namespace math
}	// end of namespace genecis
#endif
