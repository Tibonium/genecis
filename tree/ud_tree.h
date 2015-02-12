/**
 *	@file ud_tree.h
 */

#pragma once

#include <typeinfo>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std ;
	
namespace genecis {
namespace tree {

    /** ===== binary-bidirectional node class ===== **/
	template<class K, class D> class ud_node ;

	template<class K, class D>
	std::ostream& operator<< (std::ostream& os, const ud_node<K,D>& curr) ;

	template<class K, class D>
	class ud_node {

		public:
		
		    typedef K                                  key_type ;
		    typedef D                                  data_type ;
		    typedef ud_node<key_type,data_type>        self_type ;
		    typedef self_type                          node_type ;
		    typedef node_type*                         node_ptr ;
		    
			/**
			 * Main accessors
			 */
			node_ptr _parent ;
			node_ptr _child ;
			key_type _key ;
			data_type _data ;
		
			/**
			 * Constructor
			 */
			ud_node(key_type key, data_type data) {
				_parent = NULL ;
				_child = NULL ;
				_key = key ;
				_data = data ;
			}
		
		    /**
		     * Copy operator
		     */
			node_ptr operator= ( node_type& rhs ) {
				_parent = rhs._parent ;
				_child = rhs._child ;
				_key = rhs._key ;
				_data = rhs._data ;
				return this ;
			}
		
		    /**
		     * Comparison operator
		     */
			bool operator== ( node_type& rhs ) {
				if( _key.compare(rhs._key) == 0 &&
					_data == rhs._data ) {
					return true ;
				} else {
					return false ;
				}
			}
		
			friend std::ostream& operator<< <> (std::ostream& os, const self_type& curr) ;
	};

    /**
     * standard output operator overload for ud_nodes
     */
	template<class K, class D>
	std::ostream& operator<< (std::ostream& os, const ud_node<K,D>& curr)
	{
		char buff[32] ;
		std::stringstream ss ;
		ss << curr._key ;
		string s = ss.str() ;
		char* key = new char[s.size()+1] ;
		memcpy( key, s.c_str(), s.size() ) ;
		if( typeid(D) == typeid(int) ) {
			sprintf(buff,"key:%8s  data:%8.0d", key, (int)curr._data) ;
		} else {
			sprintf(buff,"key:%8s  data:%6.2f", key, (double)curr._data) ;
		}
		os << buff ;
		delete[] key ;
		return os ;
	}
	
    /** ===== binary-bidirectional tree class ===== **/
	template<class K, class D> class ud_tree ;

	template<class K, class D>
	std::ostream& operator<< (std::ostream& os, const ud_tree<K,D>& tree) ;

	template<class K, class D>
	class ud_tree {

		public:

            typedef K                               key_type ;
            typedef D                               data_type ;
            typedef std::size_t                     size_type ;
            typedef ud_tree<key_type,data_type>     self_type ;
            typedef ud_node<key_type,data_type>     node_type ;
            typedef typename node_type::node_ptr    node_ptr ;
            
			/**
			 *  Constructor
			 */
			ud_tree() {
				_first = NULL ;
				_last = NULL ;
				_count = 0 ;
			}
		
			/**
			 *  Destructor
			 */
			virtual ~ud_tree() {
				destroy_tree( _first ) ;
			}
			
			/**
			 * Insert a new node within the tree. If the first is empty
			 * then set first and last to the new node. Otherwise we
			 * perform a redundency check to make sure the key doesn't
			 * already exist in our tree. If the key is unique, then we
			 * put the new node at the end of the tree.
			 */
			 void insert( const key_type& key, const data_type& data ) {
			 	node_ptr temp = new node_type( key, data ) ;
			 	if( _first == NULL ) {
			 		_first = temp ;
			 		_last = temp ;
				 	++_count ;
			 	} else {
			 		if( !search( _first, key ) ) {
					 	node_ptr old_last = _last ;
					 	old_last->_child = temp ;
					 	temp->_parent = old_last ;
					 	_last = temp ;
		 			 	++_count ;
				 	}
			 	}
			 }

