#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
//#include <netcdfcpp.h>

using namespace std ;

int main() {

	int i = 0 ;
	stringstream ss ;
	
	while( i < 10 ) {
		ss.seekp(0) ;
//		sprintf(buff, "run%i.nc", i) ;
		ss << "run" << i << ".nc" ;
//		string s = ss.str() ;
		cout << (ss.str()).c_str() << endl ;
//		cout << "attempting to create netcdf file" << endl ;
//	    NcFile* _nc_file = new NcFile( s.c_str(), NcFile::Replace ) ;
//		delete _nc_file ;
		++i ;
	}
	
	string* a = new string[1] ;
	const string& s = "hi" ;
	a[0] = s ;
//	string s = a[0] ;
	cout << a[0] << endl ;

	return 0 ;
}
