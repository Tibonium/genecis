#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std ;

int main() {
	
	stringstream ss ;
	string s ;
	cout << "Enter a list of numbers: " ;
	getline( cin, s ) ;
	ss << s ;
	vector<int> nums ;
	char c[10] ;
	while( !ss.eof() ) {
		ss.getline(&c[0], 10, ' ') ;
		nums.push_back( atoi(c) ) ;
	}
	
	cout << "The sequence in reverse is: " ;
	for(vector<int>::reverse_iterator i=nums.rbegin(); i!=nums.rend(); ++i) {
		cout << (*i) << " " ;
	}
	cout << endl ;

}
