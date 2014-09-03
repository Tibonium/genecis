#include <genecis/container/array.h>
#include <genecis/distribution/uniform.h>
#include <cstring>

using namespace genecis::container ;
using namespace genecis::distribution ;
using namespace std ;

struct collection {

	typedef double		value_type1 ;
	typedef int			value_type2 ;
	typedef uniform		value_type3 ;
	
	value_type1 e1 ;
	value_type2 e2 ;
	value_type3 e3 ;
	
};

template<class E>
struct extract_e2 {
	typedef E		argument_type ;
	typedef typename E::value_type2		result_type ;
	
	static
	result_type use(argument_type t) {
		return t.e2 ;
	}
};

template<class E, class F>
class array_unary_special :
	public container_expression<array_unary_special<E,F> >
{	
	public:
		typedef F	functor_type ;
		typedef E	expression_type ;
		typedef typename E::size_type	size_type ;
		typedef typename E::value_type::value_type2	value_type ;
		typedef const value_type	const_reference ;
		typedef typename E::iterator		iterator ;
		typedef typename E::const_iterator			const_iterator ;
	
		explicit
		array_unary_special( const expression_type& e ) : __e(e) {}
				
		const expression_type& expression() const {
			return __e ;
		}
		
		const size_type size() const {
			return expression().size() ;
		}
		
		const_reference operator() (size_type i) const {
			return functor_type::use( __e(i) ) ;
		}
		
		const_iterator begin() const {
			return expression().begin() ;
		}
		
		const_iterator end() const {
			return expression().end() ;
		}
	
	private:
		expression_type	__e ;
};

template<class E, class F>
struct array_unary_special_traits {
	typedef array_unary_special<E,F>	result_type ;
	typedef result_type		expression_type ;
};

template<class E>
typename array_unary_special_traits<E, extract_e2<typename E::value_type> >::result_type
get_second (const container_expression<E>& e) {
	typedef typename array_unary_special_traits<E,
		extract_e2<typename E::value_type> >::expression_type	expression_type ;
	return expression_type( e() ) ;
}

template<class C, class R>
void extract(typename C::size_type i, C* c, R* result) {

	typedef typename C::size_type		size_type ;
	typedef typename C::iterator		origin_iterator ;
	typedef typename R::iterator		result_iterator ;
	typedef typename R::value_type		result_type ;
		
	origin_iterator it = c->begin() ;
	collection tmp ;
	size_type distance = 0 ;
	size_type data_bytes = 0 ;
	size_type data_size = sizeof(tmp) ;
	switch(i) {
		case 0:
			data_bytes = sizeof(tmp.e1) ;
			break;
		case 1:
			distance = sizeof(tmp.e1) ;
			data_bytes = sizeof(tmp.e2) ;
			break;
		case 2:
			distance = sizeof(tmp.e1) + sizeof(tmp.e2) ;
			data_bytes = sizeof(tmp.e3) ;
			break;
		default:
			cout << "Size of array is 3" << endl ;
			break;
	}
	
	cout << "data_bytes:    " << data_bytes << endl ;
	cout << "distance:      " << distance << endl ;
	cout << "data_size:     " << data_size << endl ;
	cout << "begin:         " << it << endl ;
	cout << "end:           " << c->end() << endl ;
	char* byte_ptr = reinterpret_cast<char*>(it) ;
	byte_ptr += distance ;
	cout << "byte_ptr:      " << (result_iterator)byte_ptr << endl ;
	result_iterator r = result->begin() ;
	
	cout << "****beginning extraction****" << endl ;
	while( (origin_iterator)byte_ptr < c->end() ) {
		result_type x = 2 ;
		result_iterator tmp_r = &x ;
		cout << "it:        " << it << endl ;
		cout << "r:         " << r << endl ;
		memcpy(tmp_r, (result_iterator)byte_ptr, data_bytes) ;
		(*r) = (*tmp_r) ;
		cout << "tmp_r:     " << *tmp_r << endl ;
		byte_ptr += data_size ;
		cout << "byte_ptr:  " << (result_iterator)byte_ptr << endl ;
		++it ;
		++r ;
	}
}

int main() {

	collection a ;
	collection b ;
	collection c ;
	// e1
	a.e1 = 3.14 ;
	b.e1 = 1.71 ;
	c.e1 = 2.714 ;
	// e2
	a.e2 = 10 ;
	b.e2 = 7 ;
//	c.e2 = 100 ;
	// e3
	a.e3 = uniform(5,10) ;
	b.e3 = uniform(20,100) ;
	c.e3 = uniform(1.1,1.2) ;
	
//	cout << a.e1 << " " << a.e2 << " " << a.e3 << endl ;
//	cout << "size of a:" << sizeof(a) << endl ;
//	cout << "size of b:" << sizeof(b) << endl ;
//	cout << "size of c:" << sizeof(c) << endl ;
	
	array<collection> m(3,a) ;
	
	m(0) = a ;
	m(1) = b ;
	m(2) = c ;
	
//	array<int> t = get_second(m) ;
//	extract(1,&m,&t) ;
//	double answer =  t(0).probability(7,8) ;
//	cout << "t:" << t << endl ;
	
//	char s[] = "this is the beginning of a great world!" ;
//	char d[8] ;
//	int N = 8 ;
//	int offset = 12 ;
//	char* it =  s + offset ;
//	memcpy(d, it, N) ;
//	for(int i=0; i<N; ++i) {
//		cout << d[i] ;
//	}
//	cout << endl ;

}
