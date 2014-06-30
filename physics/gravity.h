/**
 * @file gravity.h
 */

#ifndef GENECIS_PHYSICS_GRAVITY_H
#define GENECIS_PHYSICS_GRAVITY_H

#include "../math/mathematics.h"
#include <netcdfcpp.h>

class gravity {

	public:

		/**
		 * Newton's Law of gravitational force is between
		 * two bodies with masses m1 and m2. The force 
		 * between these two masses is governed by the
		 * equation:
		 *
		 *     F = /frac{G m1 m2} {r^2}
		 *
		 * Where G is the universal gravitation constant,
		 * m1 and m2 are the masses of the bodies, and r
		 * is the half the radial distance between the 
		 * center of mass1 and mass2.
		 *
		 * @param mass1		Mass of the first body
		 * @param mass2		Mass of the second body
		 * @param dt		Increment of time for iterations
		 * @param pos1		starting position of the first object
		 * @param pos2		starting position of the second object
		 * @param vel1		initial velocity of obj1
		 * @param vel2		initial velocity of obj2
		 * @param acc1		initial acceleration of obj1
		 * @param acc2		initial acceleration of obj2
		 */
		gravity( double mass1, double mass2, double dt,
				 svector* pos1, svector* pos2,
				 svector* vel1, svector* vel2,
				 svector* acc1, svector* acc2 ) ;
				 
		/** General information accessors **/
		inline svector* position1() {
			return _p1 ;
		}

		inline svector* position2() {
			return _p2 ;
		}

		inline svector* velocity1() {
			return _v1 ;
		}
		
		inline svector* velocity2() {
			return _v2 ;
		}
		
		inline svector* acceleration1() {
			return _a1 ;
		}
		
		inline svector* acceleration2() {
			return _a2 ;
		}
		
		inline double mass1() {
			return _m1 ;
		}
		
		inline double mass2() {
			return _m2 ;
		}
		
		inline double time() {
			return _time ;
		}
		
		/**
		 * Initialize recording of netCDF motion log.
		 * Opens the file and records initial conditions.
		 * The file structure is illustrated by the sample
		 * netCDF below:
		 * <pre>
		 * netcdf sample_test {
		 *	dimensions:
		 *		travel_time = UNLIMITED ;	// currently
		 *	variables:
		 *		double pos1(travel_time, travel_time, travel_time) ;
		 *			rho::units = "meters" ;
		 *			theta::units = "radians" ;
		 *			theta::positive = "up" ;
		 *			phi::units = "radians" ;
		 *			phi::positive = "clockwise" ;
		 *		double pos1(travel_time, travel_time, travel_time) ;
		 *			rho::units = "meters" ;
		 *			theta::units = "radians" ;
		 *			theta::positive = "up" ;
		 *			phi::units = "radians" ;
		 *			phi::positive = "clockwise" ;
		 *		double travel_time(travel_time) ;
		 *			travel_time::units = "seconds" ;
		 *
		 *	data:
		 *		pos1 = (1,0,0), (1,0,0), (1,0,0), ...
		 *		pos2 = (1,0,0), (1,0,0), (1,0,0), ...
		 *		travel_time = 0.1, 0.2, 0.3, ...
		 *   }
		 * <pre>
		 * @param filename	  Name of file to write to disk.
		 * @param long_name	  Optional global attribute for
		 *				  identifying data-set
		 */
		void init_netcdf( const char* filename,
					   const char* long_name=NULL ) ;
		
		/**
		 * Write current record to the netCDF file.
		 * Records, time, time step, and spherical positions
		 * for both bodies.
		 */
		void save_netcdf() ;
		
		/** Close the netCDF log file. */
		void close_netcdf() ;
		
	private:
	
		/**
		 * Universal gravitaiton constant, units are
		 * m^3 kg^(-1) s^(-2)
		 */
		static const double _G = 6.6738480e-11 ;
		static const double _AU = 149597870700 ;  //meters

		/**
		 * Terms for a simulation of Newton's Law of
		 * gravity.
		 *
		 * @var _m1		mass of the first body, units = kg
		 * @var _m2		mass of the second body, units = kg
		 * @var _dt		Time increment for calculations
		 * @var _p1		position of the first body
		 * @var _p2		position of the second body
		 * @var _v1		velocity of the first body
		 * @var _v2		velocity of the second body
		 * @var _a1		acceleration of the first body
		 * @var _a2		acceleration of the second body
		 * @var _time	Current time in the simulation
		 */
		double _m1 ;
		double _m2 ;
		double _dt ;
		svector* _p1 ;
		svector* _p2 ;
		svector* _v1 ;
		svector* _v2 ;
		svector* _a1 ;
		svector* _a2 ;
		double _time ;
		
		/**
		 * Marching function for the simulation of gravitational
		 * interactions between two bodies. All mathematical
		 * calculations go on during this function call and 
		 * moves the bodies in accordance to Newton's laws of
		 * gravity.
		 */
		void step() ;
		
		/**
		 * The netCDF file uses to record the motion
		 * of two bodies due to gravitation forces.
		 */
		NcFile* _nc_file ;
		
		/** netCDF variables to record the data */
		NcVar *_nc_pos1, *_nc_pos2, *_nc_v1, *_nc_v2,
			 *_nc_time ;
			 
		
		/** Current record number in the netCDF file. */
		int _nc_rec ;
};

#endif
