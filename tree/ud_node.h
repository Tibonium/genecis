/**
 *	@file ud_node.h
 */

#ifndef TREE_UD_NODE_H
#define TREE_UD_NODE_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std ;

template<class KEY_TYPE, class DATA_TYPE> class ud_node ;

template<class KEY_TYPE, class DATA_TYPE>
std::ostream& operator<< (std::ostream& os,
	const ud_node<KEY_TYPE, DATA_TYPE>& curr) ;

template<class KEY_TYPE, class DATA_TYPE> class ud_node {

	typedef ud_node self_type ;

	public:
		/**
		 * Main accessors
		 */
		ud_node<KEY_TYPE, DATA_TYPE>* parent ;
		ud_node<KEY_TYPE, DATA_TYPE>* child ;
		KEY_TYPE key ;
		DATA_TYPE data ;
		
		/**
		 * Constructor
		 */
		ud_node<KEY_TYPE, DATA_TYPE>(KEY_TYPE _key, DATA_TYPE _data) {
			parent = NULL ;
			child = NULL ;
			key = _key ;
			data = _data ;
		}
		
		inline ud_node<KEY_TYPE, DATA_TYPE>& operator=
			(ud_node<KEY_TYPE, DATA_TYPE>& rhs)
		{
			parent = rhs.parent ;
			child = rhs.child ;
			key = rhs.key ;
			data = rhs.data ;
			return *this ;
		}
		
		inline bool operator== (ud_node<KEY_TYPE, DATA_TYPE>& rhs) {
			if( key.compare(rhs.key) == 0 &&
				data == rhs.data ) {
				return true ;
			} else {
				return false ;
			}
		}
		
		/**
		 * Destructor
		 */
		~ud_node<KEY_TYPE, DATA_TYPE>() {
			if( parent != NULL ) {
				delete parent ;
			}
			if( child != NULL ) {
				delete child ;
			}
		}
		
		friend std::ostream& operator<< <> (std::ostream& os,
				const ud_node<KEY_TYPE, DATA_TYPE>& curr) ;

};

template<class KEY_TYPE, class DATA_TYPE>
std::ostream& operator<< (std::ostream& os,
		const ud_node<KEY_TYPE, DATA_TYPE>& curr)
{
	char buff[32] ;
	std::stringstream ss ;
	ss << curr.key ;
	string s = ss.str() ;
	char* _key = new char[sizeof(curr.key)/sizeof(KEY_TYPE)+1] ;
	memcpy(_key,s.c_str(),sizeof(curr.key)+sizeof(KEY_TYPE)) ;
	if( typeid(DATA_TYPE) == typeid(int) ) {
		sprintf(buff,"key:%8s  data:%8.0d", _key, (int)curr.data) ;
	} else {
		sprintf(buff,"key:%8s  data:%6.2f", _key, (double)curr.data) ;
	}
	os << buff ;
	return os ;
}

#endif
