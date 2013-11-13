/**
 * @file btree.h
 */
 
#ifndef TREES_BTREE_H
#define TREES_BTREE_H

template <class _type, int _size> class btree {

	private:
	
		btree_node<_type,_size>* root ;
		
		void insert(btree_node<_type,_size>* node, const _type& key) {
			if ( node != NULL ) {
				for(int i=0; i<_size-2; ++i) {
					if ( node->key_list[i] != NULL ) {
						if ( node->key_list[i] < key ) {
							node->key_list[i+1] = key ;
							return ;
						} else {
							_type temp_key = node->key_list[i] ;
							node->key_list[i] = key ;
							node->key_list[i+1] = temp_key ;
						}
					}
				}
			} else {
				node = new btree_node<_type,_size> ;
				for(int i=0; i<_size-1; ++i) {
					if ( i == 0 ) node->key_list[i] = key ;
					else node->key_list[i] = NULL ;
				}
				for(int i=0; i<_size; ++i) {
					node->child[i] = NULL ;
				}
			}
		}
		
		void search() {}
		
		void split_node() {}
		
		/**
		 * Delete the leaves and keys from the bottom of the tree up.
		 * Recursively calls itself on each child inside of the
		 * passed leaf.
		 * 
		 * @param leaf		leaf and associated keys to delete
		 */
		void destroy_tree(btree_node<_type,_size>* leaf) {
			for(int i=0; i<_size; ++i) {
				if ( leaf->child[i] != NULL ) {
					destroy_tree(leaf->child[i]) ;
				}
			}
			delete[] leaf->key_list ;
			delete leaf ;
		}
	
	public:
	
		void insert(const _type& key) {
			insert(root,key) ;
		}
	
		bool search(const _type& key) {
		
		}
	
		// Constructor
		btree() {
			root = NULL ;
		}
		
		// Destructor
		~btree() {
			destroy_tree(root) ;
		}

};

#endif
