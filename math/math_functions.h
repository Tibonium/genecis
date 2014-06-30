/**
 * @file math_functions.h
 */
 
#ifndef GENECIS_MATH_MATH_FUNCTIONS_H
#define GENECIS_MATH_MATH_FUNCTIONS_H

class math_functions {

	public:
	
		template <typename _T>
		void convolve(_T& _u, _T& _v, _T& result) ;
	
		// Constructor
		math_functions() {}
		
		// Destructor
		~math_functions() {}

};

#endif
