/**
 * @file gravity.h
 */

#ifndef PHYSICS_GRAVITY_H
#define PHYSICS_GRAVITY_H

#include "../math/mathematics.h"

class gravity {

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
		 * @var _mass1		mass of the first body, units = kg
		 * @var _mass2		mass of the second body, units = kg
		 * @var _obj1		position of the first body
		 * @var _obj2		position of the second body
		 * @var _dt		Time increment for calculations
		 */
		double _mass1 ;
		double _mass2 ;
		svector* _obj1 ;
		svector* _obj2 ;
		double _dt ;
		
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
		 * @param obj1		starting position of the first object
		 * @param obj2		starting position of the second object
		 * @param mass1	Mass of the first body
		 * @param mass2	Mass of the second body
		 * @param dt		Increment of time for iterations
		 */
		gravity(svector* obj1, svector* obj2,
			   double mass1, double mass2, double dt) ;
		
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
};

#endif
