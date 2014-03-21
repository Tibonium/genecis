#include <iostream>
#include "net/genecis_server.h"

using namespace std ;

int main() {
	
	cout << "server running..." << endl ;
	
//	try{
		int port = 45000 ;
		genecis_server server( port ) ;
		
		while( true ) {
			genecis_server new_sock ;
			server.accept( new_sock ) ;
//			try{
				while( true ) {
					string data ;
					new_sock >> data ;
					data = "How are you doing today?" ;
					new_sock << data ;
				}
//			} catch (int) {}
		}
//	} catch (int) {}
	
	cout << "server shutdown" << endl ;
}
