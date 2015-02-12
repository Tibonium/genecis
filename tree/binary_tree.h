/**
 * @file binary_tree.h
 */
 
#pragma once

#include <iostream>
#include <cstring>
#include <cstdio>

namespace genecis {
namespace tree {

	using namespace std ;

	template<class T>
	struct binary_node {

		public:
	        typedef T                           value_type ;
	        typedef binary_node<value_type>     self_type ;
	        typedef self_type*                  node_ptr ;
	        
			value_type key ;
			node_ptr left ;
			node_ptr right ;

	};
	
	template<class T>
	class binary_tree {

		public:
		
		    typedef T                               value_type ;
		    typedef std::size_t                     size_type ;
		    typedef binary_tree<value_type>         self_type ;
	        typedef binary_node<value_type>         node_type ;
		    typedef typename node_type::node_ptr    node_ptr ;
	
			/**
			 * Constructor
			 */
			binary_tree() {
				_root = NULL ;
			}

			/**
			 * Destructor
			 */
			virtual ~binary_tree() {
				destroy_tree( _root ) ;
			}
		
		    /**
		     * Inserts a key into the binary tree.
		     */
			void insert( const value_type key ) {
				if ( _root != NULL ) {
					insert( key, _root ) ;
				} else {
					_root = new node_type ;
					_root->key = key ;
					_root->left = NULL ;
					_root->right = NULL ;
				}
			}
		
			/**
			 * Searches the binary tree for a node with the requested
			 * key. Returns the node if a node with the key exists
			 * otherwise, returns NULL.
			 *
			 * @param key       node identifier to search for
			 */
			node_ptr search( const value_type key ) {
				return search( key, _root ) ;
			}
		
			// Printdata function
			void printdata() const {
				printdata( _root ) ;
			}
		
			// levelCount function
			size_type levelCount( size_type lvl ) {
				size_type counts = 0 ;
				levelCount( lvl, _root, counts ) ;
				return counts ;
			}
		
			// leavesCount function
			size_type leavesCount() {
				size_type counts = 0 ;
				leavesCount( _root, counts ) ;
				return counts ;
			}
			
		private:
	
			/**
			 * Root node for the binary tree.
			 */ 
			node_ptr _root ;
			 
			/**
			 * Our recursive search function that returns the leaf
			 * that is equal to the key we're looking for or NULL, meaning
			 * the key is not in our current binary tree.
			 *
			 * @param key		The key we're looking for
			 * @param leaf		The leaf with this key
			 */
			node_ptr search( const value_type key, node_ptr leaf ) {
				if ( leaf != NULL ) {
					if ( key == leaf->key ) {
						return leaf ;
					} else
					if ( key < leaf->key ) {
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
			void insert( const value_type key, node_ptr leaf ) {
				if ( key < leaf->key ) {
					if( leaf->left != NULL ) {
						insert(key, leaf->left) ;
					} else {
						leaf->left = new node_type ;
						leaf->left->key = key ;
						leaf->left->left = NULL ;
						leaf->left->right = NULL ;
					}
				} else {
					if( leaf->right != NULL ) {
						insert(key, leaf->right) ;
					} else {
						leaf->right = new node_type ;
						leaf->right->key = key ;
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
			void destroy_tree( node_ptr leaf ) {
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
			void printdata( node_ptr leaf ) const {
				if ( leaf != NULL ) {
					printdata(leaf->left) ;
					printdata(leaf->right) ;
					cout << leaf->key << " " << endl;
				}
			}
		
			/**
			 * The recursive function that finds the number of nodes within
			 * a given level of the tree.
			 *
			 * @param lvl		The level we want to find the number of
			 *					nodes on
			 * @param leaf		The leaf on the current level
			 * @param counts	Stores the number of nodes on a the level _lvl
			 */
			void levelCount( size_type lvl, node_ptr leaf, size_type& counts ) {
				if(lvl != 1) {
					if( leaf->left != NULL ) {
						levelCount(lvl-1, leaf->left, counts) ;
					}
					if( leaf->right != NULL ) {
						levelCount(lvl-1, leaf->right, counts) ;
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
			void leavesCount( node_ptr leaf, size_type& counts ) {
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

	};
	
}	// end of namespace tree
}	// end of namespace genecis
