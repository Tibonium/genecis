/**
 * @file p_vector.h
 */
 
#ifndef PHYSICS_P_VECTOR_H
#define PHYSICS_P_VECTOR_H

#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <cmath>

class p_vector {

	private:
	
		/**
		 * Spherical Coordinates for doing mathematics and physics
		 * There are accessors to pull out information in cartesian
		 * coordinates if the user desires.
		 *
		 * @var	_rho	radius, units = meters
		 * @var _theta	polar angle, units = radians, positive = up
		 * @var _phi	azimuthal angle, units = radians,
		 *				positive = clockwise
		 */
		double _rho ;
		double _theta ;
		double _phi ;
	
	public:
	
		/**
		 * Returns the inner product of two p_vectors
		 *
		 *  dot product =
		 *		rho1*rho2 ( cos(theta1)cos(theta2) +
		 *		sin(theta1)sin(theta2)cos(phi1-phi2) )
		 */
		inline double dot(const p_vector& other) const {
			double result = ( _rho * other.rho() * ( 
				cos(_theta) * cos(other.theta()) +
				sin(_theta) * sin(other.theta()) *
				cos(_phi - other.phi()) ) ) ;
			return result ;
		}
		
		/**
		 * Returns the normalized inner product of two p_vectors
		 * which is the cosine of the angle between the two
		 * p_vectors.
		 *
		 *	cos(angle) = ( cose(theta1)cos(theta2) - 
		 *				sin(theaa1)sin(theta2)cos(phi1-phi2) )
		 */
		inline double dotnorm(const p_vector& other) const {
			double result = ( cos(_theta) * cos(other.theta()) +
				sin(_theta) * sin(other.theta()) * 
				cos(_phi - other.phi()) ) ;
			return result ;
		}
		
		/**
		 * Returns the distance between two p_vectors
		 */
		inline double distance(const p_vector& other) const {
			double result = sqrt( _rho * _rho +
				other.rho() * other.rho() - 2.0 * dot(other) ) ;
			return result ;
		}
		
		/**
		 * Returns the cross product of two p_vectors
		 *
		 *  Cross product =
		 *			(theta1*phi2 - phi1*theta2) /hat{rho} +
		 *			(phi1*rho2 - rho1*phi2) /hat{theta} +
		 *			(rho1*theta2 - theta1*rho2) /hat{phi}
		 */
		inline p_vector* cross(const p_vector& other) const {
			double rho = _theta * other.phi() - 
						 _phi * other.theta() ;
			double theta = _rho * other.phi() -
						   _phi * other.rho() ;
			theta *= -1.0 ;
			double phi = _rho * other.theta() -
						 _theta * other.rho() ;
			p_vector* result = new p_vector(rho,theta,phi) ;
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
		 * Convert the vector values in cartesian coordinates
		 */
		inline double x() const {
			return ( _rho * sin(_theta) * cos(_phi) ) ;
		}

		inline double y() const {
			return ( _rho * sin(_theta) * sin(_phi) ) ;
		}

		inline double z() const {
			return ( _rho * cos(_theta) ) ;
		}
			
		/**
		 * Constructor
		 * This allows the user to create a quick and easy accessor
		 * to spherical coordinates system vector. Though in the
		 * partical sense this is not a c/c++ vector but a physics
		 * or mathetmatical meaning of such. To simplify the process
		 * the user passes in the theta and phi compoments in degrees
		 * and they are converted to radians and stored.
		 *
		 * @param d1	The value in the rho or x direction
		 * @param d2	The value in the theta or y direction
		 * @param d3	The value in the phi or z direction
		 * @param cart	A flag that is set to allow the user to pass
		 *				the values above in as cartesian coordinates
		 *				as opposed to the default, spherical. AT
		 *				construction the values are then converted
		 *				into the respective spherical values.
		 */
		p_vector(double d1, double d2, double d3, bool cart=false) {
			if( cart ) {
				_rho = sqrt( d1 * d1 + d2 * d2 + d3 * d3 ) ;
				_theta = acos( d3 / _rho ) ;
				_phi = atan( d2 / d1 ) ;
			} else {
				_rho = d1 ;
				_theta = d2 * M_PI / 180.0;
				_phi = d3 * M_PI / 180.0 ;
			}
		}
		
		// Destructor
		~p_vector() {}
		
		friend std::ostream& operator<< (std::ostream& os, const p_vector& other) ;

};

// std::output override for p_vector
inline std::ostream& operator<< (std::ostream& os, const p_vector& other) {
	os << "p_vector(rho,theta,phi): ("
	   << other.rho() << ", "
	   << other.theta() << ", "
	   << other.phi() << ")" ;
	return os ;
};

#endif
