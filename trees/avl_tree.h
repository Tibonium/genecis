/**
 * @file avl_tree.h
 */

#ifndef TREES_AVL_TREE_H
#define TREES_AVL_TREE_H

#include "avl_node.h"

template <class _type> class avl_tree {

	private:
	
		/**
		 * Create the root node of the avl_tree and two other nodes
		 * that allow us to keep track of where we are and where
		 * we need to go with inserting, rotating, and balancing the
		 * tree.
		 */
		avl_node<_type>* root ;

		avl_node<_type>* ancestor ;
		
		avl_node<_type>* temp ;
			
		/**
		 * This function takes a newly created leaf and inserts it
		 * within the avl_tree using the binary tree schema.
		 *
		 * @param leaf		New leaf to be inserted into tree.
		 */
		void insert(avl_node<_type>* leaf) ;
		
		/**
		 * Primary function that does all of the work to make sure
		 * that the avl_tree follows the correct schema. This function
		 * is called after inserting a new leaf to the tree and restores
		 * the correct orientation of the leaves in the tree.
		 *
		 * @param history	Last tree leaf that has to be rebalanced
		 * @param newleaf	The leaf that we just inserted
		 */
		void restore_avl_tree(avl_node<_type>* history, avl_node<_type>* newleaf) ;

		/**
		 * This function is called to make sure that all balance
		 * variables of all the nodes are appropriately set.
		 *
		 * @param end		last leaf up the tree that needs to be 
		 *					adjusted
		 * @param start		leaf that was just inserted
		 */
		void adjustbalance(avl_node<_type>* end, avl_node<_type>* start) ;

		/**
		 * Perform a left rotation about the designated leaf. This
		 * will rotate LLnode's parent into LLnode's left child and
		 * LLnode's left child will become the former parent's
		 * right child.
		 *
		 * @param LLnode	leaf that needs to be rotated around
		 */
		void rotateLeft(avl_node<_type>* LLnode) ;
		
		/**
		 * Perform a right rotation about the designated leaf. This
		 * will rotate RRnode's parent into RRnode's right child and
		 * RRnode's right child will become the former parent's
		 * left child.
		 *
		 * @param RRnode	leaf that needs to be rotated around
		 */
		void rotateRight(avl_node<_type>* RRnode) ;
		
		/**
		 * Performs Right to Left balancing
		 *
		 * @param end	 last leaf up tree that needs adjusting
		 * @param start	 leaf that was just inserted
		 */
		void adjustRightLeft(avl_node<_type>* end, avl_node<_type>* start) ;
		
		/**
		 * Performs Left to Right balancing
		 *
		 * @param end	 last leaf up tree that needs adjusting
		 * @param start	 leaf that was just inserted
		 */
		void adjustLeftRight(avl_node<_type>* end, avl_node<_type>* start) ;
		
		/**
		 * Destroys the tree from the bottom up
		 *
		 * @param leaf	leaf to delete
		 */
		void clear_tree(avl_node<_type>* leaf) ;
	
	public:
	
		/**
		 * Inserts a new leaf into the avl_tree with the new key
		 *
		 * @param key	key that the new leaf will have
		 */
		void insert(const _type& key) ;
		
		/**
		 * Searches throughout the tree looking for a leaf that has
		 * the requested key. Returns false if key does not exist
		 * in the tree.
		 *
		 * @param key	key to search for in the tree
		 */
		bool search(const _type& key) const ;
		
		// Constructor
		avl_tree() ;
		
		// Destructor
		~avl_tree() ;

};

#endif
