/**
 * @file numerics.h
 */
 
#pragma once

#include <cmath>

using namespace std ;

namespace genecis {
namespace math {

	class numerics {
	
		public:

    		typedef double		value_type ;
		
			static value_type
			permutation( const value_type& n,
					   const value_type& k ) ;
			
			static value_type
			combination( const value_type& n,
					   const value_type& k ) ;
					   
		    static value_type
		    stirling_approx( const value_type& N ) ;
		    
		    static value_type
		    factorial( const value_type& n ) ;
	};

}	// end of namespace math
}	// end of namespace genecis
