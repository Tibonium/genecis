/**
 * @file svector.h
 */
 
#ifndef GENECIS_MATH_SVECTOR
#define GENECIS_MATH_SVECTOR

#include "vector_io.h"

namespace genecis {
namespace math {

	template<typename T>
	class svector : public vector_expression<svector, T> {
		
		public:
		
			typedef T			value_type ;

			/**
			 * Constructors a vector in spherical coordinates.
			 *
			 * @param rho		rho component
			 * @param theta	    theta component
			 * @param phi		phi component
			 * @param rad		defaults to not needing conversion
			 */
			svector(value_type rho=0.0, value_type theta=0.0,
				    value_type phi=0.0, bool rad=false)
			{
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
	
			/**
			 * Returns the inner product of two svectors
			 *
			 *  dot product =
			 *		rho1*rho2 ( cos(theta1)cos(theta2) +
			 *		sin(theta1)sin(theta2)cos(phi1-phi2) )
			 */
			value_type dot(const svector& other) const {
				value_type result = ( _u1 * other.u1() * ( 
					cos(_u2) * cos(other.u2()) +
					sin(_u2) * sin(other.u2()) *
					cos(_u3 - other.u3()) ) ) ;
				return result ;
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
			svector cross(const svector& v) {
					// Convert both vectors to cartesian
				value_type x1 ; value_type y1 ; value_type z1 ;
				value_type x2 ; value_type y2 ; value_type z2 ;
				ToCartesianFromSpherical( _u1, _u2, _u3, x1, y1, z1 ) ;
				ToCartesianFromSpherical( v._u1, v._u2, v._u3, x2, y2, z2 ) ;
					// Take the cross product
				value_type _x = y1 * z2 - z1 * y2 ;
				value_type _y = z1 * x2 - x1 * z2 ;
				value_type _z = x1 * y2 - y1 * x2 ;
					// Guard against small erronous values that should be zero
				if( abs(_x) < 1e-10 ) _x = 0 ;
				if( abs(_y) < 1e-10 ) _y = 0 ;
				if( abs(_z) < 1e-10 ) _z = 0 ;
					// Convert back into spherical coordinates
				value_type _r ; value_type _t ; value_type _p ;
				ToSphericalFromCartesian( _x, _y, _z, _r, _t, _p ) ;
				return svector(_r,_t,_p) ;
			}

			/**
			 *	Adds two spherical vectors together and returns a new
			 *	svector that is the sum of the two.
			 */
			svector operator+ (const svector& rhs) {
					// Convert both vectors to cartesian
				value_type x1 ; value_type y1 ; value_type z1 ;
				value_type x2 ; value_type y2 ; value_type z2 ;
				ToCartesianFromSpherical( _u1, _u2, _u3, x1, y1, z1 ) ;
				ToCartesianFromSpherical( rhs._u1, rhs._u2, rhs._u3 , x2, y2, z2 ) ;
					// Add both vectors after converting
				value_type x_12 = x1+x2 ;
				value_type y_12 = y1+y2 ;
				value_type z_12 = z1+z2 ;
					// Convert back into spherical coordinates
				value_type _r ; value_type _t ; value_type _p ;
				ToSphericalFromCartesian( x_12, y_12, z_12, _r, _t, _p ) ;
				return svector(_r,_t,_p) ;
			}

			/**
			 * Subtracts two svectors
			 */
			svector operator- (const svector& rhs) {
				return operator+(rhs.negate()) ;
			}
			
			/** ========= Scalar operations ========= **/
			/**
			 * Adds a scalar vector to an svector
			 */
			svector operator+ (const value_type& c) {
				return operator+(svector(c,0,0)) ;
			}

			/**
			 * Subtracts a scalar vector to an svector
			 */
			svector operator- (const value_type& c) {
				return operator+(-c) ;
			}
			
			/**
			 * Multiples an svector by a scalar
			 */
			svector operator* (const value_type& c) {
				return svector(_u1*c,_u2,_u3) ;
			}
		
			/**
			 * Divides an svector by a scalar
			 */
			svector operator/ (const value_type& c) {
				return operator*(1.0/c) ;
			}
		
			/**
			 * A function that turns the vector r to -r in spherical
			 * coordinates. The process rotates the vector in theta
			 * and phi by pi. To keep the values of phi between zero
			 * and two pi, fmod is used.
			 */
			svector negate() const {
				value_type u2 = pi - _u2 ;
				value_type u3 = fmod( _u3+pi, pi2 ) ;
				return svector(_u1,u2,u3) ;
			}
		
			/**
			 * Functions for accessing and modifying the first component
			 */
			value_type u1() const {
				return _u1 ;
			}

			void u1(value_type _t) {
				_u1 = _t ;
			}
		
			/**
			 * Functions for accessing and modifying the second component
			 */
			value_type u2() const {
				return _u2 ;
			}
		
			void u2(value_type _t) {
				_u2 = _t ;
			}
		
		
			/**
			 * Functions for accessing and modifying the third component
			 */
			value_type u3() const {
				return _u3 ;
			}
		
			void u3(value_type _t) {
				_u3 = _t ;
			}

		protected:
		
			value_type _u1 ;
			value_type _u2 ;
			value_type _u3 ;

	};

}	// end of namespace math
}	// end of namespace genecis

#endif
