/**
 *	@file genecis_server.cc
 */

#include <genecis/net/genecis_server.h>

using namespace genecis::net ;

// Constructor
genecis_server::genecis_server( int port )
{
    if( !isocket::create() )
    {
        throw std::invalid_argument("Failed to create a server socket.") ;
    }

    if( !isocket::bind( port ) )
    {
        throw std::invalid_argument("Failed to bind port for server socket.") ;
    }
    
    if( !isocket::listen() )
    {
        throw std::invalid_argument("Unable to listen to the server socket.") ;
    }
}

// Constructor
genecis_server::genecis_server( host_type host, int port )
{
    if( !isocket::create() )
    {
        throw std::invalid_argument("Failed to create a client socket.") ;
    }

    if( !isocket::connect( host, port ) )
    {
        throw std::invalid_argument("Failed to connect to server.") ;
    }
}

// Destructor
genecis_server::~genecis_server()
{

}

// sends data to a socket
const genecis_server&
genecis_server::operator<<( const data_type& d ) 
{
	if( !isocket::send(d) )
	{
        throw std::invalid_argument("Failed in operator<<.") ;
	}
	return *this ;
}

// receives data from a socket
const genecis_server&
genecis_server::operator>>( data_type& d )
{
	if( isocket::recv(d) < 0 )
	{
        throw std::invalid_argument("Failed in operator>>.") ;
	}
	return *this ;
}

// connects a socket
void genecis_server::accept( genecis_server& sock )
{
    if( !isocket::accept(sock) )
    {
        throw std::invalid_argument("Failed to accept the socket.") ;
    }
}
