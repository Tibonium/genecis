/**
 *	@file isocket.h
 */
 
#ifndef NET_ISOCKET_H
#define NET_ISOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200 ;
const int MAXHOOKS = 5 ;
const int MAXBUFF = 500 ;

class isocket {

	public:
		
//		bool bind( const int ) ;
//				
		void listen() const ;
//		
//		bool accept( isocket& ) const ;
		
		void call() ;
		
		void chat( const std::string ) ;
		
		void read( std::string& ) ;
		
		void set_non_blocking( const bool ) ;
		
//		bool is_valid() const { return _socket != -1 ; }

		// Constructor
		isocket( const std::string&, const std::string& ) ;
		
		// Destructor
		virtual ~isocket() ;
		
	private:
	
		struct addrinfo host_info ;
		struct addrinfo* host_info_list ;
		struct sockaddr_in sin ;
		int status ;
		int socketfd ;
		ssize_t bytes_sent ;
		ssize_t bytes_recv ;

		void create() ;

};

#endif
