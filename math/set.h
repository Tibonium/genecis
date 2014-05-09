/**
 * @file set.h
 * A class that allows the creation of an abstract set to which
 * various set operations can be performed on.
 */

#ifndef MATH_SET_H
#define MATH_SET_H

#include <iostream>
#include <cstdio>

template<class _T> class set ;

template<class _T> std::ostream&
operator<< (std::ostream& os, set<_T>& output) ;

template<class _T>
class set {

	public:
	
		inline _T& operator[] (unsigned i) const {
			return pSet[i] ;
		}
	
		/**
		 *	Constructor
		 *	Takes a pointer to a "set"
		 */
		set(_T* s) : pSet(s) {}
		
		// Destructor
		~set() {}

		friend std::ostream& operator<< <> (std::ostream& os, set& output) ;
			
	private:
		
		// List or set that allows manipulation of its elements
		_T* pSet ;

};

template<class _T>
inline std::ostream& operator<< (std::ostream& os, set<_T>& output) {
	os << output ;
	return os ;
} 

#endif
