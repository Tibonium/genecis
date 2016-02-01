#include <genecis/base/genecis_stringlist.h>

USING_NAMESPACE(genecis::base)

int main() {

	const char* word = "first" ;
	genecis_string test("      This, and now, is the first test of many tests to come.") ;
	if( test.contains(word, genecis_string::CaseSensitive) ) {
		std::cout << "Found \"" << word << "\" within the test phrase." << std::endl ;
	}
	
	genecis_stringlist data = test.split(',') ;
	std::cout << "data" << data << std::endl ;


	genecis_string entity("122MM AMPHIBIOUS HOWITZER TYPE 96") ;
	std::cout << "The entity long name is: " << entity << std::endl ;
	data = entity.split(' ') ;
	std::cout << "data" << data << std::endl ;
	
}
