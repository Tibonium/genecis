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

template<class _T> class set ;

template<class _T> std::ostream&
operator<< (std::ostream& os, set<_T>& output) ;

template<class _T>
class set {

	public:
	
		inline size_t size() {
			return m_size ;
		}
	
		inline _T& operator[] (unsigned i) const {
			return pSet[i] ;
		}
		
		inline set unite(set& other) {
			std::vector<_T> temp ;
			for(size_t i=0; i<m_size; ++i) {
				temp.push_back( (*this)[i] ) ;
			}
			for(size_t i=0; i<other.m_size; ++i) {
				temp.push_back( other[i] ) ;
			}
			int N = temp.size() ;
			_T* S = new _T[N] ;
			int j = 0 ;
			for(typename std::vector<_T>::iterator i=temp.begin();
					i!=temp.end(); ++i)
			{
				S[j] = (*i) ;
				++j ;
			}
			return set<_T>(S, N) ;
		}
		
		inline set intersect(set& other) {
			std::vector<_T> temp ;
			for(size_t i=0; i<m_size; ++i) {
				for(size_t j=0; j<other.m_size; ++j) {
					_T l = (*this)[i] ;
					_T r = other[j] ;
					if( l == r ) {
						temp.push_back( r ) ;
					}
				}
			}
			int N = temp.size() ;
			_T* S = new _T[N] ;
			int j = 0 ;
			for(typename std::vector<_T>::iterator i=temp.begin();
					i!=temp.end(); ++i)
			{
				S[j] = (*i) ;
				++j ;
			}
			return set<_T>(S, N) ;
		}
		
		inline set operator- (set& rhs) {
			std::vector<_T> temp ;
			bool b_annihilate ;
			for(size_t i=0; i<m_size; ++i) {
				_T l = (*this)[i] ;
				b_annihilate = false ;
				for(size_t j=0; j<rhs.m_size; ++j) {
					_T r = rhs[j] ;
					if( l == r ) {
						b_annihilate = true ;
						break ;
					}
				}
				if( !b_annihilate ) temp.push_back( l ) ;
			}
			int N = temp.size() ;
			_T* S = new _T[N] ;
			int j = 0 ;
			for(typename std::vector<_T>::iterator i=temp.begin();
					i!=temp.end(); ++i)
			{
				S[j] = (*i) ;
				++j ;
			}
			return set<_T>(S, N) ;
		}
	
		/**
		 *	Constructor
		 *	Takes a pointer to a "set"
		 */
		set(_T* s, size_t size) : pSet(s), m_size(size) {}
		
		// Destructor
		~set() {}

		friend std::ostream& operator<< <> (std::ostream& os, set& output) ;
			
	private:
		
		// List or set that allows manipulation of its elements
		_T* pSet ;
		size_t m_size ;

};

template<class _T>
inline std::ostream& operator<< (std::ostream& os, set<_T>& output) {
	os << output ;
	return os ;
} 

#endif
