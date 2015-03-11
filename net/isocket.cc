/**
 *	@file isocket.cc
 */
 
#include <genecis/net/isocket.h>

using namespace genecis::net ;

/**
 * Constructor
 */
isocket::isocket()
{	
	__socket = socket( AF_INET, SOCK_STREAM, 0 ) ;
	if( !is_valid() ) {
		std::cout << "isocket::isocket(): "
				  << std::strerror(errno) << std::endl ;
	}
}

// Destructor
isocket::~isocket()
{
	if( is_valid() ) {
		close( __socket ) ;
		std::cout << "socket closed" << std::endl ;
	}
}

// creates a new socket port
bool isocket::create()
{
	__socket = socket( AF_INET, SOCK_STREAM, 0 ) ;
	if( !is_valid() ) {
		std::cout << "isocket::create()::socket(): " << std::strerror(errno) << std::endl ;
		return false ;
	}
	// TIME_WAIT - arg
	int on = 1 ;
	if( setsockopt(__socket, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1 )
	{
		std::cout << "isocket::create()::setsockopt(): " << std::strerror(errno) << std::endl ;
	    return false ;
    }
	// successfully created the socket
	return true ;
}

// Bind the socket to a specific port
bool isocket::bind( const int port )
{
    if( !is_valid() )
        return false ;

	s_addr.sin_family = AF_INET ;
	s_addr.sin_addr.s_addr = INADDR_ANY ;
	s_addr.sin_port = htons( port ) ;
	
	int bind_check =
	    ::bind( __socket, (struct sockaddr*) &s_addr, sizeof(s_addr) ) ;
		
	// failed to bind the socket to the port
	if( bind_check == -1 ) {
		std::cout << "isocket::bind(): " << std::strerror(errno) << std::endl ;
		return false ;
	}
    // successfully bound the socket to the port
	return true ;
}

// listens for a socket to see if it is ready		
bool isocket::listen()
{
    if( !is_valid() )
        return false ;
        
	int state = ::listen( __socket, MAXHOOKS ) ;
	// socket is bad
	if( state == -1 )
	{
		std::cout << "isocket::listen(): " << std::strerror(errno) << std::endl ;
		return false ;
	}
	// socket is ready to be used
    return true ;
}

// accepts a new socket
bool isocket::accept( isocket& new_socket ) const
{
    int len = sizeof(s_addr) ;
	new_socket.__socket =
	    ::accept( __socket, (sockaddr*) &s_addr, (socklen_t*)&len ) ;
	
	// failed to accept the new socket
	if( new_socket.__socket <= 0 )
    {
		std::cout << "isocket::accept(): " << std::strerror(errno) << std::endl ;
	    return false ;
    }
	// accepted new socket
    return true ;
}

// connects the socket to a host/port
bool isocket::connect( const host_type host, const int port )
{
    if( !is_valid() )
        return false ;
    
	s_addr.sin_family = AF_INET ;
	s_addr.sin_port = htons( port ) ;
	int status = inet_pton( AF_INET, host.c_str(), &s_addr.sin_addr ) ;
	
	if( errno == EAFNOSUPPORT )
	{
	    std::cout << "isocket::connect()::inet_pton(): " << std::strerror(errno) << std::endl ;
	    return false ;
    }
	
	status = ::connect( __socket, (sockaddr*) &s_addr, sizeof(s_addr) ) ;
	// failed to connect to the port/host combination
	if( status < 0 )
    {
        std::cout << "isocket::connect(): " << std::strerror(errno) << std::endl ;
	    return false ;
    }
	// connected successfully to the host at the port
	return true ;
}

// send information across the socket
bool isocket::send( const data_type d )
{
    std::size_t size = d.size() ;
	int status = ::send( __socket, d.c_str(), size,  MSG_NOSIGNAL ) ;
	// failed to send data
	if( status == -1 )
	{
	    std::cout << "isocket::listen(): " << std::strerror(errno) << std::endl ;
	    return false ;
    }
	// sent data successfully
	return true ;
}

// receive information from the socket
int isocket::recv( data_type& d )
{
	buff_type data_buff[MAXBUFF+1] ;
	std::memset(data_buff, 0, MAXBUFF+1) ;
	d = "" ;
	int status = ::recv( __socket, data_buff, MAXBUFF, 0 ) ;
	// If no data arrives, the program will just wait here until some data arrives.
	if( status == -1 ) {
		std::cout << "isocket::recv( data_type& ) "
				  << std::strerror(errno) << std::endl ;
		return 0 ;
	} else if( status == 0 ) {
	    return 0 ;
	} else {
	    d = data_buff ;
	    return status ;
	}
}

// sets the socket to a non_blocking socket
void isocket::set_non_blocking( const bool b )
{
	int opts = fcntl( __socket, F_GETFL ) ;
	if( opts < 0 )
		return ;
	if( b )
		opts = ( opts | O_NONBLOCK ) ;
	else
		opts = ( opts & ~O_NONBLOCK ) ;
	
	fcntl( __socket, F_SETFL, opts ) ;
}

//void isocket::change_port( const int port ) {
//	__port = port ;	
//}
