/**
 *	@file isocket.h
 */
 
#ifndef GENECIS_NET_ISOCKET_H
#define GENECIS_NET_ISOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200 ;
const int MAXHOOKS = 5 ;
const int MAXBUFF = 500 ;

class isocket {

	public:
		
		void hook() ;
				
		void ready() ;
		
		void take( isocket& ) const ;
		
		void call() ;
		
		void chat( const std::string ) ;
		
		void read( std::string& ) ;
		
		void set_non_blocking( const bool ) ;
		
//		void change_port( const int ) ;

		// Constructor
		isocket( const std::string&, const int ) ;
		
		isocket() ;
		
		// Destructor
		virtual ~isocket() ;
		
	private:
	
		struct addrinfo host_info ;
		struct addrinfo* host_info_list ;
		struct sockaddr_in s_addr ;
		int _socket ;
		int _socketfd ;
		ssize_t bytes_sent ;
		ssize_t bytes_recv ;
		
		std::string _host_name ;
		int _port ;

		void create() ;

};

#endif
