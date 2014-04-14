#include "../tree/graph_tree.h"
#include <fstream>
#include <sstream>
#include <vector>

#define MAX 100
//#define DEBUG

int main() {

	vector<graph_node> tree ;
	int nodes, a, b ;
	int *nh, *d ;
	ifstream file("graph.txt") ;
	char c ;
	while( true ) {
		c = file.peek() ;
		if( isspace(c) ) break ;
		file.get() ;
	}
	file >> nodes ;
	#ifdef DEBUG
		cout << "nodes: " << nodes << endl ;
	#endif
	while( true ) {
		string line ;
		getline(file, line) ;
		while( true ) {
			c = file.peek() ;
			if( isspace(c) ) break ;
			file.get() ;
		}
		file >> a ;
		if( file.eof() ) break ;
		
		getline(file, line) ;
		while( true ) {
			c = file.peek() ;
			if( isspace(c) ) break ;
			file.get() ;
		}
		file >> b ;
		if( file.eof() ) break ;
		if( b != 0 ) {
			nh = new int[b] ;
			d = new int[b] ;

			getline(file, line) ;
			for(int j=0; j<b; ++j) {
				file >> nh[j] ;
				while( true ) {
					c = file.peek() ;
					if( isspace(c) ) break ;
					file.get() ;
				}
				file >> d[j] ;
				if( file.eof() ) break ;
			}
		}
		
		tree.push_back( graph_node(a,b,nh,d) ) ;
	}
	
	#ifdef DEBUG
		for(std::vector<graph_node>::iterator it=tree.begin(); it != tree.end(); ++it) {
			cout << "id: " << (*it)._id << endl ;
			cout << "num: " << (*it)._num_vertices << endl ;
			cout << "neighbors: " ;
			for(int i=0; i<(*it)._num_vertices; ++i) {
				cout << (*it)._vertex[i] << " " ;
			}
			cout << endl << "weights: " ;
			for(int i=0; i<(*it)._num_vertices; ++i) {
				cout << (*it)._edge[i] << " " ;
			}
			cout << endl ;
		}
	#endif

	graph_tree t(tree, 20) ;
	
	int home ;
	cout << "Please enter home vertex: " ;
	cin >> home ;
	t.scan_tree(home) ;
}
