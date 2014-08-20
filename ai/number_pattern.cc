/**
 * @file number_pattern.cc
 */

#include <genecis/ai/number_pattern.h>

using namespace genecis::ai ;

/**
 * Attempts to find a elementry answer guess to the set that
 * was provided. Only algebraic operations are currently
 * available to predict a partten in the set.
 */
void number_pattern::find_pattern( int* set, int size ) {
	_set = set ;
	_size = size ;
	if( linear() ) make_guess( LINEAR ) ;
	else if( multiplicative() ) make_guess( MULTIPLE ) ;
	else if( power() ) make_guess( POWER ) ;
	else make_guess( UNKNOWN ) ;
}

/**
 * Tests to see if a common difference exists in the set
 */
bool number_pattern::linear() {
	c = _set[1] - _set[0] ;
	for(int i=2; i<_size; ++i) {
		if( (_set[i] - _set[i-1]) != c ) return false ;
	}
	return true ;
}

/**
 * Tests to see if a common multiple exists in the set
 */
bool number_pattern::multiplicative() {
	m = _set[1] / (double)_set[0] ;
	for(int i=2; i<_size; ++i) {
		if( m*_set[i-1] != _set[i] ) return false ;
	}
	return true ;
}

/**
 * Tests to see if a common power exists in the set
 */
bool number_pattern::power() {
	p = 1 ;
	find_power( p ) ;
	for(int i=0; i<_size; ++i) {
		double g = pow( _set[i], 1.0 / p ) ;
		if( g != (int)g ) return false ;
	}
	return true ;
}

/**
 * Brute force approach attempt to find a power of the
 * third element in the set.
 */
void number_pattern::find_power( int& x ) {
	int i = 2 ;
	while( i<10 ) {
		double g = pow( _set[2], 1.0 / i ) ;
		if( g == (int)g ) ++i ;
		else { x = --i ; break ; }
	}
}

/**
 * Makes a guess based on the attempts to find a pattern
 */
void number_pattern::make_guess( pattern_type guess ) {
	switch(guess) {
		case LINEAR:
			cout << "My guess for the next number is "
				 << (_set[_size-1]+c) << endl ;
			break ;
		case MULTIPLE:
			cout << "My guess for the next number is "
				 << (m*_set[_size-1]) << endl ;
			break ;
		case POWER:
			cout << "My guess for the next number is "
				 << pow( _size+1, p ) << endl ;
			break ;
		default:
			cout << "I'm not really sure what the next number is."
				 << endl ;
//					best_guess() ;
			break ;
	}
}
