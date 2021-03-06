/**
 *	@file priority_queue.h
 */

#pragma once

#include <genecis/container/array.h>
#include <cstring>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace genecis::container ;

namespace genecis {
namespace tree {

	using namespace std ;

	template<class T> class priority_queue ;

	template<class T>
	ostream& operator<< ( ostream& os, const priority_queue<T>& output ) ;

	template<class T>
	class priority_queue {

		public:

            typedef T                               value_type ;
            typedef std::size_t                     size_type ;
            typedef priority_queue<value_type>      self_type ;
            typedef array<size_type>                rank_container ;
	
			/**
			 * Constructor, takes a size of array and sets all member
			 * variables, and allocates memory for the _rank and _data
			 * array as well as initializing them all to a value of 0.
			 */
			priority_queue( const size_type size ) : 
			    _rank(size, 0), _front(0), _back(0),
				_max_index(size-1)
			{
				_data = new value_type[size] ;
				if( typeid(value_type) == typeid(string) ) {
					for(unsigned i=0; i<size; ++i) {
						_data[i] = "" ;
					}
				} else {
					memset(_data, 0, size*sizeof(T)) ;
				}
			}
		
			/**
			 * Destructor, cleans up the _rank and _data points if they
			 * have not been already.
			 */
			virtual ~priority_queue() {
			    delete[] _data ;
			}

			/*=================== Public Accessors ===================*/
			/**
			 * Returns a data entry via a lookup of a value_type
			 */
			value_type data( value_type d) const {
				return _data[d] ;
			}
		
		    /**
		     * Returns a data entry via a lookup of an index
		     */
			value_type data( size_type i ) const {
				return _data[i] ;
			}

            /**
             * Overloaded [] operator specific to this class
             */
			value_type operator[] ( value_type d ) const {
				size_type start = _front ;
				bool found = false ;
				while( start != _back ) {
					size_type bytes = max( sizeof(_data[start]), sizeof(d) ) ;
					size_type check = memcmp( _data[start], d, bytes ) ;
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
					cout << "priority_queue::operator[] (const T&) "
						 << "data value " << d << " not found. exit status"
						 << " (" << e << ")" << endl ;
				}
			}

			/**
			 * Pushes a new data value onto the back of the queue and
			 * sets its' priority to the default rank of 16.
			 */
			void push_back( value_type data ) {
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
			void push_back( value_type data, size_type rank ) {
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
		
		    /**
		     * Pops from the front
		     */
			value_type pop_front() {
				try {
					if( _rank[_front] == 0 ) {
						throw 1 ;
					} else {
						value_type d = _data[_front] ;
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
		    
		    /**
		     * Finds the top ranked value.
		     */
			value_type pop_top_rank() {
				try{
					if( _rank[_front] == 0 ) {
						throw 1 ;
					} else {
						size_type s = _front ;
						size_type t = 0 ;
						size_type rh = _rank[s] ;
						++s ;
						size_type rl = _rank[s] ;
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
						value_type d = _data[t] ;
						return d ;
					}
				} catch(int e) {
					cout << "priority_queue::pop_top_rank(): queue is"
						 << " empty. exit status(" << e << ")" << endl ;
					exit(e) ;
				}
			}

    		friend ostream& operator<< <> (ostream& os, const priority_queue& output) ;
	
		private:
		
			rank_container _rank ;		//array to store priority values in
			value_type* _data ;		//actual data values in queue
			size_type _front ;		//highest prioirty
			size_type _back ;		//lowest priority
			size_type _max_index ;	//maximum number of queue elements

	};

	template <class T>
	inline ostream& operator<< (ostream& os, const priority_queue<T>& output) {
		char buf[64] ;
		stringstream ss ;
		string s ;
		os << "    Data    Rank" << endl ;
		if( typeid(T) == typeid(string) ) {
			for(size_t i=0; i<=output._max_index; ++i) {
				s = output._data[i] ;
				if( s == "" ) s = "empty" ;
				int l = s.size() ;
				if( l > 1 ) l -= ceil((double)l/2.0) ;
				sprintf(buf, "| %*s %*d   |", (8-l), s.c_str(), (5+l), (int)output._rank[i]) ;
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
				sprintf(buf, "| %*s %*u  |", (8-l), (ss.str()).c_str(), (7+l), (int)output._rank[i]) ;
				os << buf ;
				if( i == output._front && i == output._back ) os << " (front/back)" << endl ;
				else if( i == output._front ) os << " (front)" << endl ;
				else if( i == output._back ) os << " (back)" << endl ;
				else os << endl ;
			}	
		}
		sprintf(buf, "front:%3u back:%3u\n   max_index:%3u", 
				(int)output._front, (int)output._back, (int)output._max_index) ;
		os << buf << endl ;
		return os ;
	}

}	// end of namespace tree
}	// end of namespace genecis
