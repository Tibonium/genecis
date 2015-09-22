/**
 * @file binomial.h
 */
 
#pragma once

#include <genecis/math/math_functions.h>
 
BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(probability)

/**
 * In probability theory and statistics, the binomial distribution with
 * parameters n and p is the discrete probability distribution of the
 * number of successes in a sequence of n independent yes/no experiments,
 * each of which yields success with probability p. A success/failure
 * experiment is also called a Bernoulli experiment or Bernoulli trial;
 * when n = 1, the binomial distribution is a Bernoulli distribution.
 * The binomial distribution is the basis for the popular binomial
 * test of statistical significance.
 */
struct binomial {
public:

	typedef double			probability_type ;
	typedef std::size_t		count_type ;
	
	static probability_type pmf(count_type n, count_type k, probability_type p)
	{
		return genecis::math::choose(n, k)*std::pow(p, k)*std::pow((1-p), (n-k)) ;
	}

};

END_NAMESPACE
END_NAMESPACE
