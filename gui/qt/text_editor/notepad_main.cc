#include "notepad.h"

int main( int argv, char** args ) {

	QApplication app(argv, args) ;
	
	notepad n ;
	n.show() ;
	
	return app.exec() ;

}
