/**
 *	@file ud_tree.h
 */

#ifndef UD_TREE_H
#define UD_TREE_H

#include <string>

using namespace std ;

template<class _T> class ud_tree {

	private:
		/**
		 * Main tree structure
		 */
		ud_node<_T>* first ;
		ud_node<_T>* last ;
		
		/**
		 * Inserts a new node at the end of the tree
		 */
		void insert(string _key, _T _data) ;
	
	public:
		/**
		 *
		 */
		 void insert(string _key, _T _data) {
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
		 	delete temp ;
		 }
	
		/**
		 *  Constructor
		 */
		ud_tree() {
			first = NULL ;
			last = NULL ;
		}
		
		/**
		 *  Destructor
		 */
		~ud_tree() {
			destroy_tree() ;
		}

};

#endif
