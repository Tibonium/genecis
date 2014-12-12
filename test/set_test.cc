#include <genecis/math/set.h>
#include <genecis/container/array.h>
#include <genecis/math/functional_logic.h>
#include <vector>

using namespace std ;
using namespace genecis::math ;
using namespace genecis::container ;

int main() {
	
//	stringstream ss ;
//	string s ;
//	cout << "Enter a list of numbers: " ;
//	getline( cin, s ) ;
//	ss << s ;
//	vector<int> nums ;
//	char c[10] ;
//	int N = 0 ;
//	while( !ss.eof() ) {
//		ss.getline(&c[0], 10, ' ') ;
//		nums.push_back( atoi(c) ) ;
//		++N ;
//	}
	
	typedef int			value_type ;
	typedef size_t			size_type ;
	typedef array<value_type>	container_type ;
	typedef set<value_type>		set_type ;
	
	size_type n = 10 ;
	container_type origin(n) ;
	
	container_type::iterator it = origin.begin() ;
	value_type i = 0 ;
	for(it=origin.begin(); it!=origin.end(); ++it, ++i) {
		*it = i ;
	}
	cout << "origin" << origin << endl ;

	set_type parent(origin) ;
	set_type a = parent.subset(0,2) ;
	cout << "Set A" ;
	a.print() ;
	set_type b = parent.subset(2,4) ;
	cout << "Set B" ;
	b.print() ;
	
	set_type set = a.unite(b) ;
	cout << "Union of A and B " ;
	set.print() ;

	set = a.intersect(b) ;
	cout << "Intersection of A and B " ;
	set.print() ;
	
	set = parent.complement(a) ;
	cout << "Complement of A " ;
	set.print() ;
	
	set = a.symmetric_difference(b) ;
	cout << "Symmetric Difference of A and B " ;
	set.print() ;
	
	set_type e = empty_set<value_type>() ;
	cout << "Empty set " ;
	e.print() ;

	set = a.unite(e) ;
	cout << "Union of A and the empty set " ;
	set.print() ;

	set = a.intersect(e) ;
	cout << "Intersection of A and the empty set " ;
	set.print() ;

	set = a.symmetric_difference(e) ;
	cout << "Symmetric Difference of A and the empty set " ;
	set.print() ;
	
	( a.isSubset(e) ) ? cout << "the empty set is a subset of A" << endl :
		cout << "the empty set is not a subset of A...oops" << endl ;
		
	set_type domain(5) ;
	set_type codomain(10) ;
	set_type::iterator itd ;
	i = 1 ;
	for(itd=domain.begin(); itd!=domain.end(); ++itd, ++i) {
		(*itd) = i ;
	}
	i = 1 ;
	for(itd=codomain.begin(); itd!=codomain.end(); ++itd, ++i) {
		(*itd) = i ;
	}
	cout << "Domain " ;
	domain.print() ;
	cout << "Codomain " ;
	codomain.print() ;

	set_type fcod(5) ;
	set_type::iterator k=fcod.begin() ;
//	(*k) = 1 ;
//	(*++k) = 2 ;
//	(*++k) = 3 ;
//	(*++k) = 4 ;
//	(*++k) = 5 ;
	(*k) = 1 ;
	(*++k) = 2 ;
	(*++k) = 3 ;
	(*++k) = 4 ;
	(*++k) = 5 ;
	functional_logic<value_type,value_type> f(domain,codomain,domain,fcod) ;
	
	f.print() ;
	cout << "The function is"
		 << (f.isValid() ? " " : " not ")
		 << "a valid function." << endl ;
	if( f.isValid() ) {
		cout << "The function is"
			 << (f.isInjective() ? " " : " not ")
			 << "a one-to-one function." << endl ;
		cout << "The function is"
			 << (f.isSurjective() ? " " : " not ")
			 << "onto." << endl ;
		cout << "The function is"
			 << (f.isBijective() ? " " : " not ")
			 << "a bijection." << endl ;
	 }
}
