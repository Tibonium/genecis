/**
 * @file uniform.h
 */
 
#ifndef DISTRIBUTION_UNIFORM_H
#define DISTRIBUTION_UNIFORM_H

class uniform : public probability_density_function {

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
