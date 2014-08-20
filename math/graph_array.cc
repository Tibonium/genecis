/**
 * @file graph_array.cc
 */

#include <genecis/math/graph_array.h>

using namespace genecis::math ;
 
/**
 * Construct a graph from file
 */
graph_array::graph_array( const char* filename ) {
	create_graph( filename ) ;
}

/**
 * Construct a graph_array from a vector of arc_pairs
 */
graph_array::graph_array( const vector<arc_pair>& graph,
		     int nvertices, int nedges ) :
	_num_vertices(nvertices),
	_num_edges(nedges),
	_distance(nvertices),
	_path(nvertices)
{
	generate_graph( graph ) ;
}

/**
 * Destructor
 */
graph_array::~graph_array() {
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

/**
 * Displays the path taken to the target location from
 * home, that produces the shortest path.
 */
void graph_array::show_path( const int& target ) {
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
void graph_array::show_distance( const int& target ) {
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
void graph_array::scan_graph( const size_t& home ) {
		// clear all of the paths and put the home node on
		// as the first node in the path
	for(vector<vector<int> >::iterator it=_path.begin();
			it!=_path.end(); ++it )
	{
		it->clear() ;
	}
	for(size_t i=0;	i<_distance.size(); ++i) {
		_distance[i] = INF ;
		_unvisited[i] = &_distance[i] ;
	}
	_distance[home] = 0 ;
	find_path( home ) ;
}

/**
 * Recursive formula to find the shortest path length from
 * the home node to all other nodes in the graph.
 */
void graph_array::find_path( const int& current ) {
	if ( _unvisited[current] ) {
		_unvisited.erase( current ) ;
		size_t index_min = _first_vertex[current] ;
		size_t index_max = _first_vertex[current+1] ;
		int temp_distance ;
		for(size_t i=index_min; i<index_max; ++i) {
			int k = _second_vertex[i] ;
			if ( _unvisited[k] ) {
				temp_distance = _distance[current] + _weight[i] ;
				if ( temp_distance < _distance[k] ) {
					_distance[k] = temp_distance ;
					_path[k] = _path[current] ;
					_path[k].push_back( current ) ;
				}
			}
		}
		int next = find_smallest() ;
		find_path( next ) ;
	}
}


/**
 * Finds the node in the graph with the smallest
 * path distance.
 */
int graph_array::find_smallest() {
	int m = INF ;
	int v = 0 ;
	for(map<int,int*>::iterator it=_unvisited.begin(); 
			it!=_unvisited.end(); ++it)
	{
		if( it->second ) {
			if( (*it->second) < m ) {
				m = (*it->second) ;
				v = it->first ;
			}
		}
	}
	return v ;
}

/**
 * Creates the graph from a vector of arc_pairs.
 */
void graph_array::generate_graph( vector<arc_pair> g ) {
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
void graph_array::create_graph( const char* filename ) {
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
	_path.resize( _num_vertices ) ;
}
