/**
 * @file genecis_reverse_iterator.h
 */
 
#ifndef GENECIS_BASE_GENECIS_REVERSE_ITERATOR_H
#define GENECIS_BASE_GENECIS_REVERSE_ITERATOR_H

#include "genecis_iterator_types.h"

namespace genecis {
namespace base {

template<class _It> class genecis_reverse_iterator : 
	public iterator<typename iterator_traits<_It>::iterator_category,
				 typename iterator_traits<_It>::value_type,
				 typename iterator_traits<_It>::difference_type,
				 typename iterator_traits<_It>::pointer,
                     typename iterator_traits<_It>::reference>
{

	protected:
		_It __rcurrent ;
		
		typedef iterator_traits<_It>	__traits ;

	public:

		typedef _It										iterator_type ;
		typedef typename __traits::difference_type		difference_type ;
		typedef typename __traits::pointer				pointer ;
		typedef typename __traits::reference			reference ;

		/** Base Constructor **/
		explicit
		genecis_reverse_iterator( iterator_type __r ) : __rcurrent( __r ) {}
		
		/** Copy Constructors **/
		genecis_reverse_iterator( const genecis_reverse_iterator& __r ) :
			__rcurrent( __r.__rcurrent ) {}
			
		template<class _Iter>
		genecis_reverse_iterator( const genecis_reverse_iterator<_Iter>& __r ) :
			__rcurrent( __r.base() ) {}
		
		/**
		 * Access __rcurrent, similar to genecis_iterator
		 */
		iterator_type base() const {
			return __rcurrent ;
		}
		
		reference operator*() {
			iterator_type __tmp = __rcurrent ;
			return *--__tmp ;
		}
		
		pointer operator->() {
			return &(operator*()) ;
		}
		
		genecis_reverse_iterator& operator++() {
			--__rcurrent ;
			return *this ;
		}
		
		genecis_reverse_iterator operator++(int) {
			genecis_reverse_iterator tmp = *this ;
			--__rcurrent ;
			return tmp ;
		}
		
		genecis_reverse_iterator& operator--() {
			++__rcurrent ;
			return *this ;
		}
		
		genecis_reverse_iterator operator--(int) {
			genecis_reverse_iterator tmp = *this ;
			++__rcurrent ;
			return tmp ;
		}
		
		// Random access iterator functions
		reference operator[] (difference_type __n) const {
			return *(*this + __n) ;
		}
		
		genecis_reverse_iterator& operator+=(difference_type __n) {
			__rcurrent -= __n ;
			return *this ;
		}
		
		genecis_reverse_iterator operator+(difference_type __n) const {
			return genecis_reverse_iterator( __rcurrent - __n ) ;
		}
		
		genecis_reverse_iterator& operator-=(difference_type __n) {
			__rcurrent += __n ;
			return *this ;
		}
		
		genecis_reverse_iterator operator-(difference_type __n) const {
			return genecis_reverse_iterator( __rcurrent + __n ) ;
		}

} ;

/** Comparison operators between genecis_iterators **/
template<class _It>
inline bool operator==(	const genecis_reverse_iterator<_It>& lhs,
						const genecis_reverse_iterator<_It>& rhs )
{
	return ( lhs.base() == rhs.base() ) ;
}

template<class _It>
inline bool operator!=(	const genecis_reverse_iterator<_It>& lhs,
						const genecis_reverse_iterator<_It>& rhs )
{
	return !( lhs == rhs ) ;
}

template<class _It>
inline bool operator<( const genecis_reverse_iterator<_It>& lhs,
					   const genecis_reverse_iterator<_It>& rhs )
{
	return ( lhs.base() < rhs.base() ) ;
}

template<class _It>
inline bool operator<=( const genecis_reverse_iterator<_It>& lhs,
					    const genecis_reverse_iterator<_It>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _It>
inline bool operator>( const genecis_reverse_iterator<_It>& lhs,
					   const genecis_reverse_iterator<_It>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _It>
inline bool operator>=( const genecis_reverse_iterator<_It>& lhs,
					    const genecis_reverse_iterator<_It>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _It>
inline typename genecis_reverse_iterator<_It>::difference_type
operator+( typename genecis_reverse_iterator<_It>::difference_type __n,
		   const genecis_reverse_iterator<_It>& lhs )
{
	return genecis_reverse_iterator<_It>( lhs.base() - __n ) ;
}

template<class _It>
inline typename genecis_reverse_iterator<_It>::difference_type
operator-( const genecis_reverse_iterator<_It>& lhs,
		   const genecis_reverse_iterator<_It>& rhs )
{
	return genecis_reverse_iterator<_It>( rhs.base() - lhs.base() ) ;
}

/** Comparison between different iterator types **/
template<class _ItL, class _ItR>
inline bool operator==(	const genecis_reverse_iterator<_ItL>& lhs,
						const genecis_reverse_iterator<_ItR>& rhs )
{
	return ( lhs.base() == rhs.base() ) ;
}

template<class _ItL, class _ItR>
inline bool operator!=(	const genecis_reverse_iterator<_ItL>& lhs,
						const genecis_reverse_iterator<_ItR>& rhs )
{
	return !( lhs == rhs ) ;
}

template<class _ItL, class _ItR>
inline bool operator<( const genecis_reverse_iterator<_ItL>& lhs,
					   const genecis_reverse_iterator<_ItR>& rhs )
{
	return ( lhs.base() < rhs.base() ) ;
}

template<class _ItL, class _ItR>
inline bool operator<=( const genecis_reverse_iterator<_ItL>& lhs,
					    const genecis_reverse_iterator<_ItR>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _ItL, class _ItR>
inline bool operator>( const genecis_reverse_iterator<_ItL>& lhs,
					   const genecis_reverse_iterator<_ItR>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _ItL, class _ItR>
inline bool operator>=( const genecis_reverse_iterator<_ItL>& lhs,
					    const genecis_reverse_iterator<_ItR>& rhs )
{
	return !( lhs < rhs ) ;
}

template<class _ItL, class _ItR>
inline typename genecis_reverse_iterator<_ItL>::difference_type
operator-( const genecis_reverse_iterator<_ItL>& lhs,
		   const genecis_reverse_iterator<_ItR>& rhs )
{
	return ( rhs.base() - lhs.base() ) ;
}

}	// end of namespace base
}	// end of namespace genecis

#endif
