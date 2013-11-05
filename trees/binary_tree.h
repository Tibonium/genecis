/**
 * @file binary_tree.h
 */
 
#ifndef BINARY_TREE_H
#define BINARY_TREE_H 

#include <iostream>
#include <string>
#include <stdio.h>
#include "binary_node.h"

//#define TREE_DEBUG

using namespace std ;

template <typename _type> class binary_tree {

	private:
	
		// Creates a root node to begin the tree at
		binary_node<_type>* root ;
		
		/**
		 * The are the functions that do all of the work
		 * Making them private prevents the user from starting
		 * in the binary tree from anywhere other then the
		 * root node.
		 */
		 
		 
		/**
		 * Our recursive search function that returns the leaf
		 * that is equal to the key we're looking for or NULL, meaning
		 * the key is not in our current binary tree.
		 *
		 * @param key		The key we're looking for
		 * @param leaf		The leaf with this key
		 *
		 * This is done recursively, until either it runs into a leaf
		 * that is NULL which means the key is not in the tree, or finds
		 * the leaf that corresponds to the key that is being searched
		 * for. 
		 *
		 * Step 1:	Check if the leaf is NULL. If not, step 2, otherwise step 6
		 * Step 2:	Check if key is equal to this leaf's key_value. If so,
		 *			return this leaf, otherwise step 3.
		 * Step 3:	Check to see if the key is less then the current leaf's
		 *			key_value, if so step 4, otherwise step 5.
		 * Step 4:	Call search again with arguements of key and current leaf's
		 *			left node, procede to step 2.
		 * Step 5:	Call search again with arguements of key and current leaf's
		 *			right node, procede to step 2. 
		 * Step 6:	Return NULL because the key you're searching for is not
		 *			in the current binary_tree.
		 */
		node<_type>* search(const _type key, binary_node<_type>* leaf) {
			if ( leaf != NULL ) {
				if ( key == leaf->key_value ) {
					return leaf ;
				} else
				if ( key < leaf->key_value ) {
					search(key, leaf->left) ;
				} else {
					search(key, leaf->right) ;
				}
			} else {
				return NULL ;
			}	
		}
		
		/**
		 * The recursive function that looks for an appropriately
		 * empty node and puts the value in it, then creates two,
		 * left and right, nodes and sets them to NULL
		 *
		 * @param key		The key we're looking to insert
		 * @param leaf		The leaf in the tree we are looking at
		 *
		 * Insert a key at the appropriate location of the
		 * binary tree. When it reaches the correct location
		 * in the tree it then creates a new node and stores
		 * the key in it.
		 */
		void insert(const _type key, binary_node<_type>* leaf) {
			if ( key < leaf->key_value ) {
				if( leaf->left != NULL ) {					// check to see if the leaf to my left is NULL
					insert(key, leaf->left) ;				// if so, call insert on that leaf
				} else {
					#ifdef TREE_DEBUG
						cout << "set leaf->left to: " << key << endl;
					#endif
					leaf->left = new binary_node<_type> ;			// otherwise create a new node
					leaf->left->key_value = key ;			// set it to key
					leaf->left->left = NULL ;				// then create a new left under this node and set to NULL
					leaf->left->right = NULL ;				// and create a new right under this node and set to NULL
				}
			} else {
				if( leaf->right != NULL ) {					// check to see if the leaf to my left is NULL
					insert(key, leaf->right) ;				// if so, call insert on that leaf
				} else {
					#ifdef TREE_DEBUG
						cout << "set leaf->right to: " << key << endl;
					#endif
					leaf->right = new binary_node<_type> ;			// otherwise create a new node
					leaf->right->key_value = key ;			// set it to key
					leaf->right->left = NULL ;				// then create a new left under this node and set to NULL
					leaf->right->right = NULL ;				// and create a new right under this node and set to NULL
				}
			}
		}
		
		/**
		 * The recursive function that destroys the binary tree
		 * from the bottom up.
		 *
		 * @param leaf		leaf to delete
		 */
		void destroy_tree(binary_node<_type>* leaf) {
			if ( leaf != NULL ) {							// check to see if this node is empty (NULL). If not...
				destroy_tree( leaf->left ) ;				// call destroy_tree on the left node under this one
				destroy_tree( leaf->right ) ;				// call destroy_tree on the right node under this one
				delete leaf ;								// if my last call to destroy_tree found a leaf == NULL, start deleting leaves
			}
		}
		
		void printdata(node<_type>* leaf) const {
			#ifdef TREE_DEBUG
				cout << "***entering printdata***" << endl;
			#endif
			if ( leaf != NULL ) {
				printdata(leaf->left) ;
				printdata(leaf->right) ;
				cout << leaf->key_value << " " << endl;
			}
		}
	
	public:
	
		// Constructor
		binary_tree<_type>() {
			root = NULL ;
		}

		// Destructor
		~binary_tree<_type>() {
			destroy_tree() ;
		}
		
		void insert(const _type key) {
			#ifdef TREE_DEBUG
				cout << "***Entering binary_tree::insert(key)***" << endl;
			#endif
			if ( root != NULL ) {
				#ifdef TREE_DEBUG
					cout << "***Root was not NULL***" << endl;
				#endif
				insert(key, root) ;
			} else {
				#ifdef TREE_DEBUG
					cout << "***Root was NULL***" << endl;
					cout << "set root to: " << key << endl;
				#endif
				root = new binary_node<_type> ;
				root->key_value = key ;
				root->left = NULL ;
				root->right = NULL ;
			}
		}
		
		node<_type>* search(const _type key) {
			return search(key, root) ;
		}
		
		void destroy_tree() {
			destroy_tree( root ) ;
		}
		
		void printdata() const {
			printdata( root ) ;
		}

};

#endif
