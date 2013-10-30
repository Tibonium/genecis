/**
 * @file poisson.h
 */
 
#ifndef DISTRIBUTION_POISSON_H
#define DISTRIBUTION_POISSON_H

class poisson : public probability_mass_function {

	private :
	
		double _lambda  ;
	
	public :

		virtual double probability(double k) {
			unsigned k_fact = 1;
			if (k > 0.0) {
				for(unsigned i=2; i<k+1; ++i) {
					k_fact *= i ;
				}
			}
			double _result = ( pow(_lambda, k) * exp(-_lambda) ) / k_fact ;
			return _result ;
		}
	
		///constructor
		poisson(double lambda) {
			if(lambda <= 0.0) {
				cout << "lambda must be greater then zero, lambda: "
					<< lambda << endl;
			} else { _lambda = lambda ;}
		}

};

#endif
