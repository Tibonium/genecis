/**
 * @file quadtree.h
 */

#pragma once

#include <genecis/container/array.h>
#include <genecis/container/dynamic_array.h>
#include <genecis/tree/quadtree_functors.h>

using namespace genecis::container ;

namespace genecis {
namespace tree {

            
/**
 * Quadrant numbers
 *  _________________
 * |        |        |
 * |   1    |   0    |
 * |        |        |
 * |-----------------|
 * |        |        |
 * |   2    |   3    |
 * |________|________|
 */
enum QUADRANT
{
    TOP_RIGHT = 0,
    TOP_LEFT = 1,
    BOTTOM_LEFT = 2,
    BOTTOM_RIGHT = 3
} ;

/**
 * Nodes and leaf class for a quadtree.
 */
template<class T>
class quad {

    public:

        typedef T                                      value_type ;
        typedef typename T::coord_type                 coord_type ;
        typedef value_type*                            value_ptr ;
        typedef quad<value_type>                       self_type ;
        typedef self_type*                             node_type ;
        typedef array<node_type>                       container_type ;
        typedef array<T>                               data_container ;
        typedef typename container_type::iterator      iterator ;
        typedef typename container_type::pointer       pointer ;
        typedef typename container_type::size_type     size_type ;

        /**
         * Constructor
         *
         * Initializes the quadrant container elements
         * all to NULL.
         */
        quad( coord_type x, coord_type y,
              coord_type width, coord_type height,
              size_type num )
        : __x(x), __y(y), __width(width), __height(height), __index(0)
        {
            __quadrant = container_type(4, NULL) ;
            __data = data_container(num) ;
        }

        /**
         * Copy Constructor
         */
        quad( const node_type other ) {
            __x = other->__x ;
            __y = other->__y ;
            __width = other->__width ;
            __height = other->__height ;
            __quadrant = container_type(4, NULL) ;
            __data = data_container( other->size() ) ;
            __parent = other->parent() ;
            __index = 0 ;
        }

        /**
         * Destructor
         */
        virtual ~quad() {}

        /** Returns the top right quadrant **/
        node_type top_right() const {
            return __quadrant(TOP_RIGHT) ;
        }

        /** Sets the top right quadrant **/
        void top_right( node_type n ) {
            if( __quadrant(TOP_RIGHT) ) delete __quadrant(TOP_RIGHT) ;
            __quadrant(TOP_RIGHT) = n ;
        }

        /** Returns the top left quadrant **/
        node_type top_left() const {
            return __quadrant(TOP_LEFT) ;
        }

        /** Sets the top left quadrant **/
        void top_left( node_type n ) {
            if( __quadrant(TOP_LEFT) != NULL ) delete __quadrant(TOP_LEFT) ;
            __quadrant(TOP_LEFT) = n ;
        }

        /** Returns the bottom left quadrant **/
        node_type bottom_left() const {
            return __quadrant(BOTTOM_LEFT) ;
        }

        /** Sets the bottom left quadrant **/
        void bottom_left( node_type n ) {
            if( __quadrant(BOTTOM_LEFT) ) delete __quadrant(BOTTOM_LEFT) ;
            __quadrant(BOTTOM_LEFT) = n ;
        }

        /** Returns the bottom right quadrant **/
        node_type bottom_right() const {
            return __quadrant(BOTTOM_RIGHT) ;
        }

        /** Sets the bottom right quadrant **/
        void bottom_right( node_type n ) {
            if( __quadrant(BOTTOM_RIGHT) ) delete __quadrant(BOTTOM_RIGHT) ;
            __quadrant(BOTTOM_RIGHT) = n ;
        }

        /** Returns the number of elements in this node **/
        size_type size() const {
            return __index ;
        }

        /** Returns the i'th element of the data **/
        value_type data( size_type i ) {
            return __data[i] ;
        }

        /**
        * Adds an item to the data container at the back
        */
        void add( value_type t ) {
            __data(__index++) = t ;
        }

        /** Returns the parent node **/
        node_type parent() {
            return __parent ;
        }

        /** Sets the parent node **/
        void parent( self_type* p ) {
            __parent = p ;
        }
        
        /**
         * Creates the children nodes from the parent node by
         * evenly dividing the parent into four new quadrants.
         *
         * @param size      max size of the data container
         */
        void create_children( size_type size ) {
            coord_type nw = 0.5*__width, nh = 0.5*__height ;
                // Top left quadrant
            __quadrant(TOP_LEFT) = new self_type(__x,__y+nh,nw,nh,size) ;
            __quadrant(TOP_LEFT)->__parent = this ;
                // Bottom left quadrant
            __quadrant(BOTTOM_LEFT) = new self_type(__x,__y,nw,nh,size) ;
            __quadrant(BOTTOM_LEFT)->__parent = this ;
                // Top right quadrant
            __quadrant(TOP_RIGHT) = new self_type(__x+nw,__y+nh,nw,nh,size) ;
            __quadrant(TOP_RIGHT)->__parent = this ;
                // Bottom right quadrant
            __quadrant(BOTTOM_RIGHT) = new self_type(__x+nw,__y,nw,nh,size) ;
            __quadrant(BOTTOM_RIGHT)->__parent = this ;
        }

