/**
 * @file gaussian.h
 */

#ifndef GENECIS_DISTRIBUTION_GAUSSIAN_H
#define GENECIS_DISTRIBUTION_GAUSSIAN_H

/**
 * The normal (or Gaussian) distribution is a continuous
 * probability distribution—a function that tells the
 * probability of a number in some context falling between
 * any two real numbers.
 */

class gaussian : public probability_density_function<double>
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
		
		/**
		 * Overloading of various operators
		 */
		bool operator==(const gaussian& rhs) const {
			if( (this->_mu == rhs._mu) &&
			    (this->_sigma == rhs._sigma) )
			{
				return true ;
			} else {
				return false ;
			}
		}
		
		bool operator!= (const gaussian& rhs) const {
			return !(*this == rhs) ;
		}
		
		inline gaussian& operator= (const gaussian& rhs) {
			this->_mu = rhs._mu ;
			this->_sigma = rhs._sigma ;
			this->_dx = rhs._dx ;
			return *this ;
		}
		
		friend std::ostream& operator<< (std::ostream& out, const gaussian& other) ;

		/// Constructor
		gaussian(double mu, double sigma, double dx) :
		_mu(mu), _sigma(sigma), _dx(dx) {}
	
};

inline std::ostream& operator<< (std::ostream& os, const gaussian& other) {
	os << "***Gaussian Distribution***\n"
	   << "*  Mean: " << other._mu << "\t\t  *\n"
	   << "*  Standard Dev: " << other._sigma << "\t  *\n"
	   << "*  Delta x: " << other._dx << "\t  *\n"
	   << "***************************" ;
	return os ;
}

//} ///end of namespace distribution

#endif
