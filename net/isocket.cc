/**
 *	@file isocket.cc
 */
 
#include "isocket.h"
#include <cerrno>
#include <fcntl.h>
#include <iostream>

// Constructor
isocket::isocket() : _socket(-1) {
	std::memset( &_addr, 0, sizeof(_addr) ) ;
}

// Destructor
isocket::~isocket() {
	if( is_valid() ) {
		::close( _socket ) ;
	}
}

bool isocket::create() {
	_socket = socket( AF_INET, SOCK_STREAM, 0 ) ;
	if( !is_valid() ) {
		return false ;
	}
	int on = 1 ;
	if( setsockopt( _socket, SOL_SOCKET, SO_REUSEADDR,
		(const char*) &on, sizeof(on) ) == -1 )
	{
		return false ;
	}
	return true ;
}

bool isocket::bind( const int port ) {
	if( !is_valid() ) {
		return false ;
	}
	_addr.sin_family = AF_INET ;
	_addr.sin_addr.s_addr = INADDR_ANY ;
	_addr.sin_port = htons( port ) ;
	
	int bind_check = ::bind( _socket, (struct sockaddr*) &_addr,
		sizeof(_addr) ) ;
		
	if( bind_check == -1 ) {
		return false ;
	}
	return true ;
}
		
bool isocket::listen() const {
	if( !is_valid() ) {
		return false ;
	}
	int listen_check = ::listen( _socket, MAXHOOKS ) ;
	if( listen_check == -1 ) {
		return false ;
	}
	return true ;
}

bool isocket::accept( isocket& n_socket ) const {
	int addr_length = sizeof(_addr) ;
	n_socket._socket = ::accept( _socket, (sockaddr*) &_addr,
		(socklen_t*) &addr_length ) ;
		
	if( n_socket._socket <= 0 ) {
		return false ;
	} else {
		return true ;
	}
}

bool isocket::connect( const std::string host, const int port ) {
	if( !is_valid() ) return false ;
	
	_addr.sin_family = AF_INET ;
	_addr.sin_port = htons( port ) ;
	
	int status = inet_pton( AF_INET, host.c_str(), &_addr.sin_addr ) ;
	if( errno == EAFNOSUPPORT ) return false ;
	status = ::connect( _socket, (sockaddr*) &_addr, sizeof(_addr) ) ;
	if( status == 0 ) {
		return true ;
	} else {
		return false ;
	}
}

bool isocket::send( const std::string s ) const {
	int status = ::send( _socket, s.c_str(), s.size(), MSG_NOSIGNAL ) ;
	if( status == -1 ) {
		return false ;
	} else {
		return true ;
	}
}

int isocket::recv( std::string& s ) const {
	char buff [MAXBUFF+1] ;
	s = "" ;
	memset( buff, 0, MAXBUFF+1 ) ;
	int status = ::recv( _socket, buff, MAXBUFF, 0 ) ;
	if( status == -1 ) {
		std::cout << "isocket::recv: status(" << status
				  << ") errno == " << std::strerror(errno) << std::endl ;
		return 0 ;
	} else if( status == 0 ) {
		return 0 ;
	} else {
		s = buff ;
		return status ;
	}
}

void isocket::set_non_blocking( const bool b ) {
	int opts = fcntl( _socket, F_GETFL ) ;
	if( opts < 0 ) {
		return ;
	}
	if( b ) {
		opts = ( opts | O_NONBLOCK ) ;
	} else {
		opts = ( opts & ~O_NONBLOCK ) ;
	}
	fcntl( _socket, F_SETFL, opts ) ;
}
