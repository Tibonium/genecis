/**
 * @file
 */
 
#pragma once

namespace genecis {
namespace math {

	class numerics {
	
		typedef double		value_type ;
		
		public:
		
			static value_type
			permutation( const value_type& n,
					   cosnt value_type& k ) ;
			
			static value_type
			combination( const value_type& n,
					   const value_type& k ) ;
	};

}	// end of namespace math
}	// end of namespace genecis
