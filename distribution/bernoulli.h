/**
 * @file bernoulli.h
 */
 
#ifndef GENECIS_DISTRIBUTION_BERNOULLI_H
#define GENECIS_DISTRIBUTION_BERNOULLI_H

/**
 * The Bernoulli distribution is a discrete
 * probability distribution, which takes a value
 * of true with success probability p and value
 * of false with failure probability q=1-p.
 */

namespace genecis {
namespace distribution {

class bernoulli : public probability_mass_function<double, bool>
{

	private:
		
		double _success ;
	
	public:
	
		virtual bool probability(double chance) {
			if (chance <= _success) {return true ;}
			else {return false ;}
		}
		
		bernoulli(double success) : _success(success) {}

};

}	// end of namespace distribution
}	// end of namespace genecis

#endif
