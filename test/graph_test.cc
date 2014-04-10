#include "../tree/graph_tree.h"

int main() {

	int id = 0 ;
	int n = 3 ;
	int nh0[] = {1, 10, 15} ;
	int d0[] = {43, 26, 34} ;
	graph_node n0(id, n, nh0, d0) ;
	
	id = 1 ;
	n = 4 ;
	int nh1[] = {2, 7, 16, 19} ;
	int d1[] = {8, 15, 14, 18} ;
	graph_node n1(id, n, nh1, d1) ;
	
	id = 2 ;
	n = 2 ;
	int nh2[] = {3, 16} ;
	int d2[] = {16, 26} ;
	graph_node n2(id, n, nh2, d2) ;

	id = 3 ;
	n = 3 ;
	int nh3[] = {2, 4, 10} ;
	int d3[] = {16, 50, 33} ;
	graph_node n3(id, n, nh3, d3) ;
	
	id = 4 ;
	n = 3 ;
	int nh4[] = {3, 10, 19} ;
	int d4[] = {50, 27, 6} ;
	graph_node n4(id, n, nh4, d4) ;
	
	id = 5 ;
	n = 3 ;
	int nh5[] = {13, 14, 17} ;
	int d5[] = {44, 23, 5} ;
	graph_node n5(id, n, nh5, d5) ;
	
	id = 6 ;
	n = 2 ;
	int nh6[] = {15, 18} ;
	int d6[] = {2, 16} ;
	graph_node n6(id, n, nh6, d6) ;
		
	id = 7 ;
	n = 2 ;
	int nh7[] = {1, 18} ;
	int d7[] = {15, 19} ;
	graph_node n7(id, n, nh7, d7) ;
	
	id = 8 ;
	n = 0 ;
	int nh8[] = {} ;
	int d8[] = {} ;
	graph_node n8(id, n, nh8, d8) ;
	
	id = 9 ;
	n = 0 ;
	int nh9[] = {} ;
	int d9[] = {} ;
	graph_node n9(id, n, nh9, d9) ;
	
	id = 10 ;
	n = 3 ;
	int nh10[] = {0, 3, 4} ;
	int d10[] = {26, 33, 27} ;
	graph_node n10(id, n, nh10, d10) ;
	
	id = 11 ;
	n = 4 ;
	int nh11[] = {10, 12, 14, 17} ;
	int d11[] = {48, 3, 7, 20} ;
	graph_node n11(id, n, nh11, d11) ;
	
	id = 12 ;
	n = 2 ;
	int nh12[] = {11, 13} ;
	int d12[] = {3, 20} ;
	graph_node n12(id, n, nh12, d12) ;
	
	id = 13 ;
	n = 3 ;
	int nh13[] = {5, 12, 19} ;
	int d13[] = {44, 20, 28} ;
	graph_node n13(id, n, nh13, d13) ;
	
	id = 14 ;
	n = 2 ;
	int nh14[] = {5, 11} ;
	int d14[] = {23, 28} ;
	graph_node n14(id, n, nh14, d14) ;
	
	id = 15 ;
	n = 2 ;
	int nh15[] = {0, 6, 7} ;
	int d15[] = {34, 41, 54} ;
	graph_node n15(id, n, nh15, d15) ;
	
	id = 16 ;
	n = 2 ;
	int nh16[] = {1, 2} ;
	int d16[] = {14, 26} ;
	graph_node n16(id, n, nh16, d16) ;
	
	id = 17 ;
	n = 3 ;
	int nh17[] = {5, 11, 18} ;
	int d17[] = {5, 20, 16} ;
	graph_node n17(id, n, nh17, d17) ;
	
	id = 18 ;
	n = 3 ;
	int nh18[] = {6, 7, 17} ;
	int d18[] = {16, 19, 16} ;
	graph_node n18(id, n, nh18, d18) ;
	
	id = 19 ;
	n = 3 ;
	int nh19[] = {1, 4, 13} ;
	int d19[] = {18, 6, 28} ;
	graph_node n19(id, n, nh19, d19) ;

	cout << "n10._neighborhood: " << n10._neighborhood[0]
		 << " " << n10._neighborhood[1] << " "
		 << n10._neighborhood[2] << endl ;
	cout << "n10._distance: " << n10._distance[0]
		 << " " << n10._distance[1] << " "
		 << n10._distance[2] << endl ;

	
	graph_node tree[] = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10,
						 n11, n12, n13, n14, n15, n16, n17, n18, n19} ;
	graph_tree t(tree, 20) ;
	
	t.scan_tree(10) ;
}
