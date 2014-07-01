#include <iostream>
#include <sstream>
#include "../net/genecis_server.h"

using namespace std ;
using namespace genecis::net ;

int main() {
	
	cout << "server running..." << endl ;
	
//	try{
		int port = 45000 ;
//		int rec = 1 ;
		genecis_server server( port ) ;
		
		while( true ) {
			cout << "waiting for response from client..." << endl ;
			genecis_server _sock1 ;
			server.accept( _sock1 ) ;
//			genecis_server _sock2 ;
//			server.accept( _sock2 ) ;
//			try{
				while( true ) {
//					cout << "Client intialized..." << endl ;
					stringstream ss ;
					string data ;
					_sock1 >> data ;
//					ss << "This is request #" << rec ;
//					cout << data << endl ;
					if( strcmp(data.c_str(),"break") == 0 ) break ;
					cout << "client: " << data << endl ;
					cout << "msg: " ;
					string reply ;
					getline(cin, reply) ;
					data = reply ;
//					data = "Yep, got the request." ;
					_sock1 << data ;
//					++rec ;
//					ss.seekp(0) ;
				}
			break ;
		}
//	} catch (int) {}
	
	cout << "server shutdown" << endl ;
}
