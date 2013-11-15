/**
 * @file bvector.h
 */
 
#ifndef MATH_BVECTOR_H
#define MATH_BVECTOR_H

#include <iostream>

class bvector {

	private:
	
		/**
		 * Mathematical vectors in cartesian coordinates
		 *
		 * @var _x	x-axis value, positive = out
		 * @var _y	y-axis value, positive = right
		 * @var _z	z-axis value, positive = up
		 */
		double _x ;
		double _y ;
		double _z ;
	
	public:
	
		/**
		 * Returns the inner product of two bvectors
		 *
		 *  dot product =
		 *		x*x + y*y + z*z
		 */
		inline double dot(const bvector& other) const {
			double result = _x * other.x() + 
							_y * other.y() +
							_z * other.z() ;
			return result ;
		}
		
		/**
		 * Returns the normalized inner product of two bvectors
		 * which is the cosine of the angle between the two
		 * bvectors.
		 *
		 *	cos(angle) = /frac{|u dot v|} {|u||v|} 
		 */
		inline double dotnorm(const bvector& other) const {
			double result = dot(other) / 
				( dot(*this) * other.dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the magnitude square or the length
		 * of the vector.
		 */
		inline double magnitude() {
			return dot(*this) ;
		}
		
		/**
		 * Returns the normalized vector
		 */
		inline bvector norm() const {
			double n = dot(*this) ;
			return bvector(_x/n, _y/n, _z/n) ;
		}
		
		/**
		 * Returns the distance between two bvectors
		 *
		 *   Distance =
		 *		|u| + |v| - 2.0 * cos(angle)
		 */
		inline double distance(const bvector& other) const {
			double result = sqrt( dot(*this) * dot(*this) +
				other.dot(other) * other.dot(other) -
				2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the cross product of two bvectors
		 *
		 *  Cross product =
		 *			(y1*z2 - z1*y2) /hat{x} +
		 *			(x1*z2 - z1*x2) /hat{y} +
		 *			(x1*y2 - y1*x2) /hat{z}
		 */
		inline bvector cross(const bvector& other) const {
			double x = _y * other.z() - _z * other.y() ;
			double y = -1.0 * ( _x * other.z() - _z * other.x() ) ;
			double z = _x * other.y() - _y * other.x() ;
			bvector result(x,y,z) ;
			return result ;
		}
		
		/**
		 * Functions for accessing and modifying the x component
		 */
		inline double x() const {
			return _x ;
		}
		
		inline void x(double _r) {
			_x = _r ;
		}
		
		/**
		 * Functions for accessing and modifying the y component
		 */
		inline double y() const {
			return _y ;
		}
		
		inline void y(double _t) {
			_y = _t ;
		}
		
		
		/**
		 * Functions for accessing and modifying the z component
		 */
		inline double z() const {
			return _z ;
		}
		
		inline void z(double _p) {
			_z = _p ;
		}
			
		/**
		 * Constructor
		 * This allows the user to create a quick and easy accessor
		 * to spherical coordinates system vector. Though in the
		 * partical sense this is not a c/c++ vector but a physics
		 * or mathetmatical meaning of such. To simplify the process
		 * the user passes in the theta and phi compoments in degrees
		 * and they are converted to radians.
		 *
		 * @param d1	x component of the vector
		 * @param d2	y component of the vector
		 * @param d3	z component of the vector
		 */
		bvector(double d1, double d2, double d3) {
			_x = d1 ;
			_y = d2 ;
			_z = d3 ;
		}
		
		// Destructor
		~bvector() {}
		
		/**
		 * Various overload operators required for different
		 * mathematical operations and comparisons.
		 */
		bool operator== (const bvector& other) {
			bool result = ( ( _x == other.x() ) &&
					      ( _y == other.y() ) &&
					      ( _z == other.z() ) ) ;
			return result ;
		}

		bool operator!= (const bvector& other) {
			return !( *this == other ) ;
		}
		
		bool operator> (const bvector& other) {
			return ( dot(*this) > dot(other) ) ;
		}
		
		bool operator>= (const bvector& other) {
			return !(*this < other) ;
		}
		
		bool operator< (const bvector& other) {
			return ( dot(other) > dot(*this) ) ;
		}
		
		bool operator<= (const bvector& other) {
			return !(*this > other) ;
		}
		
		void operator- (const bvector& other) {
			_x -= other.x() ;
			_y -= other.y() ;
			_z -= other.z() ;
		}
		
		void operator+ (const bvector& other) {
			_x += other.x() ;
			_y += other.y() ;
			_z += other.z() ;
		}

		void operator= (const bvector& other) {
			_x = other.x() ;
			_y = other.y() ;
			_z = other.z() ;
		}

		template<typename T>
		void operator/ (const T& val) {
			_x /= val ;
			_y /= val ;
			_z /= val ;
		}
				
		friend std::ostream& operator<< (std::ostream& os, const bvector& other) ;

};

// std::output override for bvector
inline std::ostream& operator<< (std::ostream& os, const bvector& other) {
	os << "(x,y,z): ("
	   << other.x() << ", "
	   << other.y() << ", "
	   << other.z() << ")" ;
	return os ;
};

#endif
