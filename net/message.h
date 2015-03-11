/**
 * @file message.h
 */
#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace genecis {
namespace net {

class message {

    public:
    
        typedef std::size_t     size_type ;
        typedef char            value_type ;
        typedef value_type*     value_ptr ;
        typedef const value_type* const_value_ptr ;
    
        // Length of the header
        enum { header_size = 4 } ;
        // maximum number of characters in the message
        enum { max_size = 512 } ;
        
        // Empty constructor
        message() : _size(0) {}
        
        /**
         * Pointer to the start of data
         */
        const_value_ptr data() const {
            return _data ;
        }
        
        value_ptr data() {
            return _data ;
        }
        
        /**
         * Size of _data
         */
        size_type size() {
            return header_size + _size ;
        }
        
        /**
         * Returns the start of the message
         */
        const_value_ptr body() const {
            return _data + header_size ;
        }
        
        value_ptr body() {
            return _data + header_size ;
        }

        /**
         * Returns the size of the message
         */        
        size_type body_size() {
            return _size ;
        }

        /**
         * Sets the current size of the message
         */
        void body_size( size_type size ) {
            _size = size ;
            if( size > max_size )
                size = max_size ;
        }
        
        /**
         * Interprets the header
         */
        bool decode_header() {
            using namespace std ;
            value_type header[header_size+1] = "" ;
            strncat(header, _data, header_size) ;
            _size = atoi(header) ;
            if( _size > max_size ) {
                _size = 0 ;
                return false ;
            }
            return true ;
        }
        
        /**
         * Codes the header used to interpret the message
         */
        void encode_header() {
            using namespace std ;
            value_type header[header_size+1] = "" ;
            sprintf(header, "%4d", static_cast<int>(_size)) ;
            memcpy(_data, header, header_size) ;
        }
    
    private:
    
        value_type _data[header_size + max_size] ;
        size_type _size ;

};

}   // end of namespace net
}   // end of namespace genecis
