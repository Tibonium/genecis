/**
 * @file svector.h
 */
 
#ifndef GENECIS_MATH_SVECTOR_H
#define GENECIS_MATH_SVECTOR_H

#include "math_vector.h"
#define pi2 2.0*M_PI
#define pi M_PI

class svector : public math_vector<double> {
		
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
		 *	Adds two spherical vectors together and returns a new
		 *	svector that is the sum of the two.
		 */
		inline svector* operator+ (const svector& rhs) {
				// Convert both vectors to cartesian
			double x1 = _u1*sin(_u2)*cos(_u3) ;
			double x2 = rhs._u1*sin(rhs._u2)*cos(rhs._u3) ;
			double y1 = _u1*sin(_u2)*sin(_u3) ;
			double y2 = rhs._u1*sin(rhs._u2)*sin(rhs._u3) ;
			double z1 = _u1*cos(_u2) ;
			double z2 = rhs._u1*cos(rhs._u2) ;
				// Add both vectors after converting
			double x_12 = x1+x2 ;
			double y_12 = y1+y2 ;
			double z_12 = z1+z2 ;
			double x_sqr = x_12*x_12 ;
			double y_sqr = y_12*y_12 ;
			double z_sqr = z_12*z_12 ;
				// Convert back into spherical coordinates
			double _r = sqrt( x_sqr + y_sqr + z_sqr ) ;
			double _t = atan( sqrt( x_sqr + y_sqr ) / z_12 ) ;
			double _p = atan( y_12 / x_12 ) ;
			svector* s = new svector(_r,_t,_p) ;
			return s ;
		}
		
		inline svector* operator- (const svector& rhs) {
			return (*this) + svector(-rhs.u1(),-rhs.u2(),-rhs.u3()) ;
		}
		
		/**
		 * Returns the cross product of two svectors by converting
		 * to Cartesian, calculating the determinate and then
		 * converting back to spherical
		 *
		 *  Cross product =
		 *			| i   j   k  |
		 *		det	| u1  u2  u3 |   =
		 *			| v1  v2  v3 |
		 * 
		 *  (u2*v3-u3*v2) i - (u1*v3-u3*v1) j + (u1*v2-u2*v1) k
		 */
		inline svector* cross(const svector& rhs) const {
				// Convert both vectors to cartesian
			double x1 = _u1*sin(_u2)*cos(_u3) ;
			double x2 = rhs._u1*sin(rhs._u2)*cos(rhs._u3) ;
			double y1 = _u1*sin(_u2)*sin(_u3) ;
			double y2 = rhs._u1*sin(rhs._u2)*sin(rhs._u3) ;
			double z1 = _u1*cos(_u2) ;
			double z2 = rhs._u1*cos(rhs._u2) ;
				// Take the cross product
			double _x = y1 * z2 - z1 * y2 ;
			double _y = z1 * x2 - x1 * z2 ;
			double _z = x1 * y2 - y1 * x2 ;
				// Guard against small erronous values that should be zero
			if( abs(_x) < 1e-10 ) _x = 0 ;
			if( abs(_y) < 1e-10 ) _y = 0 ;
			if( abs(_z) < 1e-10 ) _z = 0 ;
			double x_sqr = _x*_x ;
			double y_sqr = _y*_y ;
			double z_sqr = _z*_z ;
				// Convert back into spherical coordinates
			double _r = sqrt( x_sqr + y_sqr + z_sqr ) ;
			double _t = acos( _z / _r ) ;
			double _p ;
				// Guard against dividing by zero
			if( _x <= 1e-10 ) {
				_p = 0.0 ;
			} else {
				_p = atan( _y / _x ) ;
			}
			svector* s = new svector(_r,_t,_p) ;
			return s ;
		}
		
		void operator* (const double& c) {
			_u1 *= c ;
		}
		
		void operator/ (const double& c) {
			_u1 /= c ;
		}
		
		/**
		 * A function that turns the vector r to -r in spherical
		 * coordinates. The process rotates the vector in theta
		 * and phi by pi. To keep the values of phi between zero
		 * and two pi, fmod is used.
		 */
		void negate() {
			u2 = pi - _u2 ;
			u3 = fmod( _u3+pi, pi2 ) ;
			svector* s = new svector(_u1,u2,u3) ;
			return s ;
		}
				
		/**
		 * Constructors a vector in spherical coordinates.
		 *
		 * @param rho		rho component
		 * @param theta	    theta component
		 * @param phi		phi component
		 * @param rad		defaults to not needing conversion
		 */
		svector(double rho=0.0, double theta=0.0,
			   double phi=0.0, bool rad=false) {
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
	os << "(rho,theta,phi): ["
	   << other.u1() << ", "
	   << other.u2() << ", "
	   << other.u3() << "]" ;
	return os ;
};

#endif
