/**
 * @file quadtree.h
 */

#pragma once

#include <genecis/container/array.h>

using genecis::container::array ;

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
            typedef typename container_type::iterator      iterator ;
            typedef typename container_type::pointer       pointer ;
            typedef typename container_type::size_type     size_type ;
            typedef enum { PARENT, LEAF }                  node_type ;
            
            /**
             * Constructor
             *
             * Initializes the quadrant container elements
             * all to NULL.
             */
            quad() {
                _quadrant = container_type(4) ;
                for(size_type i=0; i<4; ++i) {
                    _quadrant(i) = NULL ;
                    _type = LEAF ;
                }
            }
            
            /**
             * Destructor
             */
            virtual ~quad() {}
        
        protected:
        
        private:
        
            /**
             * List of the quadrant nodes.
             */
            container_type _quadrant ;
            
            /**
             * Type of node this is.
             *
             * PARENT - has non-NULL children
             * LEAF   - all children all NULL
             */
            node_type _type ;
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
            
            /**
             * Constructor
             */
            quadtree() {
            
            }
            
            /**
             * Destructor
             */
            virtual ~quadtree() {
                destroy_tree() ;
            }
        
        protected:
        
        private:
        
            /**
             * The root node of the quadtree
             */
            node_type _root ;
        
            /**
             * Deletes all nodes and elements of the tree.
             */
            void destroy_tree() {
                
            }
    };
    
}   // end of namespace tree
}   // end of namespace genecis
