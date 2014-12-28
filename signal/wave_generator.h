/**
 * wave_generator.h
 */
 
#pragma once

#include <genecis/container/array.h>

using namespace genecis::container ;

namespace genecis {
namespace signal {

	class wave_generator {
	
		typedef std::size_t			size_type ;
		typedef double				value_type ;
		typedef array<value_type>	array_type ;
	
		public:
		
			template<class C>
			static C* square_wave( const size_type& size, const size_type& duration,
							   const typename C::value_type& amplitude )
			{
				C* data = new C( size ) ;
				size_type offset = floor((size - duration) / 2.0) ;
				std::fill_n( (data->begin()+offset), duration, amplitude ) ;
				return data ;
			}
	
	};

} // end of namespace signal
} // end of namespace genecis
