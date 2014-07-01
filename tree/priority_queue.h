/**
 *	@file priority_queue.h
 */

#ifndef GENECIS_TREE_PRIORITY_QUEUE_H
#define GENECIS_TREE_PRIORITY_QUEUE_H

#include <cstring>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <typeinfo>

namespace genecis {
namespace tree {

using namespace std ;

template <class TYPE> class priority_queue ;

template <class TYPE>
ostream& operator<< (ostream& os, const priority_queue<TYPE>& output) ;

template <class TYPE> class priority_queue {

	typedef priority_queue<TYPE> self_type ;

	public:
	
		/*=================== Public Accessors ===================*/
		inline const TYPE& data(const TYPE& d) {
			return _data[d] ;
		}
		
		inline const TYPE& data(const size_t& i) {
			return _data[i] ;
		}

		inline const TYPE& operator[] (const TYPE& d) {
			size_t start = _front ;
			bool found = false ;
			while( start != _back ) {
				size_t bytes = max( sizeof(_data[start]), sizeof(d) ) ;
				int check = memcmp(_data[start], d, bytes) ;
				if( check == 0 ) found = true ; break ;
				++ start ;
				if( start > _max_index ) start = 0 ;
			}
			try {
				if( found ) {
					return _data[start] ;
				} else {
					throw 1 ;
				}
			} catch (int e) {
				cout << "priority_queue::operator[] (const TYPE&) "
					 << "data value " << d << " not found. exit status"
					 << " (" << e << ")" << endl ;
			}
		}

		/**
		 * Pushes a new data value onto the back of the queue and
		 * sets its' priority to the default rank of 16.
		 */
		inline void push_back(const TYPE& data) {
			try {
				if( _front == _back && _rank[_front] != 0 ) {
					throw 1 ;
				} else {
					_data[_back] = data ;
					_rank[_back] = 16 ;
					++_back ;
					if( _back > _max_index ) {
						_back = 0 ;
					}
				}
			} catch (int e) {
				cout << "priority_queue::push_back(const T&) exit "
					 << "status(" << e << "), queue is full."
					 << endl ;
				exit(e) ;
			}
		}

		/**
		 * Pushes a new data/rank pair onto the back of the queue.
		 */
		inline void push_back(const TYPE& data, const int& rank) {
			try {
				if( _front == _back && _rank[_front] != 0 ) {
					throw 1 ;
				} else {
					_data[_back] = data ;
					_rank[_back] = rank ;
					++_back ;
					if( _back > _max_index ) {
						_back = 0 ;
					}
				}
			} catch (int e) {
				cout << "priority_queue::push_back(const T&, const int&)"
					 << " exit status(" << e << "), queue is full."
					 << endl ;
				exit(e) ;
			}
		}
		
		inline const TYPE& pop_front() {
			try {
				if( _rank[_front] == 0 ) {
					throw 1 ;
				} else {
					TYPE& d = _data[_front] ;
					_rank[_front] = 0 ;
					while( _rank[_front] == 0 ) {
						++_front ;
						if( _front > _max_index ) _front = 0 ;
						if( _front == _back && _rank[_front] == 0 ) break ;
					}
					return d ;
				}
			} catch(int e) {
				cout << "priority_queue::pop_front() queue is empty."
					 << " exit status (" << e << ")" << endl ;
				exit(e) ;
			}
		}
		
		inline const TYPE& pop_top_rank() {
			try{
				if( _rank[_front] == 0 ) {
					throw 1 ;
				} else {
					size_t s = _front ;
					size_t t = 0 ;
					size_t rh = _rank[s] ;
					++s ;
					size_t rl = _rank[s] ;
					while( s != _front ) {
						if( rl > rh ) { rh = rl ; t = s ; }
						++s ;
						if( s > _max_index ) s = 0 ;
						rl = _rank[s] ;
					}
					_rank[t] = 0 ;
					if( t == _front ) {
						++_front ;
						if( _front > _max_index ) _front = 0 ;
					} else if( t == _back ) {
						if( _back == 0 ) _back = _max_index ;
						else --_back ;
					} else _back = t ;
					TYPE& d = _data[t] ;
					return d ;
				}
			} catch(int e) {
				cout << "priority_queue::pop_top_rank(): queue is"
					 << " empty. exit status(" << e << ")" << endl ;
				exit(e) ;
			}
		}

		/**
		 * Constructor, takes a size of array and sets all member
		 * variables, and allocates memory for the _rank and _data
		 * array as well as initializing them all to a value of 0.
		 */
		priority_queue(const size_t& size) : _front(0), _back(0),
			_max_index(size-1)
		{
			_rank = new int[size] ;
			_data = new TYPE[size] ;
			memset(_rank, 0, size*sizeof(int)) ;
			if( typeid(TYPE) == typeid(string) ) {
				for(unsigned i=0; i<size; ++i) {
					_data[i] = "" ;
				}
			} else {
				memset(_data, 0, size*sizeof(TYPE)) ;
			}
		}
		
		/**
		 * Destructor, cleans up the _rank and _data points if they
		 * have not been already.
		 */
		~priority_queue() {
			_front = 0 ;
			_back = 0 ;
			_max_index = 0 ;
			delete[] _data ;
			delete[] _rank ;
		}
		
	friend ostream& operator<< <> (ostream& os, const priority_queue& output) ;
	
	private:
		int* _rank ;		//array to store priority values in
		TYPE* _data ;		//actual data values in queue
		size_t _front ;		//highest prioirty
		size_t _back ;		//lowest priority
		size_t _max_index ;	//maximum number of queue elements

};

template <class TYPE>
inline ostream& operator<< (ostream& os, const priority_queue<TYPE>& output) {
	char buf[64] ;
	stringstream ss ;
	string s ;
	os << "    Data    Rank" << endl ;
	if( typeid(TYPE) == typeid(string) ) {
		for(size_t i=0; i<=output._max_index; ++i) {
			s = output._data[i] ;
			if( s == "" ) s = "empty" ;
			int l = s.size() ;
			if( l > 1 ) l -= ceil((double)l/2.0) ;
			sprintf(buf, "| %*s %*d   |", (8-l), s.c_str(), (5+l), output._rank[i]) ;
			os << buf ;
			if( i == output._front && i == output._back ) os << " (front/back)" << endl ;
			else if( i == output._front ) os << " (front)" << endl ;
			else if( i == output._back ) os << " (back)" << endl ;
			else os << endl ;
		}
	} else {
		for(size_t i=0; i<=output._max_index; ++i) {
			ss.str("") ;
			ss << output._data[i] ;
			int l = (ss.str()).size() ;
			if( l > 1 ) l -= ceil((double)l/2.0) ;
			sprintf(buf, "| %*s %*d  |", (8-l), (ss.str()).c_str(), (7+l), output._rank[i]) ;
			os << buf ;
			if( i == output._front && i == output._back ) os << " (front/back)" << endl ;
			else if( i == output._front ) os << " (front)" << endl ;
			else if( i == output._back ) os << " (back)" << endl ;
			else os << endl ;
		}	
	}
	sprintf(buf, "front:%3d back:%3d\n   max_index:%3d", 
			output._front, output._back, output._max_index) ;
	os << buf << endl ;
	return os ;
}

}	// end of namespace tree
}	// end of namespace genecis

#endif
