#include <iostream>
#include <sstream>
#include <genecis/net/genecis_server.h>

using namespace std ;
using namespace genecis::net ;

int main() {
	
	cout << "server running..." << endl ;
	
	int port = 45000 ;
	genecis_server host( port ) ;
    string data ;
    data.clear() ;
	while( true ) {
		cout << "waiting for client connection..." << endl ;
		genecis_server sock1 ;
		host.accept( sock1 ) ;
		while( strcmp(data.c_str(),"ready") != 0 )
		{
		    sock1 >> data ;
		    usleep(1000) ;
	    }
        cout << "client connected" << endl ;
        data.clear() ;
        while( true ) {
	        sock1 >> data ;
			if( strcmp(data.c_str(),"break") == 0 ) break ;
			cout << "client: " << data << endl ;
			cout << "msg: " ;
			string reply ;
			getline(cin, reply) ;
			data = reply ;
			sock1 << data ;
			if( strcmp(data.c_str(),"break") == 0 ) break ;
            data.clear() ;
		}
		break ;
	}
	
	cout << "server shutdown" << endl ;
}
