/**
 * @file matrix_expression.h
 */
 
#ifndef GENECIS_MATH_MATRIX_EXPRESSION_H
#define GENECIS_MATH_MATRIX_EXPRESSION_H

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <genecis/base/genecis_expression.h>
#include <genecis/base/genecis_functions.h>

using namespace genecis::base ;

namespace genecis {
namespace math {

	using namespace std ;
	 
	template<class E>
	class matrix_expression : public genecis_expression<E> {
	
		public:
			typedef E		expression_type ;
			typedef double	value_type ;
			typedef size_t	size_type ;

			expression_type& operator() () {
				return *static_cast<expression_type*> (this) ;
			}
			
			const expression_type& operator() () const {
				return *static_cast<const expression_type*> (this) ;
			}

	};
	
	/*********************** MATRIX OPERATIONS *************************
	**
	* This section contains all metatemplates for the various
	* matrix operations for this class. That would return a new matrix
	* but instead return class copies.
	*
	*******************************************************************/

	/** ===================Scalar Multiplication=================== **/
	template<class E, class T, class F>
	class matrix_scalar1 :
		public matrix_expression<matrix_scalar1<E,T,F> >
	{
	
		public:
	
			typedef E						expression_type ;
			typedef F						function_type ;
			typedef typename E::value_type	value_type ;
			typedef typename E::size_type	size_type ;
			typedef value_type				reference ;
			typedef const reference			const_reference ;
			typedef matrix_scalar1<E,T,F>		self_type ;
			
			// Constructor
			explicit
			matrix_scalar1(const value_type& c, const matrix_expression<E>& m) :
				__c(c), __e(m) {}
			
			// Expression accessors
			expression_type& expression() {
				return __e ;
			}
			
			const expression_type& expression() const {
				return __e ;
			}
			
			// Size accessors
			size_type rows() const {
				return __e.rows() ;
			}
			
			size_type cols() const {
				return __e.cols() ;
			}
			
			bool verify() const {
				return __e.verify() ;
			}
			
			bool singular() const {
				return __e.singular() ;
			}
			
			
			
			// Element accessor
			reference operator() (size_type i, size_type j) const {
				return function_type::use( __e(i,j), __c ) ;
			}
			
		private:
		
			expression_type __e ;
			value_type __c ;
	};
	
	template<class E, class T, class F>
	struct matrix_scalar1_traits {
		typedef matrix_scalar1<E,T,F>		expression_type ;
		typedef typename E::self_type		result_type ;
	};

	// (s + m)(i,j) = s + m(i,j)
	template<class E, class T>
	typename matrix_scalar1_traits<E, T, scalar_add<typename E::value_type, T> >::result_type
	operator+ (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar1_traits<E, T,
				scalar_add<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( s, e() ) ;
	}

	// (s - m)(i,j) = s - m(i,j)
	template<class E, class T>
	typename matrix_scalar1_traits<E, T, scalar_minus<typename E::value_type, T> >::result_type
	operator- (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar1_traits<E, T,
				scalar_minus<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( s, e() ) ;
	}
	
	// (s * m)(i,j) = s * m(i,j)
	template<class E, class T>
	typename matrix_scalar1_traits<E, T, scalar_multiply<typename E::value_type, T> >::result_type
	operator* (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar1_traits<E, T,
				scalar_multiply<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( s, e() ) ;
	}
	
	// (s / m)(i,j) = s / m(i,j)
	template<class E, class T>
	typename matrix_scalar1_traits<E, T, scalar_divide<typename E::value_type, T> >::result_type
	operator/ (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar1_traits<E, T,
				scalar_divide<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( s, e() ) ;
	}

	// (s % m)(i,j) = s % m(i,j)
	template<class E, class T>
	typename matrix_scalar1_traits<E, T, scalar_mod<typename E::value_type, T> >::result_type
	operator% (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar1_traits<E, T,
				scalar_mod<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( s, e() ) ;
	}
	
