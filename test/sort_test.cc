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
	int N = 0 ;
	while( !ss.eof() ) {
		ss.getline(&c[0], 10, ' ') ;
		nums.push_back( atoi(c) ) ;
		++N ;
	}
	
	cout << "The sequence in reverse is: " ;
	for(vector<int>::reverse_iterator i=nums.rbegin(); i!=nums.rend(); ++i) {
		cout << (*i) << " " ;
	}
	cout << endl ;

	set< vector<int> > myset(&nums, nums.size()) ;
	cout << "The first element of my set is: " << (myset[0])[0] << endl ;
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
	set< matrix<int> > matset(m, 2) ;
	matrix<int>* m3 = matset[0]*matset[1] ;
	cout << "First element of set matset: " << matset[0] << endl ;
	cout << "m3 now: " << (*m3) << endl ;

	int s1[] = {1, 3, 5, 6, 8} ;
	int s2[] = {2, 3, 4, 7, 9} ;
	set<int> set1(s1, 5) ;
	set<int> set2(s2, 5) ;
	set<int> set3 = set1.unite(set2) ;
	cout << "set1 union set2: " ;
	for(unsigned i=0; i<set3.size(); ++i) {
		cout << set3[i] << " " ;
	}
	cout << endl ;

	set<int> set4 = set1.intersect(set2) ;
	cout << "set1 intersect set2: " ;
	for(unsigned i=0; i<set4.size(); ++i) {
		cout << set4[i] << " " ;
	}
	cout << endl ;
	
	set<int> set5 = set1 - set2 ;
	cout << "set1 - set2: " ;
	for(unsigned i=0; i<set5.size(); ++i) {
		cout << set5[i] << " " ;
	}
	cout << endl ;

}
