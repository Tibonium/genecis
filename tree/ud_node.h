/**
 *	@file ud_node.h
 */

#ifndef TREE_UD_NODE_H
#define TREE_UD_NODE_H

#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std ;

template<class _T> class ud_node ;

template<class _T>
std::ostream& operator<< (std::ostream& os, const ud_node<_T>& curr) ;

template<class _T> class ud_node {

	public:
		/**
		 * Main accessors
		 */
		ud_node<_T>* parent ;
		ud_node<_T>* child ;
		string key ;
		_T data ;
		
		/**
		 * Constructor
		 */
		ud_node<_T>(string _key, _T _data) {
			parent = NULL ;
			child = NULL ;
			key = _key ;
			data = _data ;
		}
		
		inline ud_node<_T>& operator= (ud_node<_T>& rhs) {
			parent = rhs.parent ;
			child = rhs.child ;
			key = rhs.key ;
			data = rhs.data ;
			return *this ;
		}
		
		inline bool operator== (ud_node<_T>& rhs) {
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
		~ud_node<_T>() {
			if( parent != NULL ) {
				delete parent ;
			}
			if( child != NULL ) {
				delete child ;
			}
		}
		
		friend std::ostream& operator<< <> (std::ostream& os, const ud_node<_T>& curr) ;

};

template<class _T>
std::ostream& operator<< (std::ostream& os, const ud_node<_T>& curr) {
	char buff[32] ;
	char* _key = new char[(curr.key).size()+1] ;
	memcpy(_key,(curr.key).c_str(),(curr.key).size()) ;
	if( typeid(_T) == typeid(int) ) {
		sprintf(buff,"key:%8s  data:%8.0d", _key, (int)curr.data) ;
	} else {
		sprintf(buff,"key:%8s  data:%6.2f", _key, (double)curr.data) ;
	}
	os << buff ;
	return os ;
}

#endif
