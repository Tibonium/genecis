#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas ;

template<class E1, class E2>
struct component_prod{
	typedef E1			argument_type1 ;
	typedef E2			argument_type2 ;
	typedef E1			result_type ;
	
	static
	result_type apply(argument_type1 t1, argument_type2 t2) {
		return element_prod( t1, t2 ) ;
	}
};

template<class E1, class E2>
typename vector_binary_traits<E1, E2, component_prod<typename E1::value_type,
	typename E2::value_type> >::result_type
layer_prod( const vector_expression<E1>& e1, const vector_expression<E2>& e2 ) {
    typedef typename vector_binary_traits<E1, E2, component_prod<
    	typename E1::value_type, typename E2::value_type> >::expression_type expression_type ;
    return expression_type( e1(), e2() ) ;
}

template<class E>
struct matrix_inverse {
	typedef E		argument_type ;
	typedef argument_type	result_type ;
	typedef typename E::value_type	value_type ;
	
	static
	result_type apply(argument_type t) {
		argument_type tmp(t) ;
		value_type d = t(0,0)*t(1,1) - t(0,1)*t(1,0) ;
		tmp(0,0) = t(1,1) / d ;
		tmp(1,0) = -t(1,0) / d ;
		tmp(0,1) = -t(0,1) / d ;
		tmp(1,1) = t(0,0) / d ;
		return tmp ;
	}
};

template<class E>
typename vector_unary_traits<E, matrix_inverse<typename E::value_type> >::result_type
inverse( const vector_expression<E>& e ) {
	typedef typename vector_unary_traits<E, matrix_inverse<typename E::value_type> >::expression_type
		expression_type ;
	return expression_type( e() ) ;
}

/** ========== VECTOR UNARY SPECIAL ========== **/
template<class E, std::size_t I1, std::size_t I2>
struct nested_index {
	typedef E			argument_type ;
	typedef typename E::value_type		result_type ;
	
	static
	result_type apply(argument_type t) {
		return t(I1,I2) ;
	}
};

template<class E1, class E2>
struct nested_plus_assign {
	typedef E1		argument_type1 ;
	typedef E2		argument_type2 ;
	typedef argument_type1	result_type ;
	typedef typename E1::size_type	size_type ;

	static
	result_type apply(argument_type1 t1, argument_type2 t2) {
		size_type size( t2.size() ) ;
		for(size_type i=0; i<size; ++i)
			t1 += t2(i) ;
		return t1 ;
	}

};

template<class E>
struct component_determinant{
	typedef E			argument_type ;
	typedef typename E::value_type			result_type ;
	
	static
	result_type apply(argument_type t) {
		return t(0,0)*t(1,1) - t(0,1)*t(1,0) ;
	}
};

template<class E, class F>
class vector_unary_special :
	public vector_expression<vector_unary_special<E,F> >
{	
	public:
		typedef F	functor_type ;
		typedef E	expression_type ;
		typedef typename E::size_type	size_type ;
		typedef typename E::value_type::value_type	value_type ;
		typedef value_type	const_reference ;
		typedef typename E::iterator		iterator ;
		typedef typename E::const_iterator			const_iterator ;
	
		explicit
		vector_unary_special( const expression_type& e ) : __e(e) {}
				
		const expression_type& expression() const {
			return __e ;
		}
		
		const size_type size() const {
			return expression().size() ;
		}
		
		const_reference operator() (size_type i) const {
			return functor_type::apply( __e(i) ) ;
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
struct vector_unary_special_traits {
	typedef vector_unary_special<E,F>	result_type ;
	typedef result_type		expression_type ;
};

template<class E>
typename vector_unary_special_traits<E,	component_determinant<typename E::value_type> >::result_type
layer_determinant( const vector_expression<E>& e ) {
    typedef typename vector_unary_special_traits<E, component_determinant<
    	typename E::value_type> >::expression_type expression_type ;
    return expression_type( e() ) ;
}

template<template<class E1, class E2>class F, class V, class E>
void nested_vector_assign( V& v, const vector_expression<E>& e) {
	typedef F<V,E>		functor_type ;
    typedef typename V::size_type size_type ;
    v = functor_type::apply( v, e () ) ;
}

template<class E, std::size_t I1, std::size_t I2>
typename vector_unary_special_traits<E, nested_index<typename E::value_type, I1, I2> >::result_type
nested_access( const vector_expression<E>& e ) {
	typedef typename vector_unary_special_traits<E, nested_index<typename E::value_type,
		I1, I2> >::expression_type	expression_type ;
	return expression_type( e() ) ;
}

int main() {

	vector<double> v1(4) ;
	vector<double> v2(4) ;
	vector<double> v3(4) ;
	vector<double> v4(4) ;
	for(unsigned i=0; i<v1.size(); ++i) {
		v1(i) = (i+1)*1 ;
		v2(i) = (i+1)*2 ;
		v3(i) = (i+1)*6 ;
		v4(i) = (i+1)*4 ;
	}
	vector<vector<double> > vv1(2) ;
	vv1(0) = v1 ;
	vv1(1) = v2 ;
	vector<vector<double> > vv2(2) ;
	vv2(0) = v3 ;
	vv2(1) = v4 ;
	vector<vector<double> > v_diff = layer_prod(vv2, vv1) ;
	
	std::cout << "vv1: " << vv1 << std::endl ;
	std::cout << "vv2: " << vv2 << std::endl ;
	std::cout << "v_diff: " << v_diff << std::endl ;
	vector<double> vtest (4,0.0) ;
	nested_vector_assign<nested_plus_assign>(vtest, v_diff) ;
	std::cout << "vtest: " << vtest << std::endl ;
		
	matrix<double> m1(2,2) ;
	matrix<double> m2(2,2) ;
	matrix<double> m3(2,2) ;
	matrix<double> m4(2,2) ;
	for(unsigned i=0; i<m1.size1(); ++i) {
		for(unsigned j=0; j<m1.size2(); ++j) {
			m1(i,j) = (i+1)*1 + j * 1 ;
			m2(i,j) = (i+1)*6 + j * 2 ;
			m3(i,j) = (i+1)*5 + j * 3 ;
			m4(i,j) = (i+1)*4 + j * 4 ;
		}
	}	
	vector<matrix<double> > vm1(2) ;
	vm1(0) = m1 ;
	vm1(1) = m2 ;
	vector<matrix<double> > vm2(2) ;
	vm2(0) = m3 ;
	vm2(1) = m4 ;
	vector<matrix<double> > m_diff = vm1 - vm2 ;
	
	std::cout << "vm1: " << vm1 << std::endl ;
	std::cout << "vm2: " << vm2 << std::endl ;
	std::cout << "m_diff: " << m_diff << std::endl ;
	
	vector<matrix<double> > test_inverse = inverse(m_diff) ;
	std::cout << "test_inverse:" << test_inverse << std::endl ;
	
	vector<double> test_access = nested_access<vector<matrix<double> >,1,1>(m_diff) ;
	std::cout << "test_access:" << test_access << std::endl ;
	
	vector<double> det = layer_determinant(m_diff) ;
	std::cout << "det: " << det << std::endl ;
	
	double result = prod( m1, m2 )(0,0) ;
	std::cout << "result: " << result << std::endl ;
}
