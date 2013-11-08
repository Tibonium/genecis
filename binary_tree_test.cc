#include "trees/binary_tree.h"
#include <stdlib.h>
#include <time.h>

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
	cout << endl;
	
}
