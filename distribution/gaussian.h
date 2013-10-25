/**
 * @file gaussian.h
 */

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "integrate.h"

//namespace distribution {

class gaussian : public integrate
{
	private:
	
		double _mu ;
		double _sigma ;
		
	public:
	
		virtual double integrate(double a, double b) {
			return TWO_PI ;
		}

		///constructor
		gaussian(double mu, double sigma) :
		_mu(mu), _sigma(sigma) {}
	
};

//} ///end of namespace distribution

#endif
