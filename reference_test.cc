#include <iostream>

using namespace std ;

class tracker {
	public:
		tracker( int& a ) : _a(a) {} ;
		void print() ;
	private:
		int& _a ;
};

void tracker::print() {
	cout << "the current value is: " << _a << endl ;
}

class doubleup {
	public:
		doubleup( int v ) : _v(v) {} ;
		void times4() ;
		int& value() ;
		friend void operator+ ( int lhs, doubleup& rhs ) ;
		friend void operator+ ( doubleup& lhs, int rhs ) ;
	private:
		int _v ;
};

void doubleup::times4() {
	_v *= 4 ;
}

void operator+ ( int lhs, doubleup& rhs ) {
	rhs._v += lhs ;
}

void operator+ ( doubleup& lhs, int rhs ) {
	lhs._v += rhs ;
}

int& doubleup::value() {
	return _v ;
}

int main() {

	int num = 10 ;
	doubleup d(num) ;
	int& val = d.value() ;
	tracker t( val ) ;
	cout << "the number is: " << num << endl ;
	d.times4() ;
	t.print() ;
	d.times4() ;
	t.print() ;
	2 + d ;
	t.print() ;
	d + 17 ;
	t.print() ;
	return 0 ;

}
