#include "../tree/trees.h"
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
	
	if(true){
	ud_tree<string,int> myUD ;
	string k = "some" ;
	string k1 = "other" ;
	string k2 = "here" ;
	string k3 = "there" ;
//	int k = 1 ;
//	int k1 = 2 ;
//	int k2 = 3 ;
//	int k3 = 4 ;
//	double k = 1.01 ;
//	double k1 = 3.24 ;
//	double k2 = 1049 ;
//	double k3 = 2.345 ;
//	double k4 = 1.01 ;
	myUD.insert(k,10) ;
	myUD.insert(k1,20) ;
	myUD.insert(k2,30) ;
	myUD.insert(k3,40) ;
//	myUD.insert(k4,50) ;
	
	cout << myUD << endl ;
	myUD.delete_node(k1) ;
	cout << myUD << endl ;
	
	cout << "myUD type is: " << typeid(myUD).name() << endl ;
	}
	priority_queue<string> myq(5) ;
	cout << "myq: \n" << myq << endl ;
	myq.push_back("hello", 100) ;
	myq.push_back("hi",7) ;
	myq.push_back("bye",31) ;
	myq.push_back("ok", 1) ;
	myq.push_back("nice", 10) ;
	cout << "myq(1): " << myq.data(1) << endl ;
	cout << "myq: \n" << myq << endl ;
//	cout << myq.pop_front() << endl ;
//	cout << myq.pop_front() << endl ;
//	cout << myq.pop_front() << endl ;
//	cout << myq.pop_front() << endl ;
	cout << myq.pop_top_rank() << endl ;
	cout << "myq: \n" << myq << endl ;
}
