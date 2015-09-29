/**
 * @file number_generator.h
 */
#pragma once

#include <cstring>
#include <ctime>
#include <cassert>

#include <genecis/base/genecis_defines.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(probability)

class number_generator {
public:

	/**
	 * Constructor
	 */
	number_generator() {}
	
	/**
	 * Destructor
	 */
	virtual ~number_generator() {}
	
	/**
	 * Seeds the random number generator. If the seed
	 * is -1, then the seed uses the current time, otherwise
	 * the number generator is seeded with s.
	 *
	 * @param s		random number generator seed
	 */
	static void seed(int s=0)
	{
		if( s < 0 ) {
			std::srand( std::time(0) ) ;
		} else {
			std::srand(s) ;
		}
	}
	
	/**
	 * Returns a double between [0, 1]
	 */
	static double unit()
	{
		return (double)std::rand() / RAND_MAX ;
	}
	
	/**
	 * Returns an integer between [0, RAND_MAX]
	 */
	static int rinteger()
	{
		return std::rand() ;
	}
	
	/**
	 * Returns a double between [a, b]
	 */
	static double uniform(int a, int b)
	{
		assert( a < b ) ;
		return ((b-a)*unit() + a) ;
	}

private:

};

END_NAMESPACE
END_NAMESPACE
