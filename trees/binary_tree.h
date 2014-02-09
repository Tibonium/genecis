/**
 * @file binary_tree.h
 */
 
#ifndef TREES_BINARY_TREE_H
#define TREES_BINARY_TREE_H 

#include <iostream>
#include <string>
#include <stdio.h>
#include "binary_node.h"

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
		 */
		binary_node<_type>* search(const _type key, binary_node<_type>* leaf) {
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
		 */
		void insert(const _type key, binary_node<_type>* leaf) {
			if ( key < leaf->key_value ) {
				if( leaf->left != NULL ) {
					insert(key, leaf->left) ;
				} else {
					leaf->left = new binary_node<_type> ;
					leaf->left->key_value = key ;
					leaf->left->left = NULL ;
					leaf->left->right = NULL ;
				}
			} else {
				if( leaf->right != NULL ) {
					insert(key, leaf->right) ;
				} else {
					leaf->right = new binary_node<_type> ;
					leaf->right->key_value = key ;
					leaf->right->left = NULL ;
					leaf->right->right = NULL ;
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
			if ( leaf != NULL ) {
				destroy_tree( leaf->left ) ;
				destroy_tree( leaf->right ) ;
				delete leaf ;
			}
		}
		
		/**
		 * Function that prints out the data in our binary tree
		 *
		 * @param leaf		leaf that you want to print the data about
		 */
		void printdata(binary_node<_type>* leaf) const {
			if ( leaf != NULL ) {
				printdata(leaf->left) ;
				printdata(leaf->right) ;
				cout << leaf->key_value << " " << endl;
			}
		}
		
		/**
		 * The recursive function that finds the number of nodes within
		 * a given level of the tree.
		 *
		 * @param _lvl		The level we want to find the number of
		 *					nodes on
		 * @param leaf		The leaf on the current level
		 * @param counts	Stores the number of nodes on a the level _lvl
		 */
		void levelCount(int _lvl, binary_node<_type>* leaf, int& counts) {
			if(_lvl != 1) {
				if( leaf->left != NULL ) {
					levelCount(_lvl-1, leaf->left, counts) ;
				}
				if( leaf->right != NULL ) {
					levelCount(_lvl-1, leaf->right, counts) ;
				}
			} else {
				++counts ;
			}
		}

		/**
		 * The recursive function that finds the number of nodes that
		 * have no children.
		 *
		 * @param leaf		The node that we're checking to see if
		 *					it has no children
		 * @param counts	Stores the number of nodes with no children
		 */
		void leavesCount(binary_node<_type>* leaf, int& counts) {
			if( (leaf->left == NULL) && (leaf->right == NULL) ) {
				++counts ;
			} else {
				if( leaf->left != NULL ) {
					leavesCount(leaf->left, counts) ;
				}
				if( leaf->right != NULL ) {
					leavesCount(leaf->right, counts) ;
				}
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
			if ( root != NULL ) {
				insert(key, root) ;
			} else {
				root = new binary_node<_type> ;
				root->key_value = key ;
				root->left = NULL ;
				root->right = NULL ;
			}
		}
		
		// Search function
		binary_node<_type>* search(const _type key) {
			return search(key, root) ;
		}
		
		// Destroy_tree function
		void destroy_tree() {
			destroy_tree( root ) ;
		}
		
		// Printdata function
		void printdata() const {
			printdata( root ) ;
		}
		
		// levelCount function
		int levelCount(int _lvl) {
			int counts = 0 ;
			levelCount(_lvl,root, counts) ;
			return counts ;
		}
		
		// leavesCount function
		int leavesCount() {
			int counts = 0 ;
			leavesCount(root,counts) ;
			return counts ;
		}

};

#endif
