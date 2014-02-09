/**
 * @file cvector.h
 */
 
#ifndef MATH_CVECTOR_H
#define MATH_CVECTOR_H

#include "math_vector.h"

class cvector : public math_vector<double> {

	public:
	
		/**
		 * Returns the inner product of two cvectors
		 *
		 *  dot product =
		 *		r1*cos(p1) * r2*cos(p2) +
		 *		r1*sin(p1) * r2*sin(p2) +
		 *		z1 * z2
		 */
		virtual inline double dot(const math_vector& other) const {
			double result = (
				_u1 * cos(_u2) * other.u1() * cos(other.u2()) + 
				_u1 * sin(_u2) * other.u2() * sin(other.u2()) +
				_u3 * other.u3() ) ;
			return result ;
		}
				
		/**
		 * Constructor for a vector in cylindrical coordinates
		 *
		 * @param rho	rho component
		 * @param phi	phi component
		 * @param z		z component
		 * @param rad	defaults to not needing conversion done
		 */
		cvector(double rho=0.0, double phi=0.0,
			   double z=0.0, bool rad=false) {
			if(rad) {
				_u1 = rho ;
				_u2 = phi * M_PI / 180.0 ;
				_u3 = z ;
			} else {
			_u1 = rho ;
			_u2 = phi ;
			_u3 = z ;
			}
		}
		
		// Destructor
		virtual ~cvector() {}
				
		friend std::ostream& operator<< (std::ostream& os, const cvector& other) ;

};

// std::output override for cvector
inline std::ostream& operator<< (std::ostream& os, const cvector& other) {
	os << "(rho,phi,z): ("
	   << other.u1() << ", "
	   << other.u2() << ", "
	   << other.u3() << ")" ;
	return os ;
};

#endif
