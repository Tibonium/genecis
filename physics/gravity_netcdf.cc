/**
 * @file gravity_netcdf.cc
 */

#include <genecis/phsyics/gravity.h>

using namespace genecis::physics ;

/**
 * Initialize netCDF file for recording data
 */
void gravity::init_netcdf( const char* filename,
	const char* long_name )
{
	_nc_file = new NcFile( filename, NcFile::Replace );
	_nc_rec = 0 ;
	if ( long_name ) {
		_nc_file->add_att("long_name", long_name ) ;
	}

	// dimensions
	NcDim* time_dim = _nc_file->add_dim( "travel_time" ) ;
	
	// coordinates
	_nc_time = _nc_file->add_var( "travel_time", ncDouble, time_dim ) ;
	_nc_pos1 = _nc_file->add_var( "Object1 location", ncDouble, 
		time_dim, time_dim, time_dim ) ;
	_nc_pos2 = _nc_file->add_var( "Object2 location", ncDouble,
		time_dim, time_dim, time_dim ) ;
	
	// attributes
	_nc_time->add_att("units","days") ;
	_nc_pos1->add_att("units","rho,thata,phi") ;
	_nc_pos1->add_att("positive","out,up,clockwise") ;
	_nc_pos2->add_att("units","rho,thata,phi") ;
	_nc_pos2->add_att("positive","out,up,clockwise") ;
}

/**
 * Writes the time and position of both bodies to
 * the netCDF log
 */
void gravity::save_netcdf() {
	NcError( verbose_nonfatal ) ;
	_nc_time->put_rec( &_time, _nc_rec ) ;
	_nc_pos1->put_rec( "position1 data", _nc_rec ) ;	// need to figure out how to do this
	_nc_pos2->put_rec( "position2 data", _nc_rec ) ;	// need to figure out how to do this
	++_nc_rec ;
}

/**
 * Closes the netCDF log file
 */
void gravity::close_netcdf() {
	delete _nc_file ;
	_nc_file = NULL ;
}
