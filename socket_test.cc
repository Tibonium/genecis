#include <iostream>
#include <sstream>
#include "net/isocket.h"

using namespace std ;

int main() {

	string host = "localhost" ;
	int port = 45000 ;
	cout << "Creating socket..." << endl ;
	isocket mysock( host, port ) ;
	cout << "Connecting..." << endl ;
	mysock.call() ;
//	mysock.listen() ;
	while( true ) {
		cout << "msg: " ;
		string msg ;
		getline(cin, msg) ;
		mysock.chat(msg) ;
		if( strcmp(msg.c_str(),"break") == 0 ) break ;
//		cout << "Waiting for reply..."  << endl;
		string s ;
		mysock.read(s) ;
		cout << "server: " << s.c_str() << endl ;
	}

//	int status ;
//	struct addrinfo host_info ;
//	struct addrinfo* host_info_list ;
//	
//	memset( &host_info, 0, sizeof(host_info) ) ;
//	host_info.ai_family = AF_UNSPEC ;
//	host_info.ai_socktype = SOCK_STREAM ;
//	
//	status = getaddrinfo("na.leagueoflegends.com","80", &host_info, &host_info_list ) ;
//	
//	if( status != 0 ) cout << "getaddrinfo error" << gai_strerror(status) << endl ;

//	cout << "Creating socket..." << endl ;
//	int socketfd = socket( host_info_list->ai_family, host_info_list->ai_socktype,
//		host_info_list->ai_protocol ) ;
//	if( socketfd == -1 ) cout << "socket error" << endl ;
//	
//	cout << "Connecting..." << endl ;
//	status = connect( socketfd, host_info_list->ai_addr, 
//		host_info_list->ai_addrlen ) ;
//	if( status == -1 ) cout << "Connection error" << endl ;

//	cout << "Sending message..."  << endl;
//	stringstream ss ;
//	ss << "GET / HTTP/1.1\nhost: www.google.com\n\n" ;
//	string msg = "GET / HTTP/1.1\nhost: na.leagueoflegends.com\n\n" ;
//	int len ;
//	ssize_t bytes_sent ;
//	len = msg.size() ;
//	bytes_sent = send( socketfd, msg.c_str(), len, 0) ;
//	cout << "bytes_sent: " << bytes_sent << endl ;
//	
//	cout << "Waiting to recieve data..."  << endl;
//	ssize_t bytes_recieved ;
//	char incoming_data_buffer[1000] ;
//	bytes_recieved = recv( socketfd, incoming_data_buffer, 1000, 0 ) ;
//	// If no data arrives, the program will just wait here until some data arrives.
//	if ( bytes_recieved == 0 ) cout << "host shut down." << endl ;
//	if ( bytes_recieved == -1 ) cout << "recieve error!" << endl ;
//	cout << bytes_recieved << " bytes recieved :" << endl ;
//	cout << incoming_data_buffer << endl;

//	isocket mysock ;
//	mysock.create() ;
//	mysock.bind( 7 ) ;
//	mysock.listen() ;
////	mysock.accept(mysock) ;
//	mysock.connect( "localhost", 7 ) ;
//	string s ;
//	mysock.recv( s ) ;
//	cout << "ran test, s: " << s << endl ;

	return 0 ;

}
