/**
 * @file cvector.h
 */
 
#ifndef GENECIS_MATH_CVECTOR
#define GENECIS_MATH_CVECTOR

#include <genecis/math/vector_io.h>

namespace genecis {
namespace math {

	template<typename T>
	class cvector : public vector_expression<cvector, double> {

		public:
		
			typedef T		value_type ;

			/**
			 * Constructor for a vector in cylindrical coordinates
			 *
			 * @param rho	rho component
			 * @param phi	phi component
			 * @param z		z component
			 * @param rad	defaults to not needing conversion done
			 */
			cvector(value_type rho=0.0, value_type phi=0.0,
				    value_type z=0.0, bool rad=false) {
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
				
			/**
			 * Returns the inner product of two cvectors
			 *
			 *  dot product =
			 *		r1*cos(p1) * r2*cos(p2) +
			 *		r1*sin(p1) * r2*sin(p2) +
			 *		z1 * z2
			 */
			value_type dot(const cvector& other) const {
				value_type result = (
					_u1 * cos(_u2) * other.u1() * cos(other.u2()) + 
					_u1 * sin(_u2) * other.u2() * sin(other.u2()) +
					_u3 * other.u3() ) ;
				return result ;
			}

			/**
			 * Returns the cross product of two math_vectors, with
			 * basis vectors that are linearly independent.
			 *
			 *  Cross product =
			 *			| i   j   k  |
			 *		det	| u1  u2  u3 |   =
			 *			| v1  v2  v3 |
			 * 
			 *  (u2*v3-u3*v2) i - (u1*v3-u3*v1) j + (u1*v2-u2*v1) k
			 */
			cvector cross(const cvector& v) const {
					// Convert both vectors to cartesian
				value_type x1 ; value_type y1 ; value_type z1 ;
				value_type x2 ; value_type y2 ; value_type z2 ;
				ToCartesianFromCylindrical( _u1, _u2, _u3, x1, y1, z1 ) ;
				ToCartesianFromCylindrical( v._u1, v._u2, v._u3, x2, y2, z2 ) ;
					// Take the cross product
				value_type _x = y1 * z2 - z1 * y2 ;
				value_type _y = z1 * x2 - x1 * z2 ;
				value_type _z = x1 * y2 - y1 * x2 ;
					// Guard against small erronous values that should be zero
				if( abs(_x) < 1e-10 ) _x = 0 ;
				if( abs(_y) < 1e-10 ) _y = 0 ;
				if( abs(_z) < 1e-10 ) _z = 0 ;
					// Convert back into spherical coordinates
				value_type r ; value_type p ; value_type z ;
				ToCylindricalFromCartesian( _x, _y, _z, r, p, z ) ;
				return cvector(r,p,z) ;
			}

			/**
			 * Adds two cvectors together
			 */
			cvector operator+ (const cvector& rhs) const {
				value_type x1 ; value_type y1 ; value_type z1 ;
				value_type x2 ; value_type y2 ; value_type z2 ;
				ToCartesianFromCylindrical( _u1, _u2, _u3, x1, y1, z1 ) ;
				ToCartesianFromCylindrical( rhs._u1, rhs._u2, rhs._u3, x2, y2, z2 ) ;
				value_type u1 = x1 + x2 ;
				value_type u2 = y1 + y2 ;
				value_type u3 = z1 + z2 ;
				value_type r ; value_type p ; value_type z ;
				ToCylindricalFromCartesian( u1, u2, u3, r, p, z) ;
				return cvector(r,p,z) ;
			}
			
			/**
			 * Adds two cvectors together
			 */
			cvector operator- (const cvector& rhs) {
				cvector tmp = rhs ;
				tmp = tmp * -1 ;
				return operator+(tmp) ;
			}
			
			/** =========== Scalar Operations =========== **/
			cvector operator* (const value_type& c) {
				return cvector(_u1*c,_u2,_u3) ;
			}

			cvector operator/ (const value_type& c) {
				return cvector(_u1/c,_u2,_u3) ;
			}
			
			cvector operator+ (const value_type& c) {
				return operator+(cvector(c,0,0)) ;
			}

			cvector operator- (const value_type& c) {
				return operator+(-c) ;
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
