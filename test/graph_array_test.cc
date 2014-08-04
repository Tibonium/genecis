#include "../math/graph_array.h"

using namespace genecis::math ;

int main() {

	const char* grname = "rome99.gr" ;
	int home ;
	int target ;
	graph_array graph( grname ) ;
	cout << "Finished reading " << graph.numberOfVertices()
		 << " and " << graph.numberOfEdges() << " edges." << endl ;
	cout << "Please enter the node would you like to search from: " ;
	cin >> home ;
	graph.scan_graph(home) ;
	do {
		cout << "Choose a node to view its weight and path (-1 to exit): " ;
		cin >> target ;
		
		if( target == -1 ) break ;
		
		if( target >= 0 && unsigned(target) < graph.numberOfVertices() ) {
			graph.show_distance( target ) ;
			graph.show_path( target ) ;
		} else {
			cout << "The ID you have chosen is not a valid ID." << endl ;
		}
	} while (true) ;

//	cout << graph ;
	
}
