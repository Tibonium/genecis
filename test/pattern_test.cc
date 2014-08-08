#include "../ai/number_pattern.h"
#include "../container/array.h"

using namespace genecis::ai ;
using namespace genecis::container ;

int main() {

	array<int> myset(5) ;
	number_pattern p ;
	
	myset(0) = 200000 ;
	for(size_t i=1; i<myset.size(); ++i) {
		myset(i) = myset(i-1) / 2 ;
	}
	
	cout << "Set" << myset << endl ;
	p.find_pattern( myset.data(), myset.size() ) ;

}
