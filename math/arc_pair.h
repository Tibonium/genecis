/**
 * @file arc_pair.h
 */

#ifndef GENECIS_MATH_ARC_PAIR_H
#define GENECIS_MATH_ARC_PAIR_H
 
#include <iostream>

using namespace std ;

namespace genecis {
namespace math {
 
class arc_pair {

	public:
	
		/**
		 * Constructor
		 * creates a null vertex/vertex pair with weight 0
		 */
		arc_pair( int u=0, int v=0, int w=0 ) :
			_u(u), _v(v), _w(w)
		{}
		
		/**
		 * Copy constructor
		 */
		arc_pair( const arc_pair& other ) {
			(*this) = other ;
		}
		
		/**
		 * Creates a clone of the arc_pair.
		 */
		arc_pair* clone() const {
			return new arc_pair( *this ) ;
		}
		
		/**
		 * Destructor
		 */
		~arc_pair() {}
		
		friend ostream& operator<< ( ostream& os, const arc_pair& output ) ;
		
		/** Various operator overloads **/
		
		void operator= ( const arc_pair& rhs ) {
			_u = rhs.first_node() ;
			_v = rhs.second_node() ;
			_w = rhs.weight() ;
		}
		
		/**
		 * Comparison functions, used to sort the arc_pairs
		 */
		bool compareFirstVertex ( const arc_pair& lhs,
								  const arc_pair& rhs )
		{
			return ( lhs._u < rhs._u ) ;
		}
		
		bool compareSecondVertex ( const arc_pair& lhs,
								   const arc_pair& rhs )
		{
			return ( lhs._v < rhs._v ) ;
		}
	
		/**
		 * Getter and Setter for the first vertex
		 */
		int first_node() const {
			return _u ;
		}
		
		void first_node( int u ) {
			_u = u ;
		}

		/**
		 * Getter and Setter for the second vertex
		 */
		int second_node() const {
			return _v ;
		}
		
		void second_node( int v ) {
			_v = v ;
		}
		
		/**
		 * Getter and Setter for the weight between these vertices
		 */
		int weight() const {
			return _w ;
		}
		
		void weight( int w ) {
			_w = w ;
		}

	private:
	
		int _u ;
		int _v ;
		int _w ;

};

ostream& operator<< ( ostream& os, const arc_pair& output ) {
	os << "( "
	   << output.first_node() << " "
	   << output.second_node() << " "
	   << output.weight()
	   << " )" ;
	return os ;
};

}	// end of namespace math
}	// end of namespace genecis
#endif
