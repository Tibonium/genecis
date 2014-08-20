/**
 *	@file ud_tree.h
 */

#ifndef GENECIS_TREE_UD_TREE_H
#define GENECIS_TREE_UD_TREE_H

#include <typeinfo>
#include <genecis/tree/ud_node.h>

namespace genecis {
namespace tree {

	using namespace std ;

	template<class KEY_TYPE, class DATA_TYPE> class ud_tree ;

	template<class KEY_TYPE, class DATA_TYPE>
	std::ostream& operator<< (std::ostream& os,
		const ud_tree<KEY_TYPE, DATA_TYPE>& tree) ;

	template<class KEY_TYPE, class DATA_TYPE> class ud_tree {

		typedef ud_tree self_type ;

		public:
			/**
			 * Insert a new node within the tree. If the first is empty
			 * then set first and last to the new node. Otherwise we
			 * perform a redundency check to make sure the key doesn't
			 * already exist in our tree. If the key is unique, then we
			 * put the new node at the end of the tree.
			 */
			 inline void insert(const KEY_TYPE& key, const DATA_TYPE& data) {
			 	ud_node<KEY_TYPE, DATA_TYPE>* temp = 
			 		new ud_node<KEY_TYPE, DATA_TYPE>(key, data) ;
			 	if ( _first == NULL ) {
			 		_first = temp ;
			 		_last = temp ;
				 	++_count ;
			 	} else {
			 		if( !search(_first,key) ) {
					 	ud_node<KEY_TYPE, DATA_TYPE>* old_last = _last ;
					 	old_last->child = temp ;
					 	temp->parent = old_last ;
					 	_last = temp ;
		 			 	++_count ;
				 	}
			 	}
			 	delete temp ;
			 }

			 inline void delete_node(const KEY_TYPE& key) {
			 	ud_node<KEY_TYPE, DATA_TYPE>* temp = find_node(_first,key) ;
			 	if( temp == _first ) {
			 		temp->child->parent = NULL ;
			 		_first = temp->child ;
			 	} else if( temp == _last ) {
			 		_last = temp->parent ;
			 		_last->child = NULL ;
			 	} else {
			 		ud_node<KEY_TYPE, DATA_TYPE>* temp_p = temp->parent ;
			 		ud_node<KEY_TYPE, DATA_TYPE>* temp_c = temp->child ;
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
			 inline bool find_key(const KEY_TYPE& key) {
			 	return search(_first,key) ;
			 }
			 
			 inline DATA_TYPE find_data(const KEY_TYPE& key) {
			 	ud_node<KEY_TYPE, DATA_TYPE>* temp = find_node(_first,key) ;
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
				destroy_tree(_first) ;
			}

		private:
			/**
			 * Main tree structure
			 */
			ud_node<KEY_TYPE, DATA_TYPE>* _first ;
			ud_node<KEY_TYPE, DATA_TYPE>* _last ;
			int _count ;
		
			/**
			 * Recursive search to find a node with key as its key.
			 */
			inline bool search(ud_node<KEY_TYPE, DATA_TYPE>* curr, const KEY_TYPE& key) {
				bool result = false ;
				stringstream ss1 ;
				stringstream ss2 ;
				ss1 << key ;
				ss2 << curr->key ;
				string s1 = ss1.str() ;
				string s2 = ss2.str() ;
				int m = max( s1.size(), s2.size() ) ;
				int n = memcmp(s1.c_str(), s2.c_str(), m ) ;
				if( n == 0 ) {
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
			inline ud_node<KEY_TYPE, DATA_TYPE>* find_node(
				ud_node<KEY_TYPE, DATA_TYPE>* curr, const KEY_TYPE& key)
			{
				try {
					stringstream ss1 ;
					stringstream ss2 ;
					ss1 << key ;
					ss2 << (curr->key) ;
					string s1 = ss1.str() ;
					string s2 = ss2.str() ;
					int m = max( s1.size(), s2.size() ) ;
					int n = memcmp(s1.c_str(), s2.c_str(), m ) ;
					if( n == 0 ) {
						return curr ;
					} else if( curr == _last ) {
						throw -1 ;
					} else {
						curr = find_node(curr->child, key) ;
					}
				} catch (int e) {
					cout << "ud_tree::find_node<" << typeid(DATA_TYPE).name()
						 << ">: key(" << key << ") does not exist in"
						 << " this tree. **exit status(" << e << ")**"
						 << endl ;
					exit(e) ;
				}
				return curr ;
			}
		
			void destroy_tree(ud_node<KEY_TYPE, DATA_TYPE>* curr) {
				if( curr != NULL ) {
					destroy_tree(curr->child) ;
					delete curr ;
				}
			}
		
			friend std::ostream& operator<< <> (std::ostream& os,
				const ud_tree<KEY_TYPE, DATA_TYPE>& tree) ;

	};

	template <class KEY_TYPE, class DATA_TYPE>
	inline std::ostream& operator<< (std::ostream& os,
			const ud_tree<KEY_TYPE, DATA_TYPE>& tree)
	{
		ud_node<KEY_TYPE, DATA_TYPE>* temp = tree._first ;
		os << "\n*******Doubly linked list*******" << endl ;
		os << "      number of node(s): " << tree._count << endl ;
		os << "       data is type: " ;
		if( typeid(DATA_TYPE) == typeid(int) ) {
			os << "int" << endl ;
		} else if( typeid(DATA_TYPE) == typeid(double) ) {
			os << "double" << endl ;
		} else if( typeid(DATA_TYPE) == typeid(float) ) {
			os << "float" << endl ;
		} else {
			os << typeid(DATA_TYPE).name() << endl ;
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

}	// end of namespace tree
}	// end of namespace genecis

#endif
