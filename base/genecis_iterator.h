/**
 * @file genecis_iterator.h
 */
 
#ifndef GENECIS_BASE_GENECIS_ITERATOR_H
#define GENECIS_BASE_GENECIS_ITERATOR_H

#include "genecis_iterator_types.h"

namespace genecis {
namespace base {

template<class _It> class genecis_iterator  : 
	public iterator<typename iterator_traits<_It>::iterator_category,
				 typename iterator_traits<_It>::value_type,
				 typename iterator_traits<_It>::difference_type,
				 typename iterator_traits<_It>::pointer,
                     typename iterator_traits<_It>::reference>
{

	protected:
		_It __current ;
		
		typedef iterator_traits<_It>	__traits ;

	public:

		typedef _It										iterator_type ;
		typedef random_access_iterator_tag			iterator_category ;
		typedef typename __traits::value_type			value_type ;
		typedef typename __traits::difference_type		difference_type ;
		typedef typename __traits::pointer				pointer ;
		typedef typename __traits::reference			reference ;
		
		/**
		 * Iterator constructor
		 */
		explicit
		genecis_iterator( const iterator_type& __i ) : __current(__i) {}
		
		// Forward iterator functions
		reference operator*() {
			return *__current ;
		}
		
		pointer operator->() {
			return __current ;
		}
		
		genecis_iterator& operator++() {
			++__current ;
			return *this ;
		}
		
		genecis_iterator operator++(int) {
			return genecis_iterator(__current++) ;
		}
		
		// Backward iterator functions
		genecis_iterator& operator--() {
			--__current ;
			return *this ;
		}
		
		genecis_iterator operator--(int) {
			return genecis_iterator(__current--) ;
		}
		
		// Random access iterator functions
		reference operator[] (const difference_type __n) const {
			return __current[__n] ;
		}
		
		genecis_iterator& operator+=(difference_type __n) {
			__current += __n ;
			return *this ;
		}
		
		genecis_iterator operator+(difference_type __n) const {
			return genecis_iterator( __current + __n ) ;
		}
		
		genecis_iterator& operator-=(difference_type __n) {
			__current -= __n ;
			return *this ;
		}
		
		genecis_iterator operator-(difference_type __n) const {
			return genecis_iterator( __current - __n ) ;
		}
		
		const iterator_type& base() const {
			return __current ;
		}

};

/** Comparison operators between genecis_iterators **/
template<class _It>
inline bool operator==(	const genecis_iterator<_It>& lhs,
						const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() == rhs.base() ) ;
}

template<class _It>
inline bool operator!=(	const genecis_iterator<_It>& lhs,
						const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() != rhs.base() ) ;
}

template<class _It>
inline bool operator<( const genecis_iterator<_It>& lhs,
					   const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() < rhs.base() ) ;
}

template<class _It>
inline bool operator<=( const genecis_iterator<_It>& lhs,
					    const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() <= rhs.base() ) ;
}

template<class _It>
inline bool operator>( const genecis_iterator<_It>& lhs,
					   const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() > rhs.base() ) ;
}

template<class _It>
inline bool operator>=( const genecis_iterator<_It>& lhs,
					    const genecis_iterator<_It>& rhs )
{
	return ( lhs.base() >= rhs.base() ) ;
}

template<class _It>
inline genecis_iterator<_It>
operator+( typename genecis_iterator<_It>::difference_type& __n,
		   const genecis_iterator<_It>& lhs )
{
	return genecis_iterator<_It>( lhs.base() + __n ) ;
}

template<class _It>
inline typename genecis_iterator<_It>::difference_type
operator-( const genecis_iterator<_It>& lhs, const genecis_iterator<_It>& rhs )
{
	return genecis_iterator<_It>( lhs.base() - rhs.base() ) ;
}

template<class _ItL, class _ItR>
inline typename genecis_iterator<_ItL>::difference_type
operator-( const genecis_iterator<_ItL>& lhs, const genecis_iterator<_ItR>& rhs )
{
	return genecis_iterator<_ItL>( lhs.base() - rhs.base() ) ;
}

}	// end of namespace base
}	// end of namespace genecis

#endif
