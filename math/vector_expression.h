/**
 * @file vector_expression.h
 */
 
#ifndef GENECIS_MATH_VECTOR_EXPRESSION_H
#define GENECIS_MATH_VECTOR_EXPRESSION_H

#include <cmath>
#define pi2 2.0*M_PI
#define pi M_PI

namespace genecis {
namespace math {

	using namespace std ;
	 
	template<template<typename> class E, typename T>
	class vector_expression {
		public:
			typedef T										 value_type ;
			typedef T *									 	 pointer ;
			typedef const T *								 const_pointer ;
			typedef ptrdiff_t								 difference_type ;
			typedef T &									 	 reference ;
			typedef const T &								 const_reference ;
			typedef size_t									 size_type ;
			
			/** ============ Expression Accessors ============= **/			
			operator E<T>& () {
				return static_cast<E<T>&> (*this) ;
			}
			
			operator E<T> const&() const {
				return static_cast<const E<T>&> (*this) ;
			}
			
			/** ============ Vector expression operators ============ **/
			/**
			 * Returns the inner product of two vectors
			 */
			value_type dot(const E<T>& v) const {
				return static_cast<E<T> const&> (*this).dot(v) ;
			}
			
			/**
			 * Returns the cross product of two vectors
			 */
			E<T> cross(const E<T>& v) const {
				return static_cast<E<T> const&> (*this).cross(v) ;
			}

			/**
			 * Adds two vectors and returns a new vector
			 */
			E<T> operator+(const E<T>& v) {
				return static_cast<E<T>&> (*this).operator+(v) ;
			}

			/**
			 * Subtracts two vectors and returns a new vector
			 */
			E<T> operator-(const E<T>& v) {
				return static_cast<E<T>&> (*this).operator-(v) ;
			}

			/**
			 * Returns the normalized inner product of two math_vectors
			 * which is the cosine of the angle between the two
			 * math_vectors.
			 *
			 *	cos(angle) = /frac{|u dot v|} {|u||v|} 
			 */
			value_type dotnorm(const E<T>& v) const {
				value_type result = this->dot(v) / 
					( sqrt(dot(*this)) * sqrt(v.dot(v)) ) ;
				return result ;
			}
		
			/**
			 * Returns the distance between two math_vectors
			 *
			 *   Distance =
			 *		|u| + |v| - 2.0 * |u dot v|
			 */
			value_type distance(const E<T>& v) const {
				value_type m1 = dot(*this) * dot(*this) ;
				value_type m2 = v.dot(v) * v.dot(v) ;
				value_type result = sqrt( m1 + m2 - 2.0 * dot(v) ) ;
				return result ;
			}
		
			/**
			 * Returns the magnitude of the vector.
			 */
			value_type magnitude() {
				return sqrt(dot(*this)) ;
			}
			
			/**
			 * Normalizes the vector to unit length
			 */
			void norm() {
				value_type n = sqrt(dot(*this)) ;
				this->u1( this->u1() / n ) ;
				this->u2( this->u2() / n ) ;
				this->u3( this->u3() / n ) ;
			}

			/** ============ Vector component accessors ============= **/
				// obtain the value in u1
			value_type u1() const {
				return static_cast<E<T> const&> (*this).u1() ;
			}
			
			value_type u1() {
				return static_cast<E<T> &> (*this).u1() ;
			}
			
				// obtain the value in u2
			value_type u2() const {
				return static_cast<E<T> const&> (*this).u2() ;
			}
			
			value_type u2() {
				return static_cast<E<T> &> (*this).u2() ;
			}
			
				// obtain the value in u3
			value_type u3() const {
				return static_cast<E<T> const&> (*this).u3() ;
			}

			value_type u3() {
				return static_cast<E<T> &> (*this).u3() ;
			}

			/** ============ Vector component assignment ============= **/
				// Assign value to u1
			void u1(value_type t) {
				return static_cast<E<T> &> (*this).u1(t) ;
			}

				// Assign value to u2
			void u2(value_type t) {
				return static_cast<E<T> &> (*this).u3(t) ;
			}
			
				// Assign value to u3
			void u3(value_type t) {
				return static_cast<E<T> &> (*this).u3(t) ;
			}
			
				// Copy operation
			void operator=(const E<T>& v) {
				(*this).u1( v.u1() ) ;
				(*this).u2( v.u2() ) ;
				(*this).u3( v.u3() ) ;
			}

			/** ============ Vector comparison operators ============= **/
			bool operator== (E<T>& other) {
				bool result = ( ( (*this).u1() == other.u1() ) &&
							  ( (*this).u2() == other.u2() ) &&
							  ( (*this).u3() == other.u3() ) ) ;
				return result ;
			}

			bool operator!= (E<T>& other) {
				return !( (*this) == other ) ;
			}
		
			bool operator> (E<T>& other) {
				return ( dot( (*this) ) > dot(other) ) ;
			}
		
			bool operator>= (E<T>& other) {
				return !( (*this) < other) ;
			}
		
			bool operator< (E<T>& other) {
				return ( dot(other) > dot( (*this) ) ) ;
			}
		
			bool operator<= (E<T>& other) {
				return !( (*this) > other) ;
			}
		
			/** ============ Vector scalar operators ============= **/
			E<T> operator+ (const value_type& val) {
				return static_cast<E<T> const> (*this).operator+(val) ;
			}

			E<T> operator- (const value_type& val) {
				return static_cast<E<T> const> (*this).operator-(val) ;
			}

			E<T> operator* (const value_type& val) {
				return static_cast<E<T> const> (*this).operator*(val) ;
			}
		
			E<T> operator/ (const value_type& val) {
				return static_cast<E<T> const> (*this).operator/(val) ;
			}

		protected:
		
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
		
			/**
			 * Converts cylindrical coordinates to spherical
			 */
			void ToSphericalFromCylindrical( const value_type& r,
				const value_type& p, const value_type& z,
				value_type& rho, value_type& theta, value_type& phi )
			{
				rho = sqrt( r*r + z*z ) ;
				theta = atan( r / z ) ;
				phi = p ;
			}
		
			/**
			 * Converts spherical coordinates to cylindrical
			 */
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
