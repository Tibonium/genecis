#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std ;

int main() {

	int N = 32 ;
	char buff[N] ;
	string salt = "%E7x" ;
	string s ;
	cout << "Enter a key to be hashed: " ;
	cin >> s ;
	
	for(std::string::iterator it=s.begin(); it != s.end(); ++it) {
		if( it == s.begin() ) {
			sprintf(buff, "%c%s", *it, salt.c_str()) ;
		} else {
			sprintf(buff + strlen(buff), "%c%s", *it, salt.c_str()) ;
		}
	}
	cout << "Salt is: " << salt << endl ;
	cout << "Hashed key is: " << buff << endl ;
	
	int hash_value = 0 ;
	for(int i=0; i<N; ++i) {
		char x = buff[i] ;
		hash_value += int(x) ;
	}
	
	cout << "hash_value is: " << hash_value << endl ;
	cout << "mod 1000: " << hash_value % 1000 << endl ;

}
