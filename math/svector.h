/**
 * @file svector.h
 */
 
#ifndef MATH_SVECTOR_H
#define MATH_SVECTOR_H

#include "math_vector.h"

class svector : public math_vector {
		
	public:
	
		/**
		 * Returns the inner product of two svectors
		 *
		 *  dot product =
		 *		rho1*rho2 ( cos(theta1)cos(theta2) +
		 *		sin(theta1)sin(theta2)cos(phi1-phi2) )
		 */
		virtual inline double dot(const math_vector& other) const {
			double result = ( _u1 * other.u1() * ( 
				cos(_u2) * cos(other.u2()) +
				sin(_u2) * sin(other.u2()) *
				cos(_u3 - other.u3()) ) ) ;
			return result ;
		}
				
		/**
		 * Constructors a vector in spherical coordinates.
		 *
		 * @param rho		rho component
		 * @param theta		theta component
		 * @param phi		phi component
		 * @param rad		defaults to not needing conversion
		 */
		svector(double rho, double theta, double phi, bool rad=false) {
			if(rad) {
				_u1 = rho ;
				_u2 = theta * M_PI / 180.0 ;
				_u3 = phi * M_PI / 180.0 ;
			} else {
				_u1 = rho ;
				_u2 = theta ;
				_u3 = phi ;
			}
		}
		
		// Destructor
		virtual ~svector() {}
		
		friend std::ostream& operator<< (std::ostream& os, const svector& other) ;

};

// std::output override for svector
inline std::ostream& operator<< (std::ostream& os, const svector& other) {
	os << "(rho,theta,phi): ("
	   << other.u1() << ", "
	   << other.u2() << ", "
	   << other.u3() << ")" ;
	return os ;
};

#endif
