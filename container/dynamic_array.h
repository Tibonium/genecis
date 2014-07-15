/**
 * @file dynamic_array.h
 */

#ifndef GENECIS_CONTAINER_DYNAMIC_ARRAY
#define GENECIS_CONTAINER_DYNAMIC_ARRAY

#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>

namespace genecis {
namespace container {

using namespace std ;

template<typename T>
class dynamic_array {

	public:
		/**
		 * Constructor with specified size.
		 * @param size		size of array to be allocated
		 */
		dynamic_array(int size) : _size(size) {
			try {
				if ( _size <= 0 ) {
					throw 1 ;
				} else {
					_data = new T[size] ;
					memset(_data,0,size*sizeof(T)) ;
				}
			} catch (int e) {
				cout << "Cannot initialize array of size zero or with"
					 << " a negative size." << endl ;
				exit(e) ;
			}
		}
		
		/**
		 * Default constructor, intializes array size to default_size
		 */
		dynamic_array() : _size(DEFAULT_SIZE) {
			_data = new T[_size] ;
			memset(_data,0,_size*sizeof(T)) ;
		}
		
		/**
		 * Copy constructor
		 */
		dynamic_array(dynamic_array const& other) {
			_size = other.size() ;
			_data = new T[_size] ;
			memcpy(_data,other.data(),_size*sizeof(T)) ;
		}

		/**
		 * Destructor
		 */
		virtual ~dynamic_array() {
			if( _data ) {
				delete[] _data ;
				_data = NULL ;
			}
		}

		/**
		 * Returns the maximum capacity of the data array.
		 */
		inline int size() const {
			return _size ;
		}
		
		/**
		 * Returns a pointer to the data array of the class.
		 */
		inline T* data() const {
			return _data ;
		}
		
		/**
		 * Returns a string of the array in the format of:
		 * [ e1, e2, e3, ... ]
		 */
		string str() const {
			string s = "[ " ;
			for(int i=0; i<_size; ++i) {
				ostringstream o ;
				if ( i != 0 ) s += ", " ;
				o << _data[i] ;
				s += o.str() ;
			}
			s += " ]" ;
			return s ;
		}

		/** ===== Array Operators ===== **/

		/**
		 * Concatenates two dynamic arrays and passes back a new
		 * dynamic array.
		 */
		dynamic_array* operator+(dynamic_array const& rhs) const {
			int temp_size = _size + rhs.size() ;
			dynamic_array<T>* temp = new dynamic_array<T>(temp_size) ;
			for(int i=0; i<_size; ++i) {
				temp->data[i] = _data[i] ; 
			}
			for(int i=_size; i<rhs.size(); ++i) {
				temp->data[i] = rhs.data[i] ;
			}
			return temp ;
		}
		
		/**
		 * Concatenates this array with the rhs into this array.
		 */
		inline void operator+=(dynamic_array const& rhs) {
			int temp_size = _size + rhs.size() ;
			dynamic_array<T>* temp = new dynamic_array<T>(temp_size) ;
			for(int i=0; i<_size; ++i) {
				temp->data[i] = _data[i] ; 
			}
			for(int i=_size; i<rhs.size(); ++i) {
				temp->data[i] = rhs.data[i] ;
			}
			delete[] _data ;
			_size = temp_size ;
			_data = temp->data() ;
		}
		
		/**
		 * Class assignment operator
		 */
		inline void operator=(dynamic_array const& rhs) {
			delete[] _data ;
			_size = rhs.size() ;
			_data = new T[_size] ;
			memcpy(_data,rhs.data(),_size*sizeof(T)) ;
		}
		
		/**
		 * Array accessor
		 * If index is out of bounds, the array with do one of two
		 * things:
		 *	1. If index is positive, _data will be expanded to that size
		 *	2. If index is negative, _data will be accessed from the end
		 *	   in reverse order.
		 */
		inline T& operator() (int index) {
			if( index > _size-1 ) {
				resize(index+1) ;
			} else if ( index < 0 ) {
				index += _size ;
			}
			return _data[index] ;
		}
		
		/**
		 * Array assignment operator
		 */
		template<int _index>
		inline void operator= (T c) {
			_data[_index] = c ;
		}

	private:
		/**
		 * Default array size for default constructor
		 */
		static const int DEFAULT_SIZE = 5 ;

		/**
		 * Maximum size of the array
		 */
		int _size ;
		
		/**
		 * Pointer to the data stored in the dynamic_array
		 */
		T* _data ;
		
		/**
		 * Resizes the data array to prevent the array from going
		 * out of bounds when the index is larger then the size of
		 * the array.
		 */
		void resize(const int& new_size) {
			T* n_data = new T[new_size] ;
			memset(n_data,0,new_size*sizeof(T)) ;
			memcpy(n_data,_data,_size*sizeof(T)) ;
			delete[] _data ;
			_data = n_data ;
			_size = new_size ;
		}

};

}	// end of namespace container
}	// end of namespace genecis

#endif
