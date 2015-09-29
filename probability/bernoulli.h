/**
 * @file bernoulli.h
 */
 
#pragma once

#include <genecis/probability/number_generator.h>
 
BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(probability)

/**
 * A Bernoulli distribution is a binary distrubution with
 * where success is when below a threshold.
 */
class bernoulli {
public:

	/**
	 * Constructor
	 *
	 * @param p		probability threshold (percent chance)
	 */	
	bernoulli( double p ) :
		__p( p )
	{}
	
	/**
	 * Destructor
	 */
	virtual ~bernoulli() {}
	
	/**
	 * Probability function
	 */
	bool trial()
	{
		return ( std::rand() < __p) ;
	}
	
	/**
	 * Resets the probability of success to a new threshold value
	 */
	void reset(double p)
	{
		__p = p ;
	}
	
private:

	double __p ;

};

END_NAMESPACE
END_NAMESPACE
