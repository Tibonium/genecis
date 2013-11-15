/**
 * @file cvector.h
 */
 
#ifndef MATH_CVECTOR_H
#define MATH_CVECTOR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class cvector {

	private:
	
		/**
		 * Mathematical vectors in cylindrical coordinates
		 *
		 * @var _rho	radius, units = "distance from origin"
		 * @var _phi	azimuthal angle, units = radians,
		 * 				positive = clockwise
		 * @var _z		height, positive = up ;
		 */
		double _rho ;
		double _phi ;
		double _z ;
	
	public:
	
		/**
		 * Returns the inner product of two cvectors
		 *
		 *  dot product =
		 *		r1*cos(p1) * r2*cos(p2) +
		 *		r1*sin(p1) * r2*sin(p2) +
		 *		z1 * z2
		 */
		inline double dot(const cvector& other) const {
			double result = ( _rho * cos(_phi) * 
					other.rho() * cos(other.phi()) + 
					_rho * sin(_phi) * 
					other.phi() * sin(other.phi()) +
					_z * other.z() ) ;
			return result ;
		}
		
		/**
		 * Returns the normalized inner product of two cvectors
		 * which is the cosine of the angle between the two
		 * cvectors.
		 *
		 *	cos(angle) = /frac{|u dot v|} {|u||v|} 
		 */
		inline double dotnorm(const cvector& other) const {
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
		inline cvector norm() const {
			double n = dot(*this) ;
			return cvector(_rho/n, _phi/n, _z/n) ;
		}
		
		/**
		 * Returns the distance between two cvectors
		 *
		 *   Distance =
		 *		|u| + |v| - 2.0 * |u| |v| cos(angle)
		 */
		inline double distance(const cvector& other) const {
			double result = sqrt( dot(*this) * dot(*this) +
				other.dot(other) * other.dot(other) -
				2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the cross product of two cvectors
		 *
		 *  Cross product =
		 *			(p1*z2 - z1*p2) /hat{rho} +
		 *			(r1*z2 - z1*r2) /hat{phi} +
		 *			(r1*p2 - p1*r2) /hat{z}
		 */
		inline cvector cross(const cvector& other) const {
			double rho = _phi * other.z() - 
						 _z * other.phi() ;
			double phi = _rho * other.z() -
						 _z * other.rho() ;
			phi *= -1.0 ;
			double z = _rho * other.phi() -
					   _phi * other.rho() ;
			cvector result(rho,phi,z) ;
			return result ;
		}
		
		/**
		 * Functions for accessing and modifying the rho component
		 */
		inline double rho() const {
			return _rho ;
		}
		
		inline void rho(double _r) {
			_rho = _r ;
		}
		
		/**
		 * Functions for accessing and modifying the theta component
		 */
		inline double phi() const {
			return _phi ;
		}
		
		inline void phi(double _p) {
			_phi = _p ;
		}
		
		
		/**
		 * Functions for accessing and modifying the phi component
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
		 * the user passes phi compoment in degrees and is converted
		 * to radians.
		 *
		 * @param d1	rho component of the vector
		 * @param d2	phi component of the vector
		 * @param d3	z component of the vector
		 */
		cvector(double d1, double d2, double d3) {
			_rho = d1 ;
			_phi = d2 * M_PI / 180.0 ;
			_z = d3 ;
		}
		
		// Destructor
		~cvector() {}
		
		/**
		 * Various overload operators required for different
		 * mathematical operations and comparisons.
		 */
		bool operator== (const cvector& other) {
			bool result = ( ( _rho == other.rho() ) &&
					      ( _phi == other.phi() ) &&
					      ( _z == other.z() ) ) ;
			return result ;
		}

		bool operator!= (const cvector& other) {
			return !( *this == other ) ;
		}
		
		bool operator> (const cvector& other) {
			return ( dot(*this) > dot(other) ) ;
		}
		
		bool operator>= (const cvector& other) {
			return !(*this < other) ;
		}
		
		bool operator< (const cvector& other) {
			return ( dot(other) > dot(*this) ) ;
		}
		
		bool operator<= (const cvector& other) {
			return !(*this > other) ;
		}
		
		void operator- (const cvector& other) {
			_rho -= other.rho() ;
			_phi -= other.phi() ;
			_z -= other.z() ;
		}
		
		void operator+ (const cvector& other) {
			_rho += other.rho() ;
			_phi += other.phi() ;
			_z += other.z() ;
		}

		void operator= (const cvector& other) {
			_rho = other.rho() ;
			_phi = other.phi() ;
			_z = other.z() ;
		}

		template<typename T>
		void operator/ (const T& val) {
			_rho /= val ;
			_phi /= val ;
			_z /= val ;
		}
				
		friend std::ostream& operator<< (std::ostream& os, const cvector& other) ;

};

// std::output override for cvector
inline std::ostream& operator<< (std::ostream& os, const cvector& other) {
	os << "(rho,phi,z): ("
	   << other.rho() << ", "
	   << other.phi() << ", "
	   << other.z() << ")" ;
	return os ;
};

#endif
