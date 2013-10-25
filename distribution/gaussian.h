/**
 * @file gaussian.h
 */

#ifndef DISTRIBUTION_GAUSSIAN_H
#define DISTRIBUTION_GAUSSIAN_H

#include "distribution_model.h"

//namespace distribution {

class gaussian : public distribution_model
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
