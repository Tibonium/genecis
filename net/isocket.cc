/**
 *	@file isocket.cc
 */
 
#include "isocket.h"
#include <cerrno>
#include <fcntl.h>
#include <iostream>
#include <cstdio>
#include <sstream>

// Constructor
isocket::isocket( const std::string& host, const int port ) :
	_host_name(host), _port(port)
{
	memset( &host_info, 0, sizeof(host_info) ) ;
	host_info.ai_family = AF_UNSPEC ;
	host_info.ai_socktype = SOCK_STREAM ;

	std::stringstream ss ;
	ss << port ;
	std::string p = ss.str() ;
	_socket = getaddrinfo( host.c_str(), p.c_str(),
			&host_info, &host_info_list ) ;

	create() ;
}

isocket::isocket() {
//	memset( &host_info, 0, sizeof(host_info) ) ;
//	host_info.ai_family = AF_UNSPEC ;
//	host_info.ai_socktype = SOCK_STREAM ;
	
	_socketfd = socket( AF_INET, SOCK_STREAM, 0 ) ;
	if( _socketfd == -1 ) {
		std::cout << "isocket::isocket() "
				  << std::strerror(errno) << std::endl ;
		std::exit(_socketfd) ;
	}
}

// Destructor
isocket::~isocket() {
	if( _socket != -1 ) {
		close( _socket ) ;
		std::cout << "socket closed" << std::endl ;
	}
}

void isocket::create() {
	_socketfd = socket( host_info_list->ai_family, host_info_list->ai_socktype,
		host_info_list->ai_protocol ) ;
	if( _socketfd == -1 ) {
		std::cout << "isocket::create() "
				  << std::strerror(errno) << std::endl ;
		std::exit(_socketfd) ;
	}
}

void isocket::hook() {
	s_addr.sin_family = AF_INET ;
	s_addr.sin_addr.s_addr = INADDR_ANY ;
	s_addr.sin_port = htons( _port ) ;
	
	int bind_check = bind( _socketfd, (struct sockaddr*) &s_addr,
		sizeof(s_addr) ) ;
		
	if( bind_check == -1 ) {
		std::cout << "isocket::hook() "
				  << std::strerror(errno) << std::endl ;
		std::exit(bind_check) ;
	}
}
		
void isocket::ready() {
	int state = listen( _socketfd, MAXHOOKS ) ;
	if( state == -1 ) {
		std::cout << "isocket::ready() "
				  << std::strerror(errno) << std::endl ;
		std::exit(_socketfd) ;
	}
}

void isocket::take( isocket& n_socket ) const {
	int len = sizeof(s_addr) ;
	n_socket._socketfd = accept( _socketfd, (sockaddr*) &s_addr,
		(socklen_t*) &len ) ;
		
	if( n_socket._socketfd <= 0 ) {
		std::cout << "isocket::take() "
				  << std::strerror(errno) << std::endl ;
		std::exit(_socketfd) ;
	}
}

void isocket::call() {
	_socket = connect( _socketfd, host_info_list->ai_addr, 
		host_info_list->ai_addrlen ) ;
	if( _socket == -1 ) {
		std::cout << "isocket::call() "
				  << std::strerror(errno) << std::endl ;
		std::exit(_socket) ;
	}
}

void isocket::chat( const std::string s ) {
	int len = s.size() ;
	bytes_sent = send( _socketfd, s.c_str(), len, 0) ;
	if( bytes_sent == -1 ) {
		std::cout << "isocket::chat( const std::string ) "
				  << std::strerror(errno) << std::endl ;
		std::exit(bytes_sent) ;
	}
}

void isocket::read( std::string& s ) {
	char data_buff[MAXBUFF+1] ;
	bytes_recv = recv( _socketfd, data_buff, MAXBUFF, 0 ) ;
	// If no data arrives, the program will just wait here until some data arrives.
//	if ( bytes_recv == 0 ) std::cout << "host shut down." << std::endl ;
	if ( bytes_recv == -1 ) {
		std::cout << "isocket::read( std::string& ) "
				  << std::strerror(errno) << std::endl ;
		std::exit(bytes_recv) ;
	}
	s = data_buff ;
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

//void isocket::change_port( const int port ) {
//	_port = port ;	
//}
