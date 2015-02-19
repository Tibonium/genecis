/**
 * @file quadtree_functors.h
 */

#pragma once

namespace genecis {
namespace tree {

    /** Forward decleration of the quad class **/
    template<class T> class quad ;

    template<class T, int N>
    struct max_count {
        typedef quad<T>*  argument_type ;
        typedef bool      result_type ;
        
        static result_type check( argument_type a ) {
            return (a->size() >= N) ;
        }
    };
    
    template<class B, class I>
    struct split_points {
        typedef I               item_type ;
        typedef quad<item_type> node_type ;
        typedef node_type*      argument_type ;
        typedef std::size_t     size_type ;
        typedef B               bound_functor ;
        
        static void apply( argument_type a ) {
            argument_type old_node = a ;
            argument_type new_node = new node_type ;
            // split the elemnts into each node
            size_type size( a->size() ) ;
            for(size_type i=0; i<size; ++i) {
                item_type curr = a->data(i) ;
                bool left = bound_functor::left( a, curr ) ;
                bool top = bound_functor::top( a, curr ) ;
                if( left ) {
                    if( top ) {
                        if( new_node->top_left() ) {
                            new_node->top_left()->add( curr ) ;
                        } else {
                            new_node->top_left( new node_type ) ;
                            new_node->top_left()->add( curr ) ;                            
                        }
                    } else {
                        if( new_node->bottom_left() ) {
                            new_node->bottom_left()->add( curr ) ;
                        } else {
                            new_node->bottom_left( new node_type ) ;
                            new_node->bottom_left()->add( curr ) ;                            
                        }
                    }
                } else {
                    if( top ) {
                        if( new_node->top_right() ) {
                            new_node->top_right()->add( curr ) ;
                        } else {
                            new_node->top_right( new node_type ) ;
                            new_node->top_right()->add( curr ) ;                            
                        }
                    } else {
                        if( new_node->bottom_right() ) {
                            new_node->bottom_right()->add( curr ) ;
                        } else {
                            new_node->bottom_right( new node_type ) ;
                            new_node->bottom_right()->add( curr ) ;                            
                        }   // end if/else -> bottom_right
                    }   // end if/else -> top
                }   // end if/else -> left
            }   // end for in i
            a = new_node ;
            delete old_node ;
        }   // end function apply
    };
    
    template<class I>
    struct bound_box {
        typedef quad<I>*     bounding_node ;
        typedef I           item_type ;
        typedef bool        result_type ;
        
        static result_type left( bounding_node n,
                                 item_type item )
        {
            return ( item.x > (n->__x + 0.5 * n->__width) ) ;
        }
        
        static result_type top( bounding_node n,
                                item_type item )
        {
            return (  item.y > (n->__y + 0.5 * n->__height)  ) ;
        }
    };

}   // end of namespace tree
}   // end of namespace genecis
