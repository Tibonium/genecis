#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "../math/set.h"
#include "../math/matrix.h"

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

	set<int> myset(&nums) ;
	cout << "The first element of my set is: " << myset[0] << endl ;
	matrix<int> m1(2,2) ;
	matrix<int> m2(2,2) ;
	for(int i=0 ; i<2; ++i) {
		for(int j=0; j<2; ++j) {
			m1(i,j) = i*2 + j + 1 ;
			m2(i,j) = i*2 + j + 2 ;
		}
	}
	matrix<int> m[2] ;
	m[0] = m1 ;
	m[1] = m2 ;
	cout << "m[0]: " << m[0] << endl ;
	set< matrix<int> > matset(m) ;
	matrix<int> m3 = matset[0] ;
	cout << "First element of set matset: " << matset[0] << endl ;
	cout << "m3 now: " << m3 << endl ;

}
