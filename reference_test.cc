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
	private:
		int _v ;
};

void doubleup::times4() {
	_v *= 4 ;
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
	return 0 ;

}
