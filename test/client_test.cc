#include <iostream>
#include <sstream>
#include <genecis/net/genecis_server.h>

using namespace std ;
using namespace genecis::net ;

int main() {

	string host = "localhost" ;
	int port = 45000 ;
	cout << "Creating client server..." << endl ;
	genecis_server client( host, port ) ;
	cout << "Connecting..." << endl ;
	client << "ready" ;
	while( true ) {
		cout << "msg: " ;
		string msg ;
		getline(cin, msg) ;
		client << msg ;
		if( strcmp(msg.c_str(),"break") == 0 ) break ;
		string s ;
		client >> s ;
		if( strcmp(s.c_str(),"break") == 0 ) break ;
		cout << "server: " << s.c_str() << endl ;
	}

}
