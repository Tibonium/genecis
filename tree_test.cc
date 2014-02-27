#include "tree/trees.h"
#include <ctime>

int main() {

	cout << "Let's do some binary tree tests!" << endl;
	srand( time(NULL) ) ;
	
	int num_keys = 5 ;
	int dummy_key ;
	binary_tree<int> mytree ;
	for(int i=0; i < num_keys; ++i) {
		dummy_key = rand() % 100 + 1 ;
		cout << "setting a leaf to: " << dummy_key << endl;
		mytree.insert(dummy_key) ;
	}
	
	mytree.printdata() ;
	
	avl_tree<int> myAVL ;
	myAVL.insert(10) ;
	myAVL.print_tree() ;
	
	ud_tree<int> myUD ;
	string k = "some" ;
	string k1 = "other" ;
	myUD.insert(k,10) ;
	cout << "key=" << k << " "
		 << ((myUD.find_key(k)) ? "is " : "is not ")
		 << "within the tree" << endl ;
	cout << "data for some is: " << myUD.find_data(k) << endl ;
	
	myUD.insert(k1,20) ;
	cout << "key=" << k1 << " "
		 << ((myUD.find_key(k1)) ? "is " : "is not ")
		 << "within the tree" << endl ;
	cout << "data for other is: " << myUD.find_data(k1) << endl ;	
	
	cout << "my tree has " << myUD.nodecount()
		 << (( myUD.nodecount() > 1 ) ? " nodes." : "node") << endl ;
		 
	cout << myUD << endl ;
}
