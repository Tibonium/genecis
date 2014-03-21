/**
 *	@file genecis_server.cc
 */

#include "genecis_server.h"

const std::string host = "localhost" ;

genecis_server::genecis_server( const int port ) :
		isocket( host, port )
{
//	std::stringstream ss ;
//	ss << port ;
//	std::string s = ss.str() ;
//	std::string host = "localhost" ;
//	
	hook() ;
	ready() ;
}

genecis_server::~genecis_server() {} ;

const genecis_server& genecis_server::operator<< (
	const std::string& s ) 
{
	chat( s ) ;
	return *this ;
}

const genecis_server& genecis_server::operator>> (
	std::string& s )
{
	read( s ) ;
	return *this ;
}

void genecis_server::accept ( genecis_server& sock ) {
	take( sock ) ;
}
