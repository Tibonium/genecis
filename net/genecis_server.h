/**
 *	@file genecis_server.h
 */
#pragma once

#include <genecis/net/isocket.h>

namespace genecis {
namespace net {

class genecis_server : private isocket {

	public:
	
	    typedef genecis_server       self_type ;
	    typedef std::string          host_type ;
	    typedef isocket::data_type   data_type ;
	
		// Host server Constructor
		genecis_server( int port ) ;
		
		// Client server Constructor
		genecis_server( host_type host, int port ) ;
	
	    // Empty constructor
		genecis_server() {} ;
	
		// Destructor
		virtual ~genecis_server() ;
	
	    // reads data
		const self_type& operator<< ( const data_type& ) ;
	
	    // writes data
		const self_type& operator>> ( data_type& ) ;
	
	    // accepts a new socket
		void accept( self_type& ) ;

};

}	// end of namespace net
}	// end of namespace genecis
