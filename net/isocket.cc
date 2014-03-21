/**
 *	@file isocket.cc
 */
 
#include "isocket.h"
#include <cerrno>
#include <fcntl.h>
#include <iostream>

// Constructor
isocket::isocket( const std::string& host, const std::string& port ) {
	memset( &host_info, 0, sizeof(host_info) ) ;
	host_info.ai_family = AF_UNSPEC ;
	host_info.ai_socktype = SOCK_STREAM ;

	status = getaddrinfo(host.c_str(), port.c_str(),
			&host_info, &host_info_list ) ;

	create() ;
}

// Destructor
isocket::~isocket() {
	if( socketfd != -1 ) {
		close( status ) ;
		std::cout << "socket closed" << std::endl ;
	}
}

void isocket::create() {
	socketfd = socket( host_info_list->ai_family, host_info_list->ai_socktype,
		host_info_list->ai_protocol ) ;
	if( socketfd == -1 ) {
		std::cout << "Socket creation error." << std::endl ;
	}
}

//bool isocket::bind( const int port ) {
//	if( !is_valid() ) {
//		return false ;
//	}
//	_addr.sin_family = AF_INET ;
//	_addr.sin_addr.s_addr = INADDR_ANY ;
//	_addr.sin_port = htons( port ) ;
//	
//	int bind_check = ::bind( _socket, (struct sockaddr*) &_addr,
//		sizeof(_addr) ) ;
//		
//	if( bind_check == -1 ) {
//		return false ;
//	}
//	return true ;
//}
//		
//bool isocket::listen() const {
//	if( !is_valid() ) {
//		return false ;
//	}
//	int listen_check = ::listen( _socket, MAXHOOKS ) ;
//	if( listen_check == -1 ) {
//		return false ;
//	}
//	return true ;
//}

//bool isocket::accept( isocket& n_socket ) const {
//	int addr_length = sizeof(_addr) ;
//	n_socket._socket = ::accept( _socket, (sockaddr*) &_addr,
//		(socklen_t*) &addr_length ) ;
//		
//	if( n_socket._socket <= 0 ) {
//		return false ;
//	} else {
//		return true ;
//	}
//}

void isocket::call() {
	status = connect( socketfd, host_info_list->ai_addr, 
		host_info_list->ai_addrlen ) ;
	if( status == -1 ) {
		std::cout << "Connection error" << std::endl ;
	}
}

void isocket::chat( const std::string s ) {
	int len ;
	len = s.size() ;
	bytes_sent = send( socketfd, s.c_str(), len, 0) ;
}

void isocket::read( std::string& s ) {
	char incoming_data_buffer[MAXBUFF+1] ;
	bytes_recv = recv( socketfd, incoming_data_buffer, MAXBUFF, 0 ) ;
	// If no data arrives, the program will just wait here until some data arrives.
	if ( bytes_recv == 0 ) std::cout << "host shut down." << std::endl ;
	if ( bytes_recv == -1 ) std::cout << "recieve error!" << std::endl ;
	s = incoming_data_buffer ;
}

void isocket::set_non_blocking( const bool b ) {
	int opts = fcntl( status, F_GETFL ) ;
	if( opts < 0 ) {
		return ;
	}
	if( b ) {
		opts = ( opts | O_NONBLOCK ) ;
	} else {
		opts = ( opts & ~O_NONBLOCK ) ;
	}
	fcntl( status, F_SETFL, opts ) ;
}
