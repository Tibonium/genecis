/**
 * @file poisson.h
 */
 
#ifndef GENECIS_DISTRIBUTION_POISSON_H
#define GENECIS_DISTRIBUTION_POISSON_H

/**
 * The Poisson distribution named after French
 * mathematician Siméon Denis Poisson, is a discrete
 * probability distribution that expresses the
 * probability of a given number of events occurring
 * in a fixed interval of time and/or space if these
 * events occur with a known average rate and
 * independently of the time since the last event.
 */

namespace genecis {
namespace distribution {

class poisson : public probability_mass_function<int, double>
{

	private :
	
		double _lambda  ;
	
	public :

		virtual double probability(int k) {
			unsigned k_fact = 1;
			if (k > 0.0) {
				for(int i=2; i<k+1; ++i) {
					k_fact *= i ;
				}
			}
			double _result = ( pow(_lambda, k) * exp(-_lambda) ) / k_fact ;
			return _result ;
		}
	
		// Constructor
		poisson(double lambda) {
			if(lambda <= 0.0) {
				cout << "lambda must be greater then zero, lambda: "
					<< lambda << endl;
			} else { _lambda = lambda ;}
		}
		
		// Destructor
		virtual ~poisson() {}

};

}	// end of namespace distribution
}	// end of namespace genecis

#endif