        /**
         * Quadrant information
         * (x,y) represents the lower left corner of the
         * quadrant and the width/height give the extent
         * in the x/y directions, respectively. These remain
         * public to allow for easy access during computations.
         */
        coord_type __x ;
        coord_type __y ;
        coord_type __width ;
        coord_type __height ;

    private:

        /**
         * List of the quadrant nodes.
         */
        container_type __quadrant ;

        /**
         * Container of all the data that is stored
         * in this quad.
         */
        data_container __data ;

        /**
         * Current index value and size of the array.
         */
        size_type __index ;

        /**
         * Pointer to the parent node
         */
        self_type* __parent ;
};

/**
 * Quadtree class implementation
 */
template<class C, class S, class B, class T, std::size_t N>
class quadtree {
    
    public:
        
        typedef T                   value_type ;
        typedef value_type*         value_ptr ;
        typedef value_ptr           iterator ;
        typedef value_type          value_ref ;
        typedef std::size_t         size_type ;
        typedef quad<value_type>    node_type ;
        typedef node_type*          node_ptr ;
        typedef C                   criteria_functor ;
        typedef B                   bound_functor ;
        typedef S                   split_functor ;
        typedef quadtree<criteria_functor,split_functor,
                         bound_functor,value_type,N>         self_type ;
        typedef typename T::coord_type       coord_type ;
                    
        /**
         * Constructor
         */
        quadtree( coord_type x, coord_type y,
                  coord_type width, coord_type height )
        {
            __root = new node_type( x, y, width, height, __size ) ;
            __root->parent( NULL ) ;
        }
        
        /**
         * Destructor
         */
        virtual ~quadtree() {
            destroy_tree( __root ) ;
        }
        
        /**
         * Inserts an element into the quadtree.
         * If the node meets the criteria for splitting
         * the node is split into its children nodes.
         */
        void insert( value_type item ) {
            node_ptr n = find_node( __root, item ) ;
            insert( n, item ) ;
        }
        
        template<class Box, class List>
        void query( const Box b, List* l ) {
            construct_list( __root, b, l ) ;
        }
        
        /**
         * Test funciton -- Not permanent
         */
        void print() {
            std::cout << "ROOT"
                      << " x[" << __root->__x << " " << __root->__x+__root->__width << "]"
                      << " y[" << __root->__y << " " << __root->__y+__root->__height << "]"
                      << std::endl ;
            print( __root ) ;
        }
    
    protected:
    
        /**
         * Recrusive engine for inserting an element into the quadtree
         * and splitting quadrants
         */
        void insert( node_ptr n, value_type item ) {
            if( criteria_functor::check( n ) ) {
                node_ptr tmp = split_functor::apply( n ) ;
                if( n == __root ) {
                    __root = tmp ;
                    delete n ;
                } else {
                    if( n == n->parent()->top_left() ) {
                        n->parent()->top_left( tmp ) ;
                    } else if( n == n->parent()->top_right() ) {
                        n->parent()->top_right( tmp ) ;
                    } else if( n == n->parent()->bottom_left() ) {
                        n->parent()->bottom_left( tmp ) ;
                    } else {
                        n->parent()->bottom_right( tmp ) ;
                    }
                }
                n = find_node( tmp, item ) ;
                insert( n, item ) ;
            } else {
                n->add(item) ;
            }
        }
    
        /**
         * Test function
         */
        void print( node_ptr n ) {
            size_type size( n->size() ) ;
            if( n != __root ) {
                std::cout << "\tNEXT LEVEL"
                << " x[" << n->__x << " " << n->__x+n->__width << "]"
                << " y[" << n->__y << " " << n->__y+n->__height << "]"
                << std::endl ;
            }
            for(size_type i=0; i<size; ++i) {
                std::cout << n->data(i) << std::endl ;
            }
            if( n->top_left() ) {
                std::cout << "TOP_LEFT:" << std::endl ;
                print( n->top_left() ) ;
            }
            if( n->top_right() ) {
                std::cout << "TOP_RIGHT:" << std::endl ;
                print( n->top_right() ) ;
            }
            if( n->bottom_left() ) {
                std::cout << "BOTTOM_LEFT:" << std::endl ;
                print( n->bottom_left() ) ;
            }
            if( n->bottom_right() ) {
                std::cout << "BOTTOM_RIGHT:" << std::endl ;
                print( n->bottom_right() ) ;
            }
        }
        
