/**
 * @file arc_pair_compare.h
 */

#ifndef GENECIS_MATH_ARC_PAIR_COMPARE_H
#define GENECIS_MATH_ARC_PAIR_COMPARE_H

#include "arc_pair.h"

namespace genecis {
namespace math {
 
struct compareFirstVertex : public std::binary_function<arc_pair,arc_pair,bool>
{

	inline bool operator() ( const arc_pair& lhs, const arc_pair& rhs ) {
		return ( lhs.first_node() < rhs.first_node() ) ;
	}

};

struct compareSecondVertex : public std::binary_function<arc_pair,arc_pair,bool>
{

	inline bool operator() ( const arc_pair& lhs, const arc_pair& rhs ) {
		return ( lhs.second_node() < rhs.second_node() ) ;
	}

};

}	// end of namespace math
}	// end of namespace genecis
#endif
