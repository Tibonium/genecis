#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas ;

int main() {

	matrix<double> m1(2,1) ;
	m1(0,0) = 10.0 ;
	m1(1,0) = 5.4 ;
	matrix<double> m2(2,1) ;
	m2(0,0) = 7.3 ;
	m2(1,0) = 1.25 ;
	matrix<double> s(2,2) ;
	s(0,0) = 0.25 ;
	s(1,0) = 0.0 ;
	s(0,1) = 0.0 ;
	s(1,1) = 3.1 ;
	matrix<double> m_diff = m1 - m2 ;
	
	std::cout << "m1: " << m1 << std::endl ;
	std::cout << "m2: " << m2 << std::endl ;
	std::cout << "s: " << s << std::endl ;
	matrix<double> m_trans = trans(m_diff) ;
	std::cout << m_trans << std::endl ;
	matrix<double> m_prod = prod( m_trans, s ) ;
	matrix<double> result = prod( m_prod, m_diff ) ;
	std::cout << "(m1-m2)\' * S * (m1-m2): "
			  << result(0,0) << std::endl ;
	
	return 0 ;

}
