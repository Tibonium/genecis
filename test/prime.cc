#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std ;

int main() {

	const char* filename = "prime_list.txt" ;
	ifstream file( filename ) ;
	if( !file ) {
		cout << "Generating prime database...." << endl ;
		ofstream fi( filename ) ;
		unsigned long t = 235687 ;
		vector<unsigned long> temp_list ;
		temp_list.push_back(2) ;
		temp_list.push_back(3) ;
		temp_list.push_back(5) ;
		temp_list.push_back(7) ;
		temp_list.push_back(11) ;
		temp_list.push_back(13) ;
		temp_list.push_back(17) ;
		temp_list.push_back(19) ;
		temp_list.push_back(23) ;
		temp_list.push_back(29) ;
		temp_list.push_back(31) ;
		temp_list.push_back(37) ;
		temp_list.push_back(41) ;
		temp_list.push_back(43) ;
		temp_list.push_back(47) ;
		temp_list.push_back(53) ;
		temp_list.push_back(59) ;
		for(unsigned long i=60; i<t; ++i) {
			bool bprime = true ;
			for(vector<unsigned long>::iterator it=temp_list.begin();
					it!=temp_list.end(); ++it) {
				if( i % (*it) == 0 ) {
					bprime = false ;
					break ;
				}
			}
			if( bprime ) temp_list.push_back(i) ;
		}
		for(vector<unsigned long>::iterator it=temp_list.begin();
				it!=temp_list.end(); ++it) {
			fi << (*it) << endl ;
		}
		fi.close() ;
	}
	
	unsigned long p ;
	cout << "Enter an integer: " ;
	cin >> p ;
	cout << "The number " << p ;
	ifstream fi( filename ) ;
	string line ;
	bool bprime = true ;
	while( !fi.eof() ) {
		getline(fi, line) ;
		unsigned long n = atoi(line.c_str()) ;
		if( p == n ) break ;
		if( p % n == 0 ) {
			cout << " is not prime." << endl ;
			cout << p << " is divisible by " << n << endl ;
			bprime = false ;
			break ;
		}
	}
	if( bprime ) cout << " is prime." << endl ;
}
