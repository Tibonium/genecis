/**
 * @file set.h
 * A class that allows the creation of an abstract set to which
 * various set operations can be performed on.
 */

#ifndef MATH_SET_H
#define MATH_SET_H

#include <iostream>
#include <cstdio>
#include <vector>
#include "matrix.h"

template<class _T> class set ;

template<class _T> std::ostream&
operator<< (std::ostream& os, set<_T>& output) ;

template<class _T>
class set {

	public:
	
		inline _T& operator[] (unsigned i) const {
			return pSet[i] ;
		}
		
//		inline void operator= (_T rhs) {
//			
//		}
	
		/**
		 *	Constructor
		 *	Takes a pointer to a "set"
		 */
		set(_T* s) : pSet(s) {}
		
		/**
		 *	Constructor
		 *	Specialized constructor for vectors
		 */
		set(std::vector<_T>* s) {
			pSet = new _T[s->size()] ;
			int n = 0 ;
			for(class std::vector<_T>::iterator i=s->begin(); i!=s->end(); ++i) {
				pSet[n] = (*i) ;
				++n ;
			}
		}
		
		// Destructor
		~set() {
			if(pSet) {
				delete pSet ;
				pSet = NULL ;
			}
		}

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
