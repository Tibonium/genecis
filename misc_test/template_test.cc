#include <cstring>
#include <iostream>

using namespace std ;

template<template <typename> class E, typename T >
class matrix_expression {
	public:
		size_t rows() const {
			return static_cast<E<T> const&> (*this).rows() ;
		}
		size_t cols() const {
			return static_cast<E<T> const&> (*this).cols() ;
		}
		T operator() (size_t i, size_t j) const {
			return static_cast<E<T> const&> (*this)(i,j) ;
		}
		operator E<T>& () {
			return static_cast<E<T>&> (*this) ;
		}
		operator E<T> const&() const {
			return static_cast<const E<T>&> (*this) ;
		}
};

template <typename T>
class matrix : public matrix_expression<matrix,T> {
	public:
		inline T& operator() (size_t i, size_t j) const {
			return _data[i*_cols + j] ;
		}
		size_t rows() const {
			return _rows ;
		}
		size_t cols() const {
			return _cols ;
		}
		matrix(size_t n, size_t m) : _rows(n),
			_cols(m)
		{
			_data = new T[n*m] ;
			memset(_data, 0, n*m) ;	
		}
		template<template <typename> class E>
		matrix(matrix_expression<E,T> const& other) {
			E<T> const& o = other ;
			_rows = o.rows() ;
			_cols = o.cols() ;
			size_t N = _rows * _cols ;
			_data = new T[N] ;
			for(size_t i=0; i<_rows; ++i) {
				for(size_t j=0; j<_cols; ++j) {
					_data[i*_cols+j] = o(i,j) ;
				}
			}
		}
		
		virtual ~matrix() {
			if ( _data ) {
				delete[] _data ;
				_data = NULL ;
			}
		}
		
	private:
		size_t _rows ;
		size_t _cols ;
		T* _data ;
		
};

template<typename T>
class matrix_scale : public matrix_expression<matrix_scale,T> {
	T _c ;
	matrix<T> const& _v ;
	public:
		matrix_scale(T c, matrix<T> const& v) : _c(c), _v(v) {}
		size_t rows() const { return _v.rows() ; }
		size_t cols() const { return _v.cols() ; }
		T operator() (size_t i, size_t j) const { return _c * _v(i,j) ; }

};

template <typename T>
matrix_scale<T> const
operator* (T c, matrix<T> const& v) {
	return matrix_scale<T>(c,v) ;
}

template <typename T>
matrix_scale<T> const
operator* (matrix<T> const& v, T c) {
	return matrix_scale<T>(c,v) ;
}

int main() {

	unsigned n = 2 ;
	unsigned m = 2 ;
	matrix<int> a(n,m) ;
	
	for(unsigned i=0; i<n; ++i) {
		for(unsigned j=0; j<m; ++j) {
			a(i,j) = i + j + 1 ;
			cout << "a(" << i << "," << j << "):" << a(i,j) << endl ;
		}
	}
	matrix<int> b = 5 * a ;

	cout << "after multiply " << endl ;
	for(unsigned i=0; i<n; ++i) {
		for(unsigned j=0; j<m; ++j) {
			cout << "b(" << i << "," << j << "):" << b(i,j) << endl ;
		}
	}
	
}