	template<class E, class T, class F>
	class matrix_scalar2 :
		public matrix_expression<matrix_scalar2<E,T,F> >
	{
	
		public:
	
			typedef E						expression_type ;
			typedef F						function_type ;
			typedef typename E::value_type	value_type ;
			typedef typename E::size_type	size_type ;
			typedef value_type				reference ;
			typedef const reference			const_reference ;
			typedef matrix_scalar1<E,T,F>		self_type ;
			
			// Constructor
			explicit
			matrix_scalar2(const matrix_expression<E>& m, const value_type& c) :
				__c(c), __e(m) {}
			
			// Expression accessors
			expression_type& expression() {
				return __e ;
			}
			
			const expression_type& expression() const {
				return __e ;
			}
			
			// Size accessors
			size_type rows() const {
				return __e.rows() ;
			}
			
			size_type cols() const {
				return __e.cols() ;
			}
			
			bool verify() const {
				return __e.verify() ;
			}
			
			bool singular() const {
				return __e.singular() ;
			}
			
			// Element accessor
			reference operator() (size_type i, size_type j) const {
				return function_type::use( __e(i,j), __c ) ;
			}
			
		private:
		
			expression_type __e ;
			value_type __c ;
	};
	
	template<class E, class T, class F>
	struct matrix_scalar2_traits {
		typedef matrix_scalar2<E,T,F>		expression_type ;
		typedef typename E::self_type		result_type ;
	};
		
