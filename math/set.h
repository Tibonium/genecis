/**
 * @file set.h
 * A class that allows the creation of an abstract set to which
 * various set operations can be performed on.
 */

#ifndef GENECIS_MATH_SET_H
#define GENECIS_MATH_SET_H

#include <genecis/container/array.h>
#include <genecis/container/dynamic_array.h>
#include <cstring>

using namespace genecis::container ;

namespace genecis {
namespace math {

	// Forward decleration
	template<class T> class empty_set ;

	template<class T, class container=array<T> >
	class set {

		public:
	
			typedef set<T>			self_type ;
			typedef container		container_type ;
			typedef typename container::value_type					value_type ;
			typedef typename container::size_type					size_type ;
			typedef typename container::value_type					reference ;
			typedef typename container::const_reference				const_reference ;
			typedef typename container_type::iterator				iterator ;
			typedef typename container_type::const_iterator			const_iterator ;
			typedef typename container_type::reverse_iterator		reverse_iterator ;
			typedef typename container_type::const_reverse_iterator	const_reverse_iterator ;
			
			/**
			 * Construct a set from an array
			 * @param s		array of type T
			 */
			set(container_type s) : __set(s) {}

			/**
			 * Construct a set from a specified size
			 */
			set(size_type n) : __set(container_type(n)) {}
			
			/**
			 * Copy constructor
			 */
			set(const self_type& rhs) : __set(rhs.data()) {}

			/**
			 * Destructor
			 */
			virtual ~set() {}
			
			/**
			 * Quick way to print the set to std output.
			 */
			void print() {
				std::cout << __set << std::endl ;
			}

			/**
			 * Size accessor for the set
			 */
			inline
			size_type size() {
				return __set.size() ;
			}

			inline
			size_type size() const {
				return __set.size() ;
			}
						
			/**
			 * Container accessor
			 */
			inline
			container_type data() {
				return __set ;
			}

			inline
			container_type data() const {
				return __set ;
			}
			
			/**
			 * Element accessor with no bounding checks
			 */
			inline
			reference operator() (size_type i) {
				return __set(i) ;
			}
			
			inline
			const_reference operator() (size_type i) const {
				return __set(i) ;
			}

			/**
			 * Element accessor with bounding checks
			 */
			inline
			reference operator[] (size_type i) {
				return __set[i] ;
			}

			inline
			const_reference operator[] (size_type i) const {
				return __set[i] ;
			}
			
			/**
			 * Subset of the parent set
			 *
			 * In mathematics, especially in set theory, a set A is
			 * a subset of a set B, or equivalently B is a superset
			 * of A, if A is "contained" inside B, that is, all
			 * elements of A are also elements of B.
			 */
			self_type subset(size_type first, size_type last) {
				self_type sub(last-first+1) ;
				iterator it = sub.begin() ;
				for(size_type i=0; i<sub.size(); ++i)
					*it = operator() (first+i), ++it ;
				return sub ;
			}
			
			/**
			 * Determines if a given set is a subset of the set.
			 */
			inline
			bool isSubset(const self_type& sub) {
				size_type count = 0 ;
				size_type this_size = size() ;
				size_type sub_size = sub.size() ;
				for(size_type i=0; i<this_size; ++i) {
					for(size_type j=0; j<sub_size; ++j) {
						if( operator() (i) == sub(j) ) count ++ ;
					}
				}
				return count == sub.size() ;
			}
		
			/**
			 * Union of two sets
			 *
			 * In set theory, the union (denoted by ∪) of a
			 * collection of sets is the set of all distinct
			 * elements in the collection
			 */
			self_type unite(const self_type& other) {
				size_type new_size = 0 ;
				size_type num_checks = size() ;
				bool* dup = new bool[num_checks] ;
				std::memset(dup, false, sizeof(bool)*num_checks) ;
				for(size_type i=0; i<size(); ++i) {
					for(size_type j=0; j<other.size(); ++j) {
						if( operator() (i) == other(j) ) dup[i] = true ;
					}
					if( !dup[i] ) ++new_size ;
				}
				new_size += other.size() ;
				container_type tmp(new_size) ;
				typename container_type::iterator it = tmp.begin() ;
				for(size_type i=0; i<num_checks; ++i) {
					if( !dup[i] ) (*it) = operator() (i), ++it ;
				}
				delete[] dup ;
				container_type oc = other.data() ;
				std::copy(oc.begin(), oc.end(), it) ;
				self_type new_set(tmp) ;
				return new_set ;
			}
			
