/**
 *	@file ud_tree.h
 */

#ifndef TREE_UD_TREE_H
#define TREE_UD_TREE_H

#include <typeinfo>
#include "ud_node.h"

using namespace std ;

template<class _T> class ud_tree ;

template<class _T>
std::ostream& operator<< (std::ostream& os, const ud_tree<_T>& tree) ;

template<class _T> class ud_tree {

	public:
		/**
		 * Insert a new node within the tree. If the first is empty
		 * then set first and last to the new node. Otherwise we
		 * perform a redundency check to make sure the key doesn't
		 * already exist in our tree. If the key is unique, then we
		 * put the new node at the end of the tree.
		 */
		 inline void insert(string key, const _T& data) {
		 	ud_node<_T>* temp = 
		 		new ud_node<_T>(key, data) ;
		 	if ( _first == NULL ) {
		 		_first = temp ;
		 		_last = temp ;
		 	} else {
		 		if( !search(_first,key) ) {
				 	ud_node<_T>* old_last = _last ;
				 	old_last->child = temp ;
				 	temp->parent = old_last ;
				 	_last = temp ;
			 	}
		 	}
		 	++_count ;
		 }

		 inline void delete_node(string key) {
		 	ud_node<_T>* temp = find_node(_first,key) ;
		 	if( temp == _first ) {
		 		temp->child->parent = NULL ;
		 		_first = temp->child ;
		 	} else if( temp == _last ) {
		 		_last = temp->parent ;
		 		_last->child = NULL ;
		 	} else {
		 		ud_node<_T>* temp_p = temp->parent ;
		 		ud_node<_T>* temp_c = temp->child ;
		 		temp_p->child = temp_c ;
		 		temp_c->parent = temp_p ;
		 	}
		 	--_count ;
		 }
		 		 
		 /**
		  * Search the tree for a node with the key.  Returns true
		  * if a node has the key we are looking for, otherwise
		  * false.
		  */
		 inline bool find_key(string key) {
		 	return search(_first,key) ;
		 }
		 
		 inline _T find_data(string key) {
		 	ud_node<_T>* temp = find_node(_first,key) ;
		 	return temp->data ;
		 }
		 
		/**
		 * Return the number of nodes in the list
		 */
		inline int nodecount() {
			return _count ;
		}
		
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
		~ud_tree() {
//			destroy_tree() ;
		}

	private:
		/**
		 * Main tree structure
		 */
		ud_node<_T>* _first ;
		ud_node<_T>* _last ;
		int _count ;
		
		/**
		 * Recursive search to find a node with key as its key.
		 */
		inline bool search(ud_node<_T>* curr, string key) {
			bool result = false ;
			if( (curr->key).compare(key) == 0 ) {
				result = true ;
			} else if( curr == _last ) {
				return result ;
			} else {
				search(curr->child, key) ;
			}
			return result ;
		}

		/**
		 * Recursive search to find a node with key as its key and
		 * returns this node.
		 */
		inline ud_node<_T>* find_node(ud_node<_T>* curr, string key) {
			try {
				if( (curr->key).compare(key) == 0 ) {
					return curr ;
				} else if( curr == _last ) {
					throw -1 ;
				} else {
					curr = find_node(curr->child, key) ;
				}
			} catch (int e) {
				cout << "ud_tree::find_node<" << typeid(_T).name()
					 << ">: key(" << key << ") does not exist in"
					 << " this tree. **exit status(" << e << ")**"
					 << endl ;
				exit(e) ;
			}
			return curr ;
		}
		
		friend std::ostream& operator<< <> (std::ostream& os, const ud_tree<_T>& tree) ;

};

template <class _T>
inline std::ostream& operator<< (std::ostream& os, const ud_tree<_T>& tree) {
	ud_node<_T>* temp = tree._first ;
	os << "\n*******Doubly linked list*******" << endl ;
	os << "      number of node(s): " << tree._count << endl ;
	os << "       data is type: " ;
	if( typeid(_T) == typeid(int) ) {
		os << "int" << endl ;
	} else if( typeid(_T) == typeid(double) ) {
		os << "double" << endl ;
	} else if( typeid(_T) == typeid(float) ) {
		os << "float" << endl ;
	} else {
		os << typeid(_T).name() << endl ;
	}
	os << "|----------Tree Begin----------|" << endl ;
	os << "    " << *temp << " (first)" << endl ;
	while(temp->child != NULL) {
		temp = temp->child ;
		if( temp == tree._last ) {
			os << "    " << *temp << " (last)" << endl ;
		} else {
			os << "    " << *temp << endl ;
		}
	}
	os << "|-----------Tree End-----------|" << endl ;
	return os ;
}


#endif
