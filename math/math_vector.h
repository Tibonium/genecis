/**
 * @file math_vector.h
 */
 
#ifndef MATH_MATH_VECTOR_H
#define MATH_MATH_VECTOR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

template <class _type> class math_vector {

	protected:
	
		/**
		 * Components of the 3-dimensional vector
		 */
		_type _u1 ;
		_type _u2 ;
		_type _u3 ;
	
	public:

		/**
		 * Returns the inner product of two math_vectors
		 *
		 *  dot product = |u| |v| cos(angle)
		 */
		virtual _type dot(const math_vector& other) const = 0 ;
		
		/**
		 * Returns the normalized vector
		 *
		 *  norm(u) = /frac{u} {|u|}
		 */
		template <typename T>
		inline T norm() const {
			_type n = sqrt(dot(*this)) ;
			_type u1 = _u1 / n ;
			_type u2 = _u2 / n ;
			_type u3 = _u3 / n ;
			return T(u1,u2,u3) ;
		}

		/**
		 * Returns the cross product of two math_vectors
		 *
		 *  Cross product =
		 *			| i   j   k  |
		 *		det	| u1  u2  u3 |   =
		 *			| v1  v2  v3 |
		 * 
		 *  (u2*v3-u3*v2) i - (u1*v3-u3*v1) j + (u1*v2-u2*v1) k
		 */
		template <typename T>
		inline T cross(const T& other) const {
			_type u1 = _u2 * other.u3() - _u3 * other.u2() ;
			_type u2 = _u1 * other.u3() - _u3 * other.u1() ;
			u2 *= -1.0 ;
			_type u3 = _u1 * other.u2() - _u2 * other.u1() ;
			return T(u1,u2,u3) ;
		}
		
		/**
		 * Returns the normalized inner product of two math_vectors
		 * which is the cosine of the angle between the two
		 * math_vectors.
		 *
		 *	cos(angle) = /frac{|u dot v|} {|u||v|} 
		 */
		inline _type dotnorm(const math_vector& other) const {
			_type result = dot(other) / 
				( sqrt(dot(*this)) * sqrt(other.dot(other)) ) ;
			return result ;
		}
		
		/**
		 * Returns the distance between two math_vectors
		 *
		 *   Distance =
		 *		|u| + |v| - 2.0 * |u dot v|
		 */
		inline _type distance(const math_vector& other) const {
			_type m1 = dot(*this) * dot(*this) ;
			_type m2 = other.dot(other) * other.dot(other) ;
			_type result = sqrt( m1 + m2 - 2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the magnitude square or the length
		 * of the vector.
		 */
		inline _type magnitude() {
			return sqrt(dot(*this)) ;
		}
		
		/**
		 * Functions for accessing and modifying the first component
		 */
		inline _type u1() const {
			return _u1 ;
		}
		
		inline void u1(_type _t) {
			_u1 = _t ;
		}
		
		/**
		 * Functions for accessing and modifying the second component
		 */
		inline _type u2() const {
			return _u2 ;
		}
		
		inline void u2(_type _t) {
			_u2 = _t ;
		}
		
		
		/**
		 * Functions for accessing and modifying the third component
		 */
		inline _type u3() const {
			return _u3 ;
		}
		
		inline void u3(_type _t) {
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
		template<typename T>
		void operator+ (const T& val) {
			_u1 += val ;
			_u2 += val ;
			_u3 += val ;
		}

		template<typename T>
		void operator- (const T& val) {
			_u1 -= val ;
			_u2 -= val ;
			_u3 -= val ;
		}
		
		template<typename T>
		void operator* (const T& val) {
			_u1 *= val ;
			_u2 *= val ;
			_u3 *= val ;
		}
		
		template<typename T>
		void operator/ (const T& val) {
			_u1 /= val ;
			_u2 /= val ;
			_u3 /= val ;
		}

		/// Destructor
		virtual ~math_vector() {} ;
		
};

#endif