        /**
         * Constructs the list for a queried region
         */
        template<class Box, class List>
        void construct_list( node_ptr n, const Box b, List* l ) {
            if( (b.x <= n->__x) && (b.y <= n->__y) &&
                ((n->__x+n->__width) <= (b.x+b.width)) &&
                ((n->__y+n->__height) <= (b.y+b.height)) )
            {
                add_sector( n, l ) ;
            } else {
                if( intersect(Box(n), b) ) {
                    size_type size( n->size() ) ;
                    for(size_type i=0; i<size; ++i) {
                        // Only add the data if it is actually in the box
                        if( b.x <= n->data(i).x && n->data(i).x <= (b.x+b.width) ) {
                            if( b.y <= n->data(i).y && n->data(i).y <= (b.y+b.height) ) {
                                l->push_back( n->data(i) ) ;
                            }
                        }
                    }
                    if( n->top_left() && intersect( Box(n->top_left()), b ) )
                        construct_list( n->top_left(), b, l ) ;
                    if( n->bottom_left() && intersect( Box(n->bottom_left()), b ) )
                        construct_list( n->bottom_left(), b, l ) ;
                    if( n->top_right() && intersect( Box(n->top_right()), b ) )
                        construct_list( n->top_right(), b, l ) ;
                    if( n->bottom_right() && intersect( Box(n->bottom_right()), b ) )
                        construct_list( n->bottom_right(), b, l ) ;
                }
            }
        }
        
        /**
         * Checks that either box is contained within the other
         */
        template<class Box>
        bool intersect( const Box& b1, const Box& b2 ) {
            return ( corners(b1,b2) || corners(b2,b1) ) ;
        }
        
        /**
         * Determines if any of the four corners from box 1
         * are within box 2. This check implies that box 2
         * intersects box 1.
         */
        template<class Box>
        bool corners( const Box b1, const Box b2 ) {
            bool lower_x = (b2.x <= b1.x) && (b1.x < (b2.x+b2.width)) ;
            bool lower_y = (b2.y <= b1.y) && (b1.y < (b2.y+b2.height)) ;
            // Is the SW corner of the node in the box?
            if( lower_x && lower_y ) return true ;
            bool upper_x = (b2.x < (b1.x+b1.width)) && ((b1.x+b1.width) < (b2.x+b2.width)) ;
            // Is the SE corner of the node in the box?
            if( upper_x && lower_y ) return true ;
            bool upper_y = (b2.y < (b1.y+b1.height)) && ((b1.y+b1.height) < (b2.y+b2.height)) ;
            // Is the NW corner of the node in the box?
            if( lower_x && upper_y ) return true ;
            // Is the NE corner of the node in the box?
            if( upper_x && upper_y ) return true ;
            // None of the node's corners are in the box, so this node doesn't intersect the box
            return false ;
        }

        /**
         * Adds an entire sector of elements to the list because
         * this region of the quadtree is entirely contained within
         * the query box and so every element must be added.
         */
        template<class List>
        void add_sector( node_ptr n, List* l ) {
            size_type size( n->size() ) ;
            for(size_type i=0; i<size; ++i) {
                l->push_back( n->data(i) ) ;
            }
            if( n->top_left() ) add_sector( n->top_left(), l ) ;
            if( n->bottom_left() ) add_sector( n->bottom_left(), l ) ;
            if( n->top_right() ) add_sector( n->top_right(), l ) ;
            if( n->bottom_right() ) add_sector( n->bottom_right(), l ) ;
        }

        /**
         * Recursively searches the quadtree for the smallest
         * quad that fully contains this item.
         */
        node_ptr find_node( node_ptr node, value_type item ) {
            bool left = bound_functor::left( node, item ) ;
            bool right = bound_functor::right( node, item ) ;
            bool top = bound_functor::top( node, item ) ;
            bool bottom = bound_functor::bottom( node, item ) ;
            node_ptr result = node ;
            if( (left || right) && (top || bottom) ) {
                if( left ) {
                    if( top ) {
                        if( node->top_left() ) {
                            result = find_node( node->top_left(), item ) ;
                        }
                    } else {
                        if( node->bottom_left() ) {
                            result = find_node( node->bottom_left(), item ) ;
                        }
                    }
                } else {
                    if( top ) {
                        if( node->top_right() ) {
                            result = find_node( node->top_right(), item ) ;
                        }
                    } else {
                        if( node->bottom_right() ) {
                            result = find_node( node->bottom_right(), item ) ;
                        }
                    }
                }
            }
            return result ;
        }
    
    private:
    
        /**
         * The root node of the quadtree
         */
        node_ptr __root ;
        
        static const size_type __size = N ;
    
        /**
         * Deletes all nodes and elements of the tree.
         */
        void destroy_tree( node_ptr node ) {
             // Check for a TOP_RIGHT child
            if( node->top_right() )
                destroy_tree( node->top_right() ) ;
            // Check for a TOP_LEFT child
            if( node->top_left() )
                destroy_tree( node->top_left() ) ;
            // Check for a BOTTOM_LEFT child
            if( node->bottom_left() )
                destroy_tree( node->bottom_left() ) ;
            // Check for a BOTTOM_RIGHT child
            if( node->bottom_right() )
                destroy_tree( node->bottom_right() ) ;
            delete node ;
        }
};

/** Specialized Quadtree that stores points **/
template<class T, std::size_t N>
struct quadtree_type {
    typedef quadtree<max_count<T,N>, split_points<bound_box<T>,T>,bound_box<T>,T,N> points ;
};
    
}   // end of namespace tree
}   // end of namespace genecis
