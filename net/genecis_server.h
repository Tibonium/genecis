/**
 *	@file genecis_server.h
 */

#ifndef GENECIS_NET_GENECIS_SERVER_H
#define GENECIS_NET_GENECIS_SERVER_H

#include "isocket.h"

namespace genecis {
namespace net {

class genecis_server : public isocket {

	public:
		
		// Constructor
		genecis_server( const int ) ;
		
		genecis_server() {} ;
		
		// Destructor
		virtual ~genecis_server() ;
		
		const genecis_server& operator<< ( const std::string& ) ;
		
		const genecis_server& operator>> ( std::string& ) ;
		
		void accept( genecis_server& ) ;

};

}	// end of namespace net
}	// end of namespace genecis

#endif
