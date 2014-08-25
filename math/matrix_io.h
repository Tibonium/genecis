/**
 * @file matrix_io.h
 */
 
#ifndef GENECIS_MATH_MATRIX_IO_H
#define GENECIS_MATH_MATRIX_IO_H

#include <cstdio>
#include <iosfwd>
#include <sstream>
#include <typeinfo>
#include <genecis/math/matrix_expression.h>

namespace genecis {
namespace math {

	template<class M>
	std::ostream& operator<< (std::ostream& os, const matrix_expression<M>& m)
	{
		typedef M							expression_type ;
		typedef typename M::size_type		size_type ;
		typedef typename M::value_type		value_type ;
		typedef typename M::container_type	container_type ;

		expression_type e = m() ;
		size_type rows = e.rows() ;
		size_type cols = e.cols() ;
		
		std::stringstream s ;	
		s << "\nrows: " << rows << "   det:   " << e.det() 
		  << "\ncols: " << cols ;
		os << s.str().c_str() ;
		s.clear() ;
		s.str(std::string()) ;
		if( e.singular() ) {
			s << "   singular" << endl ;
		} else {
			s << "   non-singular" << endl ;
		}
		os << s.str().c_str() ;
		s.clear() ;
		s.str(std::string()) ;	
		for(size_type i=0; i<rows; ++i) {
			s << "| " ;
			for(size_type j=0; j<cols; ++j) {
				char buf[32];
		        value_type data = e(i,j) ;
		        if( typeid(value_type) == typeid(int) ) {
		        	if( data >= 1e5 ) {
		        		sprintf(buf, "%1.1e ", (double)data) ;
		        	} else {
		    			sprintf(buf, "%7d ", (int)data) ;
		    		}
		        } else {
		        	if( (abs(data) >= 1e10) || (abs(data) <= 1e-4) ) {
		        		if( abs(data) <= 1e-40 ) {
		        			sprintf(buf, "%10.0f ", (double)data) ;
		        		} else {
		        			sprintf(buf, "%10.3e ", (double)data) ;
		        		}
		        	} else {
		    			sprintf(buf, "%10.3f ", (double)data) ;
		    		}
		        }
		        s <<  buf ;
			}
			s << " |" << endl ;
		}
		os << s.str().c_str() ;
		s.clear() ;
		s.str(std::string()) ;
		return os ;
	}

}	// end of namespace math
}	// end of namespace genecis
#endif
