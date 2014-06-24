/**
 * @file gravity.cc
 */
 
#include "gravity.h"

gravity::gravity( double mass1, double mass2, double dt,
				  svector* pos1, svector* pos2,
				  svector* vel1, svector* vel2,
				  svector* acc1, svector* acc2 ) :
	_m1(mass1),
	_m2(mass2),
	_dt(dt),
	_p1(pos1),
	_p2(pos2),
	_v1(vel1),
	_v2(vel2),
	_a1(acc1),
	_a2(acc2),
	_time(0.0)
{

}

void gravity::step() {

	svector* r12 = _pos2 - _pos1 ;
	double mag12 = r_12.magnitude() ;
	r12.norm() ;
	svector* f12 = r12 * (-(_G*_m1*_m2) / mag12) ;
	svector f21 = f12 ;
	f21 * (-1.0) ;
	_a1 = f12 / _m1 ;
	_a2 = f21 / _m2 ;

}
