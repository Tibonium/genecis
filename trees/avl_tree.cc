/**
 * @file avl_tree.cc
 */
 
#include "avl_tree.h"

//------------------------------------------------------------------
// Pulic Memeber functions
//------------------------------------------------------------------

template <class _type>
avl_tree::avl_tree() {
	root = NULL ;
}

template <class _type>
avl_tree::~avl_tree() {
	clear_tree(root) ;
}

template <class _type>
void avl_tree::insert(const _type& key) {
	ancestor = NULL ;
	temp = root ;
	leaf = new avl_node<_type> ;
	leaf->key = key ;
	leaf->balance = '' ;
	leaf->left = NULL ;
	leaf->right = NULL ;
	leaf->parent = NULL ;
	insert(leaf) ;
}

template <class _type>
bool avl_tree::search(const _type& key) const {

}

//------------------------------------------------------------------
// Private Memeber functions
//------------------------------------------------------------------

/**
 * Insert a new leaf somewhere within the tree following the basic
 * binary tree ordering schema.
 */
template <class _type>
void avl_tree::insert(avl_node<_type>* leaf) {
	if (root == NULL) {
		root = leaf ;
		return ;
	}

	if (temp == NULL) {
		temp = leaf ;
		restore_avl_tree(ancestor,leaf) ;
	} else
	if (temp->key < leaf->key) {
		leaf->parent = temp ;
		if (temp->balance == '=') { ancestor = temp ; }
		temp = temp->left ;
		insert(leaf) ;
	} else {
		leaf->parent = temp ;
		if (temp->balance == '=') { ancestor = temp ; } 
		temp = temp->right ;
		insert(leaf) ;
	}
}

/**
 * Restore the avl_tree schema after inserting a new leaf
 */
template <class _type>
void avl_tree::restore_avl_tree( 
	avl_node<_type>* history, avl_node<_type>* newleaf )
{

	//--------------------------------------------------------------
	// Case 1: history is NULL, ie all balance factors are '='
	//--------------------------------------------------------------
	if (history == NULL) {
		if (newleaf->key < root->key) {
			root->balance = 'L' ;
		} else {
			root->balance = 'R' ;
		}
		adjustbalance(root,newleaf) ;
	} else
	
	//--------------------------------------------------------------
	// Case 2: placed newleaf in the opposite side of the history's
	//         subtree.
	// history->balance = 'L' and newleaf is on the right
	//               OR
	// history->balance = 'R' and newleaf is on the left
	//--------------------------------------------------------------
	if ( (history->balance == 'L' && newleaf->key > history->key) ||
	     (history->balance == 'R' && newleaf->key < history->key) )
	{
		history->balance = '=' ;
		adjustbalance(history,newleaf) ;
	} else
	
	//--------------------------------------------------------------
	// Case 3: history->balance = 'R' and newleaf was put on the
	//         right subtree of history's right child.
	//--------------------------------------------------------------
	if ( history->balance = 'R' &&
		 newleaf->key > history->right->key )
	{
		history->balance = '=' ;
		rotateLeft(history) ;
		adjustbalance(history->parent,newleaf) ;
	} else
	
	//--------------------------------------------------------------
	// Case 4: history->balance = 'L' and newleaf was put on the
	//         left subtree of history's left child.
	//--------------------------------------------------------------
	if ( history->balance = 'L' &&
		 newleaf->key < history->left->key )
	{
		history->balance = '=' ;
		rotateRight(history) ;
		adjustbalance(history->parent,newleaf) ;
	} else
	
	//--------------------------------------------------------------
	// Case 5: history->balance = 'R' and newleaf was put on the
	//		   left subtree of history's right child.
	//--------------------------------------------------------------
	if ( history->balance 'R' &&
		 newleaf->key < history->right->left->key )
	{
		rotateRight(history->right) ;
		rotateLeft(history) ;
		adjustRightLeft(history,newleaf) ;
	} else
	
	//--------------------------------------------------------------
	// Case 6: history->balance = 'L' and newleaf was put on the
	//         right subtree of history's left child.
	//--------------------------------------------------------------
	{
		rotateLeft(histor->left) ;
		rotateRight(history) ;
		adjustLeftRight(history,newleaf) ;
	}
}

/**
 * Perform a left rotation at the designated node
 */
template <class _type>
void avl_tree::rotateLeft(avl_node<_type>* LLnode) {
	avl_node<_type>* temp = LLnode->right ;
	LLnode->right = temp->left ;
	if ( temp->left != NULL ) {
		temp->left->parent = LLnode ;
	}
	if ( LLnode->parent == NULL ) {
		root = temp ;
		temp->parent = NULL ;
	} else
	if ( LLnode->parent->left == LLnode ) {
		LLnode->parent->left = temp ;
	} else {
		LLnode->parent->right = temp ;
	}
	
	temp->left = LLnode ;
	LLnode->parent = temp ;
}

/**
 * Perform a right rotation at the designated node
 */
template <class _type>
void avl_tree::rotateRight(avl_node<_type>* RRnode) {
	avl_node<_type>* temp = RRnode->left ;
	RRnode->left = temp->right ;
	if ( temp->right != NULL ) {
		temp->right->parent = RRnode ;
	}
	if ( RRnode->parnet == NULL ) {
		root = temp ;
		temp->parent = NULL ;
	} else
	if ( RRnode->parent->left == RRnode ) {
		RRnode->parent->left = temp ;
	} else {
		RRnode->parent->right = temp ;
	}
	
	temp->right = RRnode ;
	RRnode->parent = temp ;
}

/**
 * Re-adjust the balances of the avl_tree
 */
template <class _type>
void avl_tree::adjustbalance(
		avl_node<_type>* end, avl_node<_type>* start )
{
	if ( start != end ) {
		if ( start->key < start->parent->key ) {
			start->parent->balance = 'L' ;
			adjustbalance(end,start->parent) ;
		} else {
			start->parent->balance = 'R' ;
			adjustbalance(end,start->parent) ;
		}
	}
}

/**
 * Perform adjustments to the balance factors from right to left
 */
template <class _type>
void avl_tree::adjustRightLeft(
		avl_node<_type>* end, avl_node<_type>* start )
{
    if ( end == root ) {
        end->balance = '=' ;
    } else
    if ( start->key < end->parent->key ) {
        end->balance = 'R' ;
        adjustbalance(end->parent->left, start) ;
    } else {
        end->balance = '=' ;
        end->parent->left->balance = 'L' ;
        adjustbalance(end, start) ;
    }
}

/**
 * Perform adjustments to the balance factors from left to right
 */
template <class _type>
void avl_tree::adjustLeftRight(
		avl_node<_type>* end, avl_node<_type>* start )
{
    if ( end == root ) {
        end->balance = '=' ;
    } else
    if ( start->key > end->parent->key ) {
        end->balance = 'L' ;
        adjustbalance(end->parent->right, start) ;
    } else {
        end->balance = '=' ;
        end->parent->right->balance = 'R' ;
        adjustbalance(end, start) ;
    }
}

/**
 * Destroy all nodes in the avl_tree
 */
template <class _type>
void avl_tree::clear_tree(avl_node<_type>* leaf) {
	if (leaf != NULL) {
		clear_tree(leaf->left) ;
		clear_tree(leaf->right) ;
		delete leaf ;
	}
}
