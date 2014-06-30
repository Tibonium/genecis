/**
 * @file uniform.h
 */
 
#ifndef GENECIS_DISTRIBUTION_UNIFORM_H
#define GENECIS_DISTRIBUTION_UNIFORM_H

/**
 * The continuous uniform distribution or rectangular
 * distribution is a family of symmetric probability
 * distributions such that for each member of the family,
 * all intervals of the same length on the distribution's
 * support are equally probable. The support is defined by
 * the two parameters, a and b, which are its minimum and
 * maximum values.
 */

class uniform : public probability_density_function<double>
{

	private:
	
		double _lower ;
		double _upper ;
		double _norm ;
		double _a, _b ;
		double _result ;

	public:
	
		virtual double probability(double a, double b) {
			_a = min( _upper, max(a, _lower) ) ;
			_b = max( _lower, min(b, _upper) ) ;
			_result = ( _b - _a ) * _norm ;
			return _result ;
		}

		///constructor
		uniform( double lower, double upper ) :
		_lower(lower), _upper(upper) {
			_norm = 1.0 / ( _upper - _lower ) ;
		}

};

#endif
