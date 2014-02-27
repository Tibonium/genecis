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
	
	ud_tree<double,int> myUD ;
//	string k = "some" ;
//	string k1 = "other" ;
//	string k2 = "here" ;
//	string k3 = "there" ;
//	int k = 1 ;
//	int k1 = 2 ;
//	int k2 = 3 ;
//	int k3 = 4 ;
	double k = 1.01 ;
	double k1 = 3.24 ;
	double k2 = 1049 ;
	double k3 = 2.345 ;
	myUD.insert(k,10) ;
	myUD.insert(k1,20) ;
	myUD.insert(k2,30) ;
	myUD.insert(k3,40) ;
	
	cout << myUD << endl ;
	myUD.delete_node(k1) ;
	cout << myUD << endl ;
}
