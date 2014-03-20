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
	
		bool create() ;
		
		bool bind( const int ) ;
				
		bool listen() const ;
		
		bool accept( isocket& ) const ;
		
		bool connect( const std::string , const int ) ;
		
		bool send( const std::string ) const ;
		
		int recv( std::string& ) const ;
		
		void set_non_blocking( const bool ) ; 
		
		bool is_valid() const { return _socket != -1 ; }

		// Constructor
		isocket() ;
		
		// Destructor
		virtual ~isocket() ;
		
	private:
	
		int _socket ;
		sockaddr_in _addr ;

};

#endif
