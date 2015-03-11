/**
 *	@file isocket.h
 */
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <genecis/net/message.h>

const int MAXHOSTNAME = 200 ;
const int MAXHOOKS = 5 ;
const int MAXBUFF = 500 ;

namespace genecis {
namespace net {

class isocket {

	public:

        typedef isocket         self_type ;
        typedef std::string     data_type ;
        typedef std::string     host_type ;
        typedef char            buff_type ;

        // Default constructor		
		isocket() ;
	
		// Destructor
		virtual ~isocket() ;
		
        // creates a new socket
		bool create() ;

		// binds a socket to a port
		bool bind( const int port ) ;
		
		// listens for a ready socket
		bool listen() ;
	
	    // accepts a new socket
		bool accept( self_type& ) const ;
		
		// connection call
		bool connect( const host_type host, const int port ) ;
	    
	    // Data transfer function
		bool send( const data_type ) ;
	
	    // Data receive function
		int recv( data_type& ) ;
	
	    // Unknown
		void set_non_blocking( const bool ) ;
	
	    // socket open check
	    bool is_valid() const {
	        return __socket != -1 ;
	    }
	    
//		void change_port( const int ) ;
	
	private:

		struct addrinfo host_info ;
		struct addrinfo* host_info_list ;
		struct sockaddr_in s_addr ;
		int __socket ;
		int __socketfd ;
		ssize_t bytes_sent ;
		ssize_t bytes_recv ;
	
		std::string __host_name ;
		int __port ;

};

}	// end of namespace net
}	// end of namespace genecis
