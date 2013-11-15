/**
 * @file bvector.h
 */
 
#ifndef MATH_BVECTOR_H
#define MATH_BVECTOR_H

#include "math_vector.h"

class bvector : public math_vector {

	public:
	
		/**
		 * Returns the inner product of two bvectors
		 *
		 *  dot product =
		 *		x*x + y*y + z*z
		 */
		virtual inline double dot(const math_vector& other) const {
			double result = _u1 * other.u1() + 
							_u2 * other.u2() +
							_u3 * other.u3() ;
			return result ;
		}
						
		/**
		 * Constructor for a vector in cartesian coordinates
		 *
		 * @param x 	x component
		 * @param y 	y component
		 * @param z 	z component
		 */
		bvector(double x, double y, double z) {
			_u1 = x ;
			_u2 = y ;
			_u3 = z ;
		}
		
		// Destructor
		virtual ~bvector() {}

		friend std::ostream& operator<< (std::ostream& os, const bvector& other) ;

};

// std::output override for bvector
inline std::ostream& operator<< (std::ostream& os, const bvector& other) {
	os << "(x,y,z): ("
	   << other.u1() << ", "
	   << other.u2() << ", "
	   << other.u3() << ")" ;
	return os ;
};

#endif