             /**
              * Deletes a node from the binary tree
              */
			 void delete_node( const key_type& key ) {
			 	node_ptr temp = find_node( _first, key ) ;
			 	if( temp == _first ) {
			 		temp->_child->_parent = NULL ;
			 		_first = temp->_child ;
			 	} else if( temp == _last ) {
			 		_last = temp->_parent ;
			 		_last->_child = NULL ;
			 	} else {
			 		node_ptr temp_p = temp->_parent ;
			 		node_ptr temp_c = temp->_child ;
			 		temp_p->_child = temp_c ;
			 		temp_c->_parent = temp_p ;
			 	}
			 	--_count ;
			 }
			 		 
			 /**
			  * Search the tree for a node with the key. Returns true
			  * if a node has the key we are looking for, otherwise
			  * false.
			  */
			 bool find_key( const key_type& key ) {
			 	return search( _first, key ) ;
			 }
			 
			 /**
			  * Find the data stored inside the node with the specified
			  * key. If the node is not found, a zero is returned.
			  */
			 data_type find_data( const key_type& key) {
			 	node_ptr temp = find_node( _first, key ) ;
			 	data_type result = 0 ;
			    if( temp ) {
			        result = temp->_data ;
			    }
			 	return result ;
			 }
			 
			/**
			 * Return the number of nodes in the list
			 */
			size_type nodecount() {
				return _count ;
			}

		private:
		
			/**
			 * Main tree structure
			 */
			node_ptr _first ;
			node_ptr _last ;
			size_type _count ;
		
			/**
			 * Recursive search to find a node with key as its key.
			 */
			bool search( node_ptr curr, const key_type& key) {
				bool result = false ;
				stringstream ss1 ;
				stringstream ss2 ;
				ss1 << key ;
				ss2 << curr->_key ;
				string s1 = ss1.str() ;
				string s2 = ss2.str() ;
				size_type m = max( s1.size(), s2.size() ) ;
				size_type n = memcmp( s1.c_str(), s2.c_str(), m ) ;
				if( n == 0 ) {
					result = true ;
				} else if( curr == _last ) {
					return result ;
				} else {
					search( curr->_child, key ) ;
				}
				return result ;
			}

			/**
			 * Recursive search to find a node with key as its key and
			 * returns this node.
			 */
			node_ptr find_node( node_ptr curr, const key_type& key)
			{
				try {
					stringstream ss1 ;
					stringstream ss2 ;
					ss1 << key ;
					ss2 << curr->_key ;
					string s1 = ss1.str() ;
					string s2 = ss2.str() ;
					int m = max( s1.size(), s2.size() ) ;
					int n = memcmp( s1.c_str(), s2.c_str(), m ) ;
					if( n == 0 ) {
						return curr ;
					} else if( curr == _last ) {
						throw -1 ;
					} else {
						curr = find_node( curr->_child, key ) ;
					}
				} catch (int e) {
					cout << "ud_tree::find_node<" << typeid(data_type).name()
						 << ">: key(" << key << ") does not exist in"
						 << " this tree. **exit status(" << e << ")**"
						 << endl ;
					exit(e) ;
				}
				return curr ;
			}
		
		    /**
		     * Walks the tree and deletes all nodes.
		     */
			void destroy_tree( node_ptr curr ) {
				if( curr != NULL ) {
					destroy_tree( curr->_child ) ;
					delete curr ;
				}
			}
		
			friend std::ostream& operator<< <> (std::ostream& os, const self_type& tree) ;

	};

	template <class K, class D>
	inline std::ostream& operator<< (std::ostream& os,
	    const ud_tree<K,D>& tree)
	{
		ud_node<K, D>* temp = tree._first ;
		os << "\n*******Doubly linked list*******" << endl ;
		os << "      number of node(s): " << tree._count << endl ;
		os << "       data is type: " ;
		if( typeid(D) == typeid(int) ) {
			os << "int" << endl ;
		} else if( typeid(D) == typeid(double) ) {
			os << "double" << endl ;
		} else if( typeid(D) == typeid(float) ) {
			os << "float" << endl ;
		} else {
			os << typeid(D).name() << endl ;
		}
		os << "|----------Tree Begin----------|" << endl ;
		os << "    " << *temp << " (first)" << endl ;
		while( temp->_child != NULL ) {
			temp = temp->_child ;
			if( temp == tree._last ) {
				os << "    " << *temp << " (last)" << endl ;
			} else {
				os << "    " << *temp << endl ;
			}
		}
		os << "|-----------Tree End-----------|" << endl ;
		return os ;
	}

}	// end of namespace tree
}	// end of namespace genecis
