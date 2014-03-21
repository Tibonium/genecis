#include <iostream>
#include <sstream>
#include "net/genecis_server.h"

using namespace std ;

int main() {
	
	cout << "server running..." << endl ;
	
//	try{
		int port = 45000 ;
		int rec = 1 ;
		genecis_server server( port ) ;
		
		while( true ) {
			cout << "waiting for response from client..." << endl ;
			genecis_server new_sock ;
			server.accept( new_sock ) ;
//			try{
				while( true ) {
					cout << "Client intialized..." << endl ;
					stringstream ss ;
					string data ;
					new_sock >> data ;
					ss << "This is request #" << rec ;
					data = ss.str() ;
//					data = "Yep, got the request." ;
					new_sock << data ;
					++rec ;
					ss.seekp(0) ;
				}
//			} catch (int) {}
		}
//	} catch (int) {}
	
	cout << "server shutdown" << endl ;
}
