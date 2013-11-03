/**
 * @file pointers.h
 *
 * Basic header that has multiple functions
 * but only one is called at construction. Upon
 * construction the pointer to the correct 
 * function should be called.
 */
 
#ifndef POINTERS_H
#define POINTERS_H

#include <iostream>

using namespace std ;
 
class pointers {

	protected:
		double(*func_ptr) (double) ;
		
		/**
		 * Prints a number
		 */
		double printer(double _num) {
			cout << "The number is " << _num << endl ;
			return 0 ;
		}
		
		/**
		 * Calculate and print factorial
		 */
		double factorial(double _num) {
			if(_num>1) {
				int value = 1;
				for(int i=1; i<(int)_num; ++i) {
					value *= i ;
				}
			} else {
				cout << "Cannot calculate factorial of "
				<< _num << endl ;
			}
			
			return 0 ;
		}
		
	public:

		double function_caller(double _num) {
			func_ptr(_num) ;
			return 0 ;
		}

		/**
		 * Constructor
		 */
		pointers( double(*_function) (double) ) {
			func_ptr = _function ;
		}

};

#endif