	// (m + s)(i,j) = m(i,j) + s
	template<class E, class T>
	typename matrix_scalar2_traits<E, T, scalar_add<typename E::value_type, T> >::result_type
	operator+ (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar2_traits<E, T,
				scalar_add<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (m - s)(i,j) = m(i,j) - s
	template<class E, class T>
	typename matrix_scalar2_traits<E, T, scalar_minus<typename E::value_type, T> >::result_type
	operator- (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar2_traits<E, T,
				scalar_minus<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}
	
	// (m * s)(i,j) = m(i,j) * s
	template<class E, class T>
	typename matrix_scalar2_traits<E, T, scalar_multiply<typename E::value_type, T> >::result_type
	operator* (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar2_traits<E, T,
				scalar_multiply<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}
	
	// (m / s)(i,j) = m(i,j) / s
	template<class E, class T>
	typename matrix_scalar2_traits<E, T, scalar_divide<typename E::value_type, T> >::result_type
	operator/ (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar2_traits<E, T,
				scalar_divide<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

	// (m % s)(i,j) = m(i,j) % s
	template<class E, class T>
	typename matrix_scalar2_traits<E, T, scalar_mod<typename E::value_type, T> >::result_type
	operator% (const T& s, const matrix_expression<E>& e) {
		typedef typename matrix_scalar2_traits<E, T,
				scalar_mod<typename E::value_type, T> >::expression_type expression_type ;
		return expression_type( e(), s ) ;
	}

// Binary Matrix functions
	template<class E1, class E2, class F>
	class matrix_binary :
		public matrix_expression<matrix_binary<E1,E2,F> >
	{
	
		public:
	
			typedef E1						expression1_type ;
			typedef E2						expression2_type ;
			typedef F						function_type ;
			typedef typename E1::value_type	value_type ;
			typedef typename E1::size_type	size_type ;
			typedef typename E1::container_type	container_type ;
			typedef value_type				reference ;
			typedef const reference			const_reference ;
			typedef matrix_binary<E1,E2,F>		self_type ;
			
			// Constructor
			explicit
			matrix_binary(const matrix_expression<E1>& m1,
						  const matrix_expression<E2>& m2)
			: __e1(m1), __e2(m2) { generate_data() ; }
			
			// Expression accessors
			expression1_type& expression1() {
				return __e1 ;
			}
			
			const expression1_type& expression1() const {
				return __e1 ;
			}

			expression2_type& expression2() {
				return __e2 ;
			}
			
			const expression2_type& expression2() const {
				return __e2 ;
			}

			// Size accessors
			size_type rows() const {
				return __e1.rows() ;
			}
			
			size_type cols() const {
				return __e2.cols() ;
			}
			
			bool verify() const {
				return __e1.verify()*__e2.verify() ;
			}
			
			bool singular() const {
				return __e1.singular()*__e2.singular() ;
			}
			
			container_type data() const {
				return __data ;
			}
			
			// Element accessor
			reference operator() (size_type i, size_type j) const {
				return __data(i*__e1.rows() + j) ;
			}
			
		private:
		
			expression1_type __e1 ;
			expression2_type __e2 ;
			container_type __data ;
			
			// Creates the new matrix
			void generate_data() {
				__data = container_type(__e1.rows()*__e2.cols()) ;
				for(size_type i=0; i<__e1.rows(); ++i) {
					for(size_type j=0; j<__e2.cols(); ++j) {
						value_type v = 0 ;
						for(size_type a=0; a<__e2.cols(); ++a) {
							v += function_type::use( __e1(i,a), __e2(a,j) ) ;
						}
						__data(i*__e1.rows()+j) = v ;
					}
				}
			}
	};

	template<class E1, class E2, class F>
	struct matrix_binary_traits {
		typedef matrix_binary<E1,E2,F>		expression_type ;
		typedef typename E1::self_type		result_type ;
	};
	
	// (m * n)(i,j) = sum{ m(i,k) * n(k,j), 0 <= k < n.rows() }
	template<class E1, class E2>
	typename matrix_binary_traits<E1, E2, scalar_multiply<typename E1::value_type,
		typename E2::value_type> >::result_type
	matrix_product (const matrix_expression<E1>& e1, const matrix_expression<E2>& e2) {
		assert( e1().cols() == e2().rows() ) ;
		typedef typename matrix_binary_traits<E1, E2, scalar_multiply<typename E1::value_type,
			typename E2::value_type> >::expression_type expression_type ;
		return expression_type( e1(), e2() ) ;
	}
	
	/** ======================Scalar Division====================== **/
//	template<typename T>
//	class matrix_scale_down : public matrix_expression<matrix_scale_down<T> > {
//			T _c ;
//			matrix<T> const& _m ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_scale_down(T c, matrix<T> const& m) :
//				_c(c), _m(m) {}
//			size_t rows() const { return _m.rows() ; }
//			size_t cols() const { return _m.cols() ; }
//			bool verify() const { return _m.verify() ; }
//			bool singular() const { return _m.singular() ; }
//			T operator() (size_t i, size_t j) const { return _m(i,j) / _c ; }
//	};

//	template<typename T>
//	matrix_scale_down<T> const operator/ (T c, matrix<T> const& m)
//	{
//		return matrix_scale_down<T>(c,m) ;
//	}

//	template<typename T>
//	matrix_scale_down<T> const operator/ (matrix<T> const& m, T c)
//	{
//		return matrix_scale_down<T>(c,m) ;
//	}

//	/** ======================Scalar Addition====================== **/
//	template<typename T>
//	class matrix_scale_add : public matrix_expression<matrix_scale_add<T> > {
//			T _c ;
//			matrix<T> const& _m ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_scale_add(T c, matrix<T> const& m) :
//				_c(c), _m(m) {}
//			size_t rows() const { return _m.rows() ; }
//			size_t cols() const { return _m.cols() ; }
//			bool verify() const { return _m.verify() ; }
//			bool singular() const { return _m.singular() ; }
//			T operator() (size_t i, size_t j) const { return _m(i,j) + _c ; }
//	};

//	template<typename T>
//	matrix_scale_add<T> const operator+ (T c, matrix<T> const& m)
//	{
//		return matrix_scale_add<T>(c,m) ;
//	}

//	template<typename T>
//	matrix_scale_add<T> const operator+ (matrix<T> const& m, T c)
//	{
//		return matrix_scale_add<T>(c,m) ;
//	}

//	/** =====================Scalar Subtration===================== **/
//	template<typename T>
//	class matrix_scale_minus : public matrix_expression<matrix_scale_minus<T> > {
//			T _c ;
//			matrix<T> const& _m ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_scale_minus(T c, matrix<T> const& m) :
//				_c(c), _m(m) {}
//			size_t rows() const { return _m.rows() ; }
//			size_t cols() const { return _m.cols() ; }
//			bool verify() const { return _m.verify() ; }
//			bool singular() const { return _m.singular() ; }
//			T operator() (size_t i, size_t j) const { return _m(i,j) - _c ; }
//	};

//	template<typename T>
//	matrix_scale_minus<T> const operator- (T c, matrix<T> const& m)
//	{
//		return matrix_scale_minus<T>(c,m) ;
//	}

//	template<typename T>
//	matrix_scale_minus<T> const operator- (matrix<T> const& m, T c)
//	{
//		return matrix_scale_minus<T>(c,m) ;
//	}

//	/** ===================== Modulation ===================== **/
//	template<typename T>
//	class matrix_scale_mod : public matrix_expression<matrix_scale_mod<T> > {
//			T _c ;
//			matrix<T> const& _m ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_scale_mod(T c, matrix<T> const& m) :
//				_c(c), _m(m) {}
//			size_t rows() const { return _m.rows() ; }
//			size_t cols() const { return _m.cols() ; }
//			bool verify() const { return _m.verify() ; }
//			bool singular() const { return _m.singular() ; }
//			T operator() (size_t i, size_t j) const { return _m(i,j) % _c ; }
//	};

//	template<typename T>
//	matrix_scale_mod<T> const operator- (T c, matrix<T> const& m)
//	{
//		return matrix_scale_mod<T>(c,m) ;
//	}

//	template<typename T>
//	matrix_scale_mod<T> const operator- (matrix<T> const& m, T c)
//	{
//		return matrix_scale_mod<T>(c,m) ;
//	}

//	/** ================== Matrix Multiplication ================== **/
//	template<typename T>
//	class matrix_prod : public matrix_expression<matrix_prod<T> > {
//			matrix<T> const& _lhs ;
//			matrix<T> const& _rhs ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_prod(matrix<T> const& lhs, matrix<T> const& rhs) :
//				_lhs(lhs), _rhs(rhs) {}
//			size_t rows() const { return _lhs.rows() ; }
//			size_t cols() const { return _rhs.cols() ; }
//			bool verify() const { return true ; }
//			bool singular() const { return false ; }
//			T operator() (size_t i, size_t j) const {
//				T c = 0 ;
//				for(size_t n=0; n<_lhs.cols(); ++n) {
//					c += _lhs(i,n) * _rhs(n,j) ;
//				}
//				return c ;
//			}
//	};

//	template<typename T>
//	matrix_prod<T> const operator* (matrix<T> const& lhs, matrix<T> const& rhs)
//	{
//		assert( lhs.cols() == rhs.rows() ) ;
//		return matrix_prod<T>(lhs,rhs) ;
//	}

//	/** ===================== Matrix Addition ===================== **/
//	template<typename T>
//	class matrix_sum : public matrix_expression<matrix_sum<T> > {
//			matrix<T> const& _lhs ;
//			matrix<T> const& _rhs ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_sum(matrix<T> const& lhs, matrix<T> const& rhs) :
//				_lhs(lhs), _rhs(rhs) {}
//			size_t rows() const { return _lhs.rows() ; }
//			size_t cols() const { return _rhs.cols() ; }
//			bool verify() const { return true ; }
//			bool singular() const { return false ; }
//			T operator() (size_t i, size_t j) const {
//				return _lhs(i,j) + _rhs(i,j) ;
//			}
//	};

//	template<typename T>
//	matrix_sum<T> const operator+ (matrix<T> const& lhs, matrix<T> const& rhs)
//	{
//		assert( lhs.cols() == rhs.cols() &&
//				lhs.rows() == rhs.rows() ) ;
//		return matrix_sum<T>(lhs,rhs) ;
//	}

//	/** =================== Matrix Subtraction =================== **/
//	template<typename T>
//	class matrix_minus : public matrix_expression<matrix_minus<T> > {
//			matrix<T> const& _lhs ;
//			matrix<T> const& _rhs ;
//		public:
//			typedef T	value_type ;
//			typedef size_t	size_type ;
//			matrix_minus(matrix<T> const& lhs, matrix<T> const& rhs) :
//				_lhs(lhs), _rhs(rhs) {}
//			size_t rows() const { return _lhs.rows() ; }
//			size_t cols() const { return _rhs.cols() ; }
//			bool verify() const { return true ; }
//			bool singular() const { return false ; }
//			T operator() (size_t i, size_t j) const {
//				return _lhs(i,j) - _rhs(i,j) ;
//			}
//	};

//	template<typename T>
//	matrix_minus<T> const operator- (matrix<T> const& lhs, matrix<T> const& rhs)
//	{
//		assert( lhs.cols() == rhs.cols() &&
//				lhs.rows() == rhs.rows() ) ;
//		return matrix_minus<T>(lhs,rhs) ;
//	}

}	// end of namespace math
}	// end of namespace genecis

#endif
