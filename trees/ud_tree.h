/**
 *	@file ud_tree.h
 */

#ifndef UD_TREE_H
#define UD_TREE_H

#include <string>

using namespace std ;

template<class _T> class ud_tree {

	public:
		/**
		 * Insert a new node within the tree.  If the first
		 * is empty then set first and last to the new node
		 * otherwise put it at the end of the list and make
		 * it the new last.
		 */
		 void insert(string _key, _T& _data) {
		 	ud_node<_T>* temp = 
		 		new ud_node<_T>(_key, _data) ;
		 	if ( first == NULL ) {
		 		first = temp ;
		 		last = temp ;
		 	} else {
			 	ud_node<_T>* old_last = last ;
			 	old_last->child = temp ;
			 	last = temp ;
		 	}
		 	temp->parent = NULL ;
		 	temp->child = NULL ;
		 	delete temp ;
		 	++count ;
		 }
		 
		/**
		 * Return the number of nodes in the list
		 */
		inline int nodecount() {
			return count ;
		}
		
		/**
		 *  Constructor
		 */
		ud_tree() {
			first = NULL ;
			last = NULL ;
			count = 0 ;
		}
		
		/**
		 *  Destructor
		 */
		~ud_tree() {
			destroy_tree() ;
		}

	private:
		/**
		 * Main tree structure
		 */
		ud_node<_T>* first ;
		ud_node<_T>* last ;
		int count ;

};

#endif
