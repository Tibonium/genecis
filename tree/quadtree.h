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
            typedef array<self_type*>                      container_type ;
            typedef array<T>                               data_container ;
            typedef typename container_type::iterator      iterator ;
            typedef typename container_type::pointer       pointer ;
            typedef typename container_type::size_type     size_type ;
            typedef typename container_type::value_type    node_type ;

            /**
             * Default constructor
             *
             * Initializes the quadrant container elements
             * all to NULL.
             */
            quad()
            : __x(0), __y(0), __width(100), __height(100), __index(0) 
            {
                __quadrant = container_type(4) ;
                for(size_type i=0; i<4; ++i) {
                    __quadrant(i) = NULL ;
                }
                __data = data_container(0) ;
            }

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
                __quadrant = container_type(4) ;
                for(size_type i=0; i<4; ++i) {
                    __quadrant(i) = NULL ;
                }
                __data = data_container(num) ;
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
                __quadrant(TOP_RIGHT) = n ;
             }
             
             /** Returns the top left quadrant **/
             node_type top_left() const {
                return __quadrant(TOP_LEFT) ;
             }

             /** Sets the top left quadrant **/
             void top_left( node_type n ) {
                __quadrant(TOP_LEFT) = n ;
             }

            /** Returns the bottom left quadrant **/
            node_type bottom_left() const {
                return __quadrant(BOTTOM_LEFT) ;
            }

             /** Sets the bottom left quadrant **/
             void bottom_left( node_type n ) {
                __quadrant(BOTTOM_LEFT) = n ;
             }

            /** Returns the bottom right quadrant **/
            node_type bottom_right() const {
                return __quadrant(BOTTOM_RIGHT) ;
            }

             /** Sets the bottom right quadrant **/
             void bottom_right( node_type n ) {
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
                node_ptr tmp = find_node( __root, item ) ;
                tmp->add( item ) ;
                if( criteria_functor::check( tmp ) ) {
                    split_functor::apply( tmp ) ;
                }
            }
            
            /**
             * Test funciton -- Not permanent
             */
            void print_tree() {
                print( __root ) ;
            }
        
        protected:
        
            /**
             * Test function
             */
            void print( node_ptr n ) {
                size_type size( n->size() ) ;
                for(size_type i=0; i<size; ++i) {
                    std::cout << "(" << n->data(i).x << ", " << n->data(i).y << ")" << std::endl ;
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
             * Recursively searchs the quadtree for the smallest
             * quad that fully contains this item.
             */
            node_ptr find_node( node_ptr node, value_type item ) {
                bool left = bound_functor::left( node, item ) ;
                bool top = bound_functor::top( node, item ) ;
                if( left ) {
                    if( top ) {
                        if( node->top_left() ) {
                            find_node( node->top_left(), item ) ;
                        }
                    } else {
                        if( node->bottom_left() ) {
                            find_node( node->bottom_left(), item ) ;
                        }
                    }
                } else {
                    if( top ) {
                        if( node->top_right() ) {
                            find_node( node->top_right(), item ) ;
                        }
                    } else {
                        if( node->bottom_right() ) {
                            find_node( node->bottom_right(), item ) ;
                        }
                    }
                }
                return node ;
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
