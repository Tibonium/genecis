/**
 * @file genecis_iterator_types.h
 */
 
#ifndef GENECIS_BASE_GENECIS_ITERATOR_TYPES_H
#define GENECIS_BASE_GENECIS_ITERATOR_TYPES_H

namespace genecis {
namespace base {

	///  Marking input iterators.
	struct input_iterator_tag { };

	///  Marking output iterators.
	struct output_iterator_tag { };

	/// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag { };

	/// Bidirectional iterators support a superset of forward iterator
	/// operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	/// Random-access iterators support a superset of bidirectional
	/// iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template<typename _cat, typename _T, typename _dist = ptrdiff_t,
		typename _ptr = _T*, typename _ref = _T&>
	struct iterator {
		typedef _cat	iterator_category ;
		typedef _T		value_type ;
		typedef _dist	difference_type ;
		typedef _ptr	pointer ;
		typedef _ref	reference ;		 
	};

	template<typename _Iter> struct iterator_traits {
		typedef typename _Iter::iterator_category	iterator_category ;
		typedef typename _Iter::value_type			value_type ;
		typedef typename _Iter::difference_type		difference_type ;
		typedef typename _Iter::pointer				pointer ;
		typedef typename _Iter::reference			reference ;
	};

	template<typename _T> struct iterator_traits<_T*> {
		typedef random_access_iterator_tag	iterator_category ;
		typedef _T							value_type ;
		typedef ptrdiff_t					difference_type ;
		typedef _T*							pointer ;
		typedef _T&							reference ;
	};

	template<typename _T> struct iterator_traits<const _T*> {
		typedef random_access_iterator_tag	iterator_category ;
		typedef _T							value_type ;
		typedef ptrdiff_t					difference_type ;
		typedef const _T*					pointer ;
		typedef const _T&					reference ;
	};

}	// end of namespace base
}	// end of namespace genecis
#endif