			/**
			 * Intersection of two sets
			 *
			 * In mathematics, the intersection A ∩ B of two sets A
			 * and B is the set that contains all elements of A that
			 * also belong to B (or equivalently, all elements of B
			 * that also belong to A), but no other elements.
			 */
			self_type intersect(const self_type& other) {
				size_type new_size = 0 ;
				size_type num_checks = size() ;
				bool* dup = new bool[num_checks] ;
				std::memset(dup, false, sizeof(bool)*num_checks) ;
				for(size_type i=0; i<size(); ++i) {
					for(size_type j=0; j<other.size(); ++j) {
						if( operator() (i) == other(j) ) dup[i] = true ;
					}
					if( dup[i] ) ++new_size ;
				}
				container_type tmp(new_size) ;
				typename container_type::iterator it = tmp.begin() ;
				for(size_type i=0; i<num_checks; ++i) {
					if( dup[i] ) (*it) = operator() (i), ++it ;
				}
				delete[] dup ;
				self_type new_set(tmp) ;
				return new_set ;
			}
			
			/**
			 * Complement of a subset from the parent
			 *
			 * In set theory, a complement of a set A refers to
			 * things not in (that is, things outside of) A.
			 */
			self_type complement(const self_type& subset) {
				if( isSubset(subset) ) {
					size_type n = size() - subset.size() ;
					self_type comp(n) ;
					iterator it = comp.begin() ;
					for(size_type i=0; i<size(); ++i) {
						bool dup = false ;
						for(size_type j=0; j<subset.size(); ++j) {
							if( operator() (i) == subset(j) ) dup = true ;
						}
						if( !dup ) *it = operator() (i), ++it ;
					}
					return comp ;
				} else {
					return empty_set<value_type>() ;
				}
			}

			/**
			 * Symmetic difference of two sets
			 *
			 * In mathematics, the symmetric difference of two sets
			 * is the set of elements which are in either of the
			 * sets and not in their intersection.
			 */
			self_type symmetric_difference(const self_type& rhs) {
				size_type new_size = 0 ;
				bool* dup1 = new bool[size()] ;
				bool* dup2 = new bool[rhs.size()] ;
				std::memset(dup1, false, sizeof(bool)*size()) ;
				std::memset(dup2, false, sizeof(bool)*rhs.size()) ;
				for(size_type i=0; i<size(); ++i) {
					for(size_type j=0; j<rhs.size(); ++j) {
						if( operator() (i) == rhs(j) ) dup1[i] = true, dup2[j] = true ;
					}
					if( !dup1[i] ) ++new_size ;
				}
				size_type rhs_size = 0 ;
				for(size_type i=0; i<rhs.size(); ++i) {
					if( !dup2[i] ) ++rhs_size ;
				}
				new_size += rhs_size ;
				container_type tmp(new_size) ;
				typename container_type::iterator it = tmp.begin() ;
				for(size_type i=0; i<size(); ++i) {
					if( !dup1[i] ) (*it) = operator() (i), ++it ;
				}
				for(size_type i=0; i<rhs.size(); ++i) {
					if( !dup2[i] ) (*it) = rhs(i), ++it ;
				}
				delete[] dup1 ;
				delete[] dup2 ;
				self_type new_set(tmp) ;
				return new_set ;
			}

		/** ===== Iterators ===== **/
			/**
			 * Provides a pointer to the beginning of the set.
			 */
			inline iterator begin() {
				return __set.begin() ;
			}
		
			/**
			 * Provides a pointer to the end of the set 
			 */
			inline iterator end() {
				return __set.end() ;
			}
		
			/**
			 * Provides a const pointer to the beginning of the set 
			 */
			inline const_iterator begin() const {
				return __set.begin() ;
			}
		
			/**
			 * Provides a const pointer to the end of the set 
			 */
			inline const_iterator end() const {
				return __set.end() ;
			}
		
			/**
			 * Provides a pointer to the end of the set
			 */
			inline reverse_iterator rbegin() {
				return reverse_iterator( end() ) ;
			}
		
			/**
			 * Provides a pointer to the beginning of the set
			 */
			inline reverse_iterator rend() {
				return reverse_iterator( begin() ) ;
			}
		
			/**
			 * Provides a const pointer to the end of the set
			 */
			inline const_reverse_iterator rbegin() const {
				return const_reverse_iterator( end() ) ;
			}
		
			/**
			 * Provides a const pointer to the beginning of the set
			 */
			inline const_reverse_iterator rend() const {
				return const_reverse_iterator( begin() ) ;
			}
			
		private:
		
			// The container that holds the elements of the set
			container_type __set ;

	};
	
	/**
	 * In mathematics, and more specifically set theory, the empty
	 * set is the unique set having no elements; its size or
	 * cardinality (count of elements in a set) is zero. 
	 */
	template<class T>
	class empty_set : public set<T> {
	
		public:
			empty_set() : set<T>(0) {}
	
			virtual ~empty_set() {}
	
	};

}	// end of namespace math
}	// end of namespace genecis

#endif
