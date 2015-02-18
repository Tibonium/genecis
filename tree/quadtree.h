/**
 * @file quadtree.h
 */

#pragma once

#include <genecis/container/array.h>
#include <genecis/container/dynamic_array.h>

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
            typedef value_type*                            value_ptr ;
            typedef quad<value_type>                       self_type ;
            typedef array<self_type*>                      container_type ;
            typedef dynamic_array<T>                       value_container ;
            typedef typename container_type::iterator      iterator ;
            typedef typename container_type::pointer       pointer ;
            typedef typename container_type::size_type     size_type ;
            
            /**
             * Constructor
             *
             * Initializes the quadrant container elements
             * all to NULL.
             */
            quad() : _data(0) {
                _quadrant = container_type(4) ;
                for(size_type i=0; i<4; ++i) {
                    _quadrant(i) = NULL ;
                }
            }
            
            /**
             * Destructor
             */
            virtual ~quad() {}
             
             /** Returns the top right quadrant **/
             self_type top_right() const {
                return _quadrant(TOP_RIGHT) ;
             }

            /** Returns the top left quadrant **/
            self_type top_left() const {
                return _quadrant(TOP_LEFT) ;
            }

            /** Returns the bottom left quadrant **/
            self_type bottom_left() const {
                return _quadrant(BOTTOM_LEFT) ;
            }

            /** Returns the bottom right quadrant **/
            self_type bottom_right() const {
                return _quadrant(BOTTOM_RIGHT) ;
            }
            
        protected:
        
        private:
        
            /**
             * List of the quadrant nodes.
             */
            container_type _quadrant ;
            
            /**
             *
             */
            value_container _data ;
    };

/**
 * Quadtree class implementation
 */
    template<class T>
    class quadtree {
        
        public:
            
            typedef quadtree<T>         self_type ;
            typedef T                   value_type ;
            typedef value_type*         value_ptr ;
            typedef value_ptr           iterator ;
            typedef value_type          value_ref ;
            typedef std::size_t         size_type ;
            typedef quad<value_type>    node_type ;
            typedef node_type*          node_ptr ;
            
            /**
             * Constructor
             */
            quadtree() {
                _root = new node_type ;
            }
            
            /**
             * Destructor
             */
            virtual ~quadtree() {
                destroy_tree( _root ) ;
            }
        
        protected:
        
        private:
        
            /**
             * The root node of the quadtree
             */
            node_ptr _root ;
        
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
    
}   // end of namespace tree
}   // end of namespace genecis
