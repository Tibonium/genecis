/**
 * @file btree.h
 */
 
#ifndef GENECIS_TREE_BTREE_H
#define GENECIS_TREE_BTREE_H

namespace genecis {
namespace tree {

template <class _type, int _size> class btree {

	private:
	
		// Root of our tree
		btree_node<_type,_size>* root ;
		
		/**
		 * This function is the primary worker, placing the key on
		 * a ring that follows the btree schema.
		 *
		 * @param n		Ring to check if the key goes on
		 * @param key	The key we want to add to a ring
		 */
		void insert(btree_node<_type,_size>* n, _type key) {
			if ( n == NULL ) {
				n = new btree_node<_type,_size> ;
				n->num_keys = 1 ;
				for(int i=0; i<MAX; ++i) {
					if( i==0 ) { n->key_ring[0] = key ; }
					else { n->key_ring[i] = 0 ; }
					n->child[i] = NULL ;
				}
			} else
			if ( !search(root,key) ) {
				if ( n->num_keys != MAX-1 ) {
					put_key(n,key) ;
				} else {
					split(n,key) ;
				}
			} else {
				cout << "Key: " << key << " already exists." << endl;
			}
		}

		/**
		 * This function puts the key on the ring in the appropriate
		 * slot.
		 *
		 * @param n		The ring we want to put our key on
		 * @param key	The key we want to put on the ring 
		 */
		void put_key(btree_node<_type,_size>* n, _type key) {
			//------------------------------------------------------
			// Find the first empty key slot on this ring
			//------------------------------------------------------
			int i ;
			for(i=0; i<MAX-1; ++i) {
				if( n->child[i] == NULL ) break ;
			}
	
			//------------------------------------------------------
			// Case 1: The key in question is bigger then the last
			//		   non-empty key on the ring, so put the key
			//		   there
			//------------------------------------------------------
			if( key > n->key_ring[i-1] ) {
				n->key_ring[i] = key ;
			} else	
			//------------------------------------------------------
			// Case 2: The key in question is smaller then the last
			//		   non-empty key but larger then some other key
			//		   on the ring. Move all bigger keys up a slot
			//         and put the new key in the new empty slot
			//------------------------------------------------------
			if( (key > n->key_ring[0]) && (key < n->key_ring[i-1]) )
			{
				for(int j=i-1; j>1; --j) {
					n->key_ring[j+1] = n->key_ring[j] ;
					if ( key > n->key_ring[j-1] ) {
						n->key_ring[j] = key ; 
					}
				}
			}
			//------------------------------------------------------
			// Case 3: The key in question is smaller then all the
			//         keys on the current ring, so move all keys up
			//         a slot and put the new key at the beginning
			//		   of the ring.
			//------------------------------------------------------
			else {
				for(int j=i-1; j>0; --j) {
					n->key_ring[j+1] = n->key_ring[j] ; 
				}
				n->key_ring[0] = key ;
			}
		}

	
	public:
	
		/**
		 * Allows the user to insert a key into the btree
		 *
		 * @param key		The key we want to add
		 */
		void insert(_type key) {
			insert(root,key) ;
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

}	// end of namespace tree
}	// end of namespace genecis

#endif
