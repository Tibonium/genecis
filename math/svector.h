/**
 * @file svector.h
 */
 
#ifndef MATH_SVECTOR_H
#define MATH_SVECTOR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class svector {

	private:
	
		/**
		 * Mathematical vectors in spherical coordinates
		 *
		 * @var _rho	radius, units = "distance from origin"
		 * @var _theta	polar angle, units = radians, positive = up
		 * @var _phi	azimuthal angle, units = radians,
		 *				positive = clockwise
		 */
		double _rho ;
		double _theta ;
		double _phi ;
	
	public:
	
		/**
		 * Returns the inner product of two svectors
		 *
		 *  dot product =
		 *		rho1*rho2 ( cos(theta1)cos(theta2) +
		 *		sin(theta1)sin(theta2)cos(phi1-phi2) )
		 */
		inline double dot(const svector& other) const {
			double result = ( _rho * other.rho() * ( 
				cos(_theta) * cos(other.theta()) +
				sin(_theta) * sin(other.theta()) *
				cos(_phi - other.phi()) ) ) ;
			return result ;
		}
		
		/**
		 * Returns the normalized inner product of two svectors
		 * which is the cosine of the angle between the two
		 * svectors.
		 *
		 *	cos(angle) = ( cose(theta1)cos(theta2) - 
		 *				sin(theaa1)sin(theta2)cos(phi1-phi2) )
		 */
		inline double dotnorm(const svector& other) const {
			double result = ( cos(_theta) * cos(other.theta()) +
				sin(_theta) * sin(other.theta()) * 
				cos(_phi - other.phi()) ) ;
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
		inline svector norm() const {
			double n = dot(*this) ;
			return svector(_rho/n, _theta/n, _phi/n) ;
		}
		
		/**
		 * Returns the distance between two svectors
		 */
		inline double distance(const svector& other) const {
			double result = sqrt( _rho * _rho +
				other.rho() * other.rho() - 2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the cross product of two svectors
		 *
		 *  Cross product =
		 *			(theta1*phi2 - phi1*theta2) /hat{rho} +
		 *			(phi1*rho2 - rho1*phi2) /hat{theta} +
		 *			(rho1*theta2 - theta1*rho2) /hat{phi}
		 */
		inline svector cross(const svector& other) const {
			double rho = _theta * other.phi() - 
						 _phi * other.theta() ;
			double theta = _rho * other.phi() -
						   _phi * other.rho() ;
			theta *= -1.0 ;
			double phi = _rho * other.theta() -
						 _theta * other.rho() ;
			svector result(rho,theta,phi) ;
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
		inline double theta() const {
			return _theta ;
		}
		
		inline void theta(double _t) {
			_theta = _t ;
		}
		
		
		/**
		 * Functions for accessing and modifying the phi component
		 */
		inline double phi() const {
			return _phi ;
		}
		
		inline void phi(double _p) {
			_phi = _p ;
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
		 * @param d1	rho component of the vector
		 * @param d2	theta component of the vector
		 * @param d3	phi component of the vector
		 */
		svector(double d1, double d2, double d3) {
			_rho = d1 ;
			_theta = d2 * M_PI / 180.0 ;
			_phi = d3 * M_PI / 180.0 ;
		}
		
		// Destructor
		~svector() {}
		
		/**
		 * Various overload operators required for different
		 * mathematical operations and comparisons.
		 */
		bool operator== (const svector& other) {
			bool result = ( ( _rho == other.rho() ) &&
					      ( _theta == other.theta() ) &&
					      ( _phi == other.phi() ) ) ;
			return result ;
		}

		bool operator!= (const svector& other) {
			return !( *this == other ) ;
		}
		
		bool operator> (const svector& other) {
			return ( dot(*this) > dot(other) ) ;
		}
		
		bool operator>= (const svector& other) {
			return !(*this < other) ;
		}
		
		bool operator< (const svector& other) {
			return ( dot(other) > dot(*this) ) ;
		}
		
		bool operator<= (const svector& other) {
			return !(*this > other) ;
		}
		
		void operator- (const svector& other) {
			_rho -= other.rho() ;
			_theta -= other.theta() ;
			_phi -= other.phi() ;
		}
		
		void operator+ (const svector& other) {
			_rho += other.rho() ;
			_theta += other.theta() ;
			_phi += other.phi() ;
		}

		void operator= (const svector& other) {
			_rho = other.rho() ;
			_theta = other.theta() ;
			_phi = other.phi() ;
		}

		template<typename T>
		void operator/ (const T& val) {
			_rho /= val ;
			_theta /= val ;
			_phi /= val ;
		}
				
		friend std::ostream& operator<< (std::ostream& os, const svector& other) ;

};

// std::output override for svector
inline std::ostream& operator<< (std::ostream& os, const svector& other) {
	os << "(rho,theta,phi): ("
	   << other.rho() << ", "
	   << other.theta() << ", "
	   << other.phi() << ")" ;
	return os ;
};

#endif
