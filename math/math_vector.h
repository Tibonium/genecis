/**
 * @file math_vector.h
 */
 
#ifndef GENECIS_MATH_MATH_VECTOR_H
#define GENECIS_MATH_MATH_VECTOR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <algorithm>

namespace genecis {
namespace math {

template <class _T> class math_vector {

	public:
	
		typedef _T		value_type ;

		/// Destructor
		virtual ~math_vector() {} ;

		/**
		 * Returns the inner product of two math_vectors
		 *
		 *  dot product = |u| |v| cos(angle)
		 */
		virtual value_type dot(const math_vector& other) const = 0 ;
		
		/**
		 * Returns the normalized vector
		 *
		 *  norm(u) = /frac{u} {|u|}
		 */
		void norm() {
			value_type n = sqrt(dot(*this)) ;
			this->u1( _u1 / n ) ;
			this->u2( _u2 / n ) ;
			this->u3( _u3 / n ) ;
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
		template <class T>
		inline T cross(const T& other) const {
			value_type u1 = _u2 * other.u3() - _u3 * other.u2() ;
			value_type u2 = _u1 * other.u3() - _u3 * other.u1() ;
			u2 *= -1.0 ;
			value_type u3 = _u1 * other.u2() - _u2 * other.u1() ;
			return T(u1,u2,u3) ;
		}
		
		/**
		 * Returns the normalized inner product of two math_vectors
		 * which is the cosine of the angle between the two
		 * math_vectors.
		 *
		 *	cos(angle) = /frac{|u dot v|} {|u||v|} 
		 */
		inline value_type dotnorm(const math_vector& other) const {
			value_type result = dot(other) / 
				( sqrt(dot(*this)) * sqrt(other.dot(other)) ) ;
			return result ;
		}
		
		/**
		 * Returns the distance between two math_vectors
		 *
		 *   Distance =
		 *		|u| + |v| - 2.0 * |u dot v|
		 */
		inline value_type distance(const math_vector& other) const {
			value_type m1 = dot(*this) * dot(*this) ;
			value_type m2 = other.dot(other) * other.dot(other) ;
			value_type result = sqrt( m1 + m2 - 2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the magnitude square or the length
		 * of the vector.
		 */
		inline value_type magnitude() {
			return sqrt(dot(*this)) ;
		}
		
		/**
		 * Functions for accessing and modifying the first component
		 */
		inline value_type u1() const {
			return _u1 ;
		}

		inline void u1(value_type _t) {
			_u1 = _t ;
		}
		
		/**
		 * Functions for accessing and modifying the second component
		 */
		inline value_type u2() const {
			return _u2 ;
		}
		
		inline void u2(value_type _t) {
			_u2 = _t ;
		}
		
		
		/**
		 * Functions for accessing and modifying the third component
		 */
		inline value_type u3() const {
			return _u3 ;
		}
		
		inline void u3(value_type _t) {
			_u3 = _t ;
		}
		
		/**
		 * Various overload operators required for different
		 * mathematical operations and comparisons.
		 */
		bool operator== (const math_vector& other) {
			bool result = ( ( _u1 == other.u1() ) &&
					      ( _u2 == other.u2() ) &&
					      ( _u3 == other.u3() ) ) ;
			return result ;
		}

		bool operator!= (const math_vector& other) {
			return !( *this == other ) ;
		}
		
		bool operator> (const math_vector& other) {
			return ( dot(*this) > dot(other) ) ;
		}
		
		bool operator>= (const math_vector& other) {
			return !(*this < other) ;
		}
		
		bool operator< (const math_vector& other) {
			return ( dot(other) > dot(*this) ) ;
		}
		
		bool operator<= (const math_vector& other) {
			return !(*this > other) ;
		}
		
		void operator- (const math_vector& other) {
			_u1 -= other.u1() ;
			_u2 -= other.u2() ;
			_u3 -= other.u3() ;
		}
		
		void operator+ (const math_vector& other) {
			_u1 += other.u1() ;
			_u2 += other.u2() ;
			_u3 += other.u3() ;
		}

		void operator= (const math_vector& other) {
			_u1 = other.u1() ;
			_u2 = other.u2() ;
			_u3 = other.u3() ;
		}

		/** Various operators for scalar arithmetics */
		void operator+ (const value_type& val) {
			_u1 += val ;
			_u2 += val ;
			_u3 += val ;
		}

		void operator- (const value_type& val) {
			_u1 -= val ;
			_u2 -= val ;
			_u3 -= val ;
		}
		
		void operator* (const value_type& val) {
			_u1 *= val ;
			_u2 *= val ;
			_u3 *= val ;
		}
		
		void operator/ (const value_type& val) {
			_u1 /= val ;
			_u2 /= val ;
			_u3 /= val ;
		}

	protected:
	
		/**
		 * Components of the 3-dimensional vector
		 */
		value_type _u1 ;
		value_type _u2 ;
		value_type _u3 ;
	
		/**
		 * Converts spherical coordinates into cartesian
		 */
		void ToCartesianFromSpherical( const value_type& rho,
			const value_type& theta, const value_type& phi,
			value_type& x, value_type& y, value_type& z )
		{
			x = rho * sin(theta) * cos(phi) ;
			y = rho * sin(theta) * sin(phi) ;
			z = rho * cos(theta) ;
		}
		
		/**
 		 * Converts cartesian coordinates into spherical
 		 */
		void ToSphericalFromCartesian( const value_type& x,
			const value_type& y, const value_type& z, value_type& rho,
			value_type& theta, value_type& phi )
		{
			rho = sqrt( x*x + y*y + z*z ) ;
			theta = acos( z / rho ) ;
			// gaurd against dividing by zero
			if( x <= 1e-10 ) {
				phi = 0.0 ;
			} else {
				phi = atan( y / x ) ;
			}
		}
		
		/**
		 * Converts cylindrical coordinates into cartesian
		 */
		void ToCartesianFromCylindrical( const value_type& r,
			const value_type& p, const value_type& zc,
			value_type& x, value_type& y, value_type& z )
		{
			x = r * cos(p) ;
			y = r * sin(p) ;
			z = zc ;
		}
		
		/**
		 * Converts cartesian coordinates into cylindrical
		 */
		void ToCylindricalFromCartesian( const value_type& x,
			const value_type& y, const value_type& z, value_type& r,
			value_type& p, value_type& zc )
		{
			r = sqrt( x*x + y*y ) ;
			if( abs(x) <= 1e-10) {
				p = 0 ;
			} else {
				p = atan( y / x ) ;
			}
			zc = z ;
		}
		
		/****/
		void ToSphericalFromCylindrical( const value_type& r,
			const value_type& p, const value_type& z,
			value_type& rho, value_type& theta, value_type& phi )
		{
			rho = sqrt( r*r + z*z ) ;
			theta = atan( r / z ) ;
			phi = p ;
		}
		
		/****/
		void ToCylindricalFromSpherical( const value_type& rho,
			const value_type& theta, const value_type& phi,
			value_type& r, value_type& p, value_type& z )
		{
			r = rho * sin(theta) ;
			p = phi ;
			z = rho * cos(theta) ;
		}
		
};

}	// end of namespace math
}	// end of namespace genecis

#endif
