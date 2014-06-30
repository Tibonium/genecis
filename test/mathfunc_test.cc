#include <iostream>
#include <cstring>
#include "../math/math_functions.h"

using namespace std ;

template <class _T> class myarray ;

template <class _T> std::ostream&
operator<< (std::ostream& os, myarray<_T>& a) ;

template <class _T>
class myarray : public math_functions {

	public:
	
		// Constructor
		myarray(size_t t) {
			_a = new _T[t] ;
			memset(_a, 0, t) ;
			_s = t ;
		}
		
		// Destructor
		~myarray() {
			delete _a ;
		}

		inline size_t size() {
			return _s ;
		}
		
		inline _T& operator() (size_t t) {
			_index = t ;
			return _a[t] ;
		}
		
		inline void operator= (_T c) {
			_a[_index] = c ;
		}
		
	friend std::ostream& operator<< <>
		(std::ostream& os, myarray& a) ;
	
	private:
		_T* _a ;
		size_t _s ;
		size_t _index ;	
};

template <class _T>
inline std::ostream& operator<< 
	(std::ostream& os, myarray<_T>& a)
{
	os << "[" << a.size() << "]: {" ;
	for(size_t i=0; i<a.size(); ++i) {
		os << a(i) ;
		(i!=(a.size()-1)) ? os << "," :
			os << "}" ;
	}
	return os ;
}

int main() {

	myarray<int> v1(10) ;
	myarray<int> v2(10) ;
	myarray<int> r(10) ;
	
	for(size_t i=0; i<v1.size(); ++i) {
		v1(i) = i+1 ;
		v2(i) = i+1 ;
	}
	
	cout << "v1" << v1 << endl ;
	math_functions::convolve(v1,v2,r) ;
	cout << "result" << r << endl ;
//	cout << "sizeof array: "
//		<< value.size() << endl ;
//	value(0) = 182 ;
//	cout << "value(0): " << value(0) << endl ;
	
	return 0 ;
}
