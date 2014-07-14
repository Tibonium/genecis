#include <cstring>
#include <iostream>

using namespace std ;

template<typename _t, size_t _n>
class dataset {
	public:
		inline _t& operator[] (size_t i) {
			return data[i] ;
		}
		template<size_t i>
		inline void operator= (_t c) {
			data[i] = c ;
		}
		dataset() {}
	private:
		_t data[_n] ;
};

int main() {

	unsigned n = 3 ;
	dataset<int,3> a ;
	
	for(unsigned i=0; i<n; ++i) {
		a[i] = i + 1 ;
		cout << "a[" << i << "]:" << a[i] << endl ;
	}
	
//	cout << "after memset try" << endl ;
//	for(unsigned i=0; i<n; ++i) {
//		memset(a[i],a[i]*2,n) ;
//		cout << "a[" << i << "]:" << a[i] << endl ;
//	}
}
