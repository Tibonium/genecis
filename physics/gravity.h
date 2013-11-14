/**
 * @file gravity.h
 */

#ifndef PHYSICS_GRAVITY_H
#define PHYSICS_GRAVITY_H

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
		 * @var _dt			Time increment for calculations
		 */
		double _mass1 ;
		double _mass2 ;
		p_vector* _obj1 ;
		p_vector* _obj2 ;
		double _dt ;
	
		step() ;
		
		/**
		 * The netCDF file uses to record the motion
		 * of two bodies due to gravitation forces.
		 */
		NcFile* _nc_file ;
		
		/** netCDF variables to record the data */
		NcVar *_nc_rho1, *_nc_theta1, *_nc_phi1,
			 *_nc_rho2, *_nc_theta2, *_nc_phi2,
			 *_nc_v_rho1, *_nc_v_theta1, *_nc_v_phi1,
			 *_nc_v_rho2, *_nc_v_theta2, *_nc_v_phi2,
			 *_nc_f_rho, *_nc_f_theta, *_nc_f_phi,
			 *_nc_time, *_nc_dt, *_nc_mass1, *_nc_mass2 ;
			 
		
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
		 * @param obj		starting positions of the two masses
		 * @param mass1		Mass of the first body
		 * @param mass2		Mass of the second body
		 * @param dt		Increment of time for iterations
		 */
		gravity(p_vector& obj, mass1, mass2, dt) ;
		
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
		 *		double rho1(travel_time) ;
		 *			rho1::units = "meters" ;
		 *		double theta1(travel_time) ;
		 *			theta1::units = "radians" ;
		 *			theta1::positive = "up" ;
		 *		double phi1(travel_time) ;
		 *			phi1::units = "radians" ;
		 *			phi1::positive = "clockwise" ;
		 *		double rho2(travel_time) ;
		 *			rho2::units = "meters" ;
		 *		double theta2(travel_time) ;
		 *			theta2::units = "radians" ;
		 *			theta2::positive = "up" ;
		 *		double phi2(travel_time) ;
		 *			phi2::units = "radians" ;
		 *			phi2::positive = "clockwise" ;
		 *		double travel_time(travel_time) ;
		 *			travel_time::units = "seconds" ;
		 *
		 *	// global attributes:
		 *			:Convetions = "COARDS" ;
		 *
		 *	data:
		 *		rho1 = 1, 1, 1, ...
		 *		theta1 = 0, 0, 0, ...
		 *		phi1 = 0, 0, 0, ...
		 *		rho2 = 0, 0, 0, ...
		 *		theta2 = 0, 0, 0, ...
		 *		phi2 = 0, 0, 0, ...
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
