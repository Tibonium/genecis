/**
 * @file container_express.h
 */
 
#ifndef GENECIS_CONTAINER_CONTAINER_EXPRESSION_H
#define GENECIS_CONTAINER_CONTAINER_EXPRESSION_H

#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include "../base/genecis_reverse_iterator.h"

namespace genecis {
namespace container {

	using namespace genecis::base ;

	template<template<typename> class E, typename T>
	class container_expression {
		public:
			typedef T										 value_type ;
			typedef T *									 	 pointer ;
			typedef const T *								 const_pointer ;
			typedef ptrdiff_t								 difference_type ;
			typedef T &									 	 reference ;
			typedef const T &								 const_reference ;
			typedef size_t									 size_type ;
			typedef value_type*								 iterator ;
			typedef const value_type*						 const_iterator ;
			typedef genecis_reverse_iterator<iterator>		 reverse_iterator ;
			typedef genecis_reverse_iterator<const_iterator> const_reverse_iterator ;
		
			// Expression size and data accessors
			size_type size() const {
				return static_cast<E<T> const&> (*this).size() ;
			}
			
			value_type* data() const {
				return static_cast<E<T> const&> (*this).data() ;
			}
			
			// Expression iterators
			iterator begin() {
				return static_cast<E<T> &> (*this).begin() ;
			}
			
			iterator end() {
				return static_cast<E<T> &> (*this).end() ;
			}
			
			const_iterator cbegin() const {
				return static_cast<E<T> const&> (*this).cbegin() ;
			}
			
			const_iterator cend() const {
				return static_cast<E<T> const&> (*this).cend() ;
			}
			
			reverse_iterator rbegin() {
				return static_cast<E<T> &> (*this).rbegin() ;
			}
			
			reverse_iterator rend() {
				return static_cast<E<T> &> (*this).rend() ;
			}
			
			const_reverse_iterator rcbegin() const {
				return static_cast<E<T> const&> (*this).rcbegin() ;
			}
			
			const_reverse_iterator rcend() const {
				return static_cast<E<T> const&> (*this).rcend() ;
			}
			
			// Expression Element accessors
			value_type operator() (size_type i) const {
				return static_cast<E<T> const&> (*this)(i) ;
			}
			
			value_type operator() (size_type i) {
				return static_cast<E<T> &> (*this)(i) ;
			}
			
			// Expression accessors
			operator E<T>& () {
				return static_cast<E<T>&> (*this) ;
			}
			
			operator E<T> const&() const {
				return static_cast<const E<T>&> (*this) ;
			}

	};

}	// end of namespace container
}	// end of namespace genecis

#endif
