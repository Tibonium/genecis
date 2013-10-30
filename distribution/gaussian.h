/**
 * @file gaussian.h
 */

#ifndef DISTRIBUTION_GAUSSIAN_H
#define DISTRIBUTION_GAUSSIAN_H

//namespace distribution {

class gaussian : public probability_density_function
{
	private:
	
		double _mu ;
		double _sigma ;
		double _dx ;
		
		double reimann_sum(double _a, double _b) {
			double _exponent ;
			double _value = 0.0 ;
			_a += _dx / 2.0 ;
			while( _a < _b ) {
				_exponent = -( (_a - _mu)*(_a - _mu) ) /
							( 2.0 * _sigma * _sigma ) ;
				_value += exp(_exponent) * _dx ;
				_a += _dx ;
			}
			_value /= ( _sigma * sqrt(TWO_PI) ) ;
			return _value ;
		}
		
	public:
	
		virtual double probability(double a, double b) {
			double _result = reimann_sum(a,b) ;
			return _result ;
		}

		///constructor
		gaussian(double mu, double sigma, double dx) :
		_mu(mu), _sigma(sigma), _dx(dx) {}
	
};

//} ///end of namespace distribution

#endif
