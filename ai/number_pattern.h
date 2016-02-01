/**
 * @file number_pattern.h
 */
#pragma once

#include <iostream>
#include <cmath>
#include <genecis/base/genecis_defines.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(ai)

using namespace std ;

class number_pattern {

enum pattern_type { LINEAR, MULTIPLE, POWER, UNKNOWN } ;

public:

	number_pattern() {}

	virtual ~number_pattern() {}
	
	/**
	 * Attempts to find a elementry answer guess to the set that
	 * was provided. Only algebraic operations are currently
	 * available to predict a partten in the set. If a pattern
	 * is detected, the class will produce a guess. Makes a local
	 * copy of the set, but does not keep it.
	 *
	 * @param set		Set to make a guess at the next element
	 */
	void find_pattern( int* set, int size ) ;
	
private:

	int c ;
	double m ;
	int p ;
	int _size ;
	int* _set ;

	/**
	 * Tests to see if a common difference exists in the set
	 */
	bool linear() ;

	/**
	 * Tests to see if a common multiple exists in the set
	 */
	bool multiplicative() ;

	/**
	 * Tests to see if a common power exists in the set
	 */
	bool power() ;

	/**
	 * Brute force approach attempt to find a power of the
	 * third element in the set.
	 */
	void find_power( int& x ) ;

	/**
	 * Makes a guess based on the attempts to find a pattern
	 */
	void make_guess( pattern_type guess ) ;

	/**
	 * Make a best guess if nothing else
	 */
	void best_guess() {}

};

END_NAMESPACE
END_NAMESPACE
