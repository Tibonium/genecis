/**
 * @file array.h
 */
#pragma once

#include <genecis/container/container_io.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(container)

template<class T>
class array : public container_expression<array<T> > {
public:

	typedef array<T>			self_type ;
	typedef std::allocator<T>	allocator_type ;
	typedef T			 		value_type ;
	typedef T*				  	pointer ;
	typedef const T*		  	const_pointer ;
	typedef ptrdiff_t		  	difference_type ;
	typedef value_type&			reference ;
	typedef const value_type&	const_reference ;
	typedef size_t  			size_type ;
	typedef pointer			  	iterator ;
	typedef const_pointer		const_iterator ;
	typedef genecis_reverse_iterator<iterator>
		reverse_iterator ;
	typedef genecis_reverse_iterator<const_iterator>
		const_reverse_iterator ;

	/**
	 * Empty constructor
	 */
	array() : _begin(0), _end(0) {}

	/**
	 * Constructs an array of type T with size specificed.
	 */
	array(size_type s) {
		create_storage( s ) ;
	}
	
	/**
	 * Constructs an array of type T with size specificed and
	 * fills the array with the value c or zeros.
	 */
	array(size_type s, const value_type c) {
		create_storage( s ) ;
		std::fill_n(_begin, s, c) ;
	}
	
	/**
	 * Iterator constructor
	 */
	array(iterator It, size_type s ) {
		create_storage( s ) ;
		std::copy( It, It+s,  _begin ) ;
	}

	/**
	 * Copy constructor
	 */
	array(self_type& a) {
		create_storage( a.size() ) ;
		std::copy( a.begin(), a.end(), _begin ) ;
	}
	
	template<typename A>
	array(const container_expression<A>& a) {
		create_storage( a().size() ) ;
		genecis_assign<scalar_assign>(*this, a) ;
	}

	/**
	 * Assignment operator
	 */
	void operator=(const self_type& a) {
		mng.deallocate( _begin, size() ) ;
		this->create_storage( a.size() ) ;
		std::copy( a.begin(), a.end(), _begin ) ;
	}

	template<typename A>
	void operator=(const container_expression<A>& a) {
		mng.deallocate( _begin, size() ) ;
		create_storage( a().size() ) ;
		genecis_assign<scalar_assign>(*this, a) ;
	}

	/**
	 * Destructor
	 */
	virtual ~array() {
		mng.deallocate( _begin, size() ) ;
		_begin = NULL ;
		_end = NULL ;
	}

/**** Iterators ****/
	/**
	 * Provides a pointer to the beginning of the data stored
	 * in this class.
	 */
	inline iterator begin() {
		return _begin ;
	}

	/**
	 * Provides a pointer to the end of the data stored in this
	 * class
	 */
	inline iterator end() {
		return _end ;
	}

	/**
	 * Provides a const pointer to the beginning of the data
	 * stored in this class
	 */
	inline const_iterator begin() const {
		return _begin ;
	}

	/**
	 * Provides a const pointer to the end of the data stored
	 * in this class
	 */
	inline const_iterator end() const {
		return _end ;
	}

	/**
	 * Provides a pointer to the end of the data stored in this
	 * class
	 */
	inline reverse_iterator rbegin() {
		return reverse_iterator( end() ) ;
	}

	/**
	 * Provides a pointer to the beginning of the data
	 * stored in this class
	 */
	inline reverse_iterator rend() {
		return reverse_iterator( begin() ) ;
	}

	/**
	 * Provides a const pointer to the end of the data stored
	 * in this class
	 */
	inline const_reverse_iterator rbegin() const {
		return const_reverse_iterator( end() ) ;
	}

	/**
	 * Provides a const pointer to the beginning of the data
	 * stored in this class
	 */
	inline const_reverse_iterator rend() const {
		return const_reverse_iterator( begin() ) ;
	}

	/**
	 * Returns the number of elements in the data array
	 */
	inline size_type size() {
		return size_type( _end - _begin ) ;
	}

	inline size_type size() const {
		return size_type( _end - _begin ) ;
	}

	/**
	 * Returns a pointer to the beginning of the stored data
	 * in the class
	 */
	inline pointer data() {
		return _begin ;
	}

	inline const_pointer data() const {
		return _begin ;
	}

	/**
	 * Element accessor without bounding check
	 */
	inline reference operator() (size_type t) {
		return *( _begin + t ) ;
	}

	inline const_reference operator() (size_type t) const {
		return *( _begin + t ) ;
	}
	
	/**
	 * Element accessor with bounding check
	 */
	inline reference operator[] (size_type t) {
		try {
			if( t >= size() ) {
				throw -1 ;
			} else {
		return *( _begin + t ) ;
			}
		} catch (int e) {
			std::cout << "array::operator[] bad index value of "
					  << t << ", out of bounds error."
					  << std::endl ;
			exit(e) ;
		}
	}

	inline const_reference operator[] (size_type t) const {
		try {
			if( t >= size() ) {
				throw -1 ;
			} else {
		return *( _begin + t ) ;
			}
		} catch (int e) {
			std::cout << "array::operator[] bad index value of "
					  << t << ", out of bounds error."
					  << std::endl ;
			exit(e) ;
		}
	}

	/**
	 * Element assignment
	 */
	template<int _index>
	void operator= (value_type c) {
		operator() (_index) = c ;
	}

	/** ========== Operator overloads ========== **/
	void operator+= (const value_type& c) {
		genecis_assign<scalar_add_assign> (*this, c) ;
	}

	void operator-= (const value_type& c) {
		operator+=(-c) ;
	}

	void operator*= (const value_type& c) {
		genecis_assign<scalar_multiply_assign> (*this, c) ;
	}
	
	void operator/= (const value_type& c) {
		genecis_assign<scalar_divide_assign> (*this, c) ;
	}
	
	void operator%= (const value_type& c) {
		genecis_assign<scalar_mod_assign> (*this, c) ;
	}

	/**
	 * Squeezes the array down to an array with no zeros
	 */
	self_type squeeze() {
		size_type count = 0 ;
		for(iterator i=_begin; i!=_end; ++i) {
			if( (*i) == 0 ) ++count ;
		}
		self_type tmp( size() - count ) ;
		size_type j = 0 ;
		for(iterator i=_begin; i!=_end; ++i) {
			if( (*i) != 0 ) tmp(j) = (*i), ++j ;
		}
		return tmp ;
	}
	
	/**
	 * Pop function with random access
	 * Returns the value at index t and removes it from
	 * the parent array.
	 *
	 * @param t		index of the element in the array
	 * @return		the element at the index in the array
	 *				removed from the array.
	 */
	value_type pop(size_type t) {
		try {
			if( _begin == _end ) throw -1 ;
			value_type v = *(_begin + t) ;
			iterator first = _begin + t ;
			std::copy( first+1, _end, first ) ;
			iterator tmp = _end ;
			--_end ;
			mng.destroy( tmp ) ;
			return v ;
		} catch (int e) {
			std::cout << "array::pop(size_type): Array is empty"
					  << std::endl ;
			exit(e) ;
		}
	}
	
	/**
	 * Resizes the array to a new size
	 *
	 * @param s		new size of the array
	 * @param copy	preserve data in the array. If true, data
	 *				is copied up to min(size,new size), and
	 * 				zeros are placed in all empty entries. If
	 *				false, the array entries are set to zero.
	 */
	void resize(size_type s, bool copy=false) {
		if( copy ) {
			iterator __tmp ;
			__tmp = mng.allocate( s ) ;
			size_type n = std::min( size(), s ) ;
			std::copy( _begin, _begin+n, __tmp ) ;
			if( n < s ) std::fill_n( __tmp+n, s-n, 0 ) ;
			mng.deallocate( _begin, size() ) ;
			_begin = __tmp ;
			_end = __tmp + s ;
		} else {
			mng.deallocate( _begin, size() ) ;
			create_storage( s ) ;
			std::fill_n( _begin, s, 0 ) ;
		}
	}

	/**
	 * Clears the data and replaces it with the casted zero type
	 */
	void clear() {
		std::fill_n( _begin, size(), 0 ) ;
	}

private:
	// begin and end of the data stored in this class
	iterator _begin ;
	iterator _end ;
	allocator_type mng ;

	void create_storage(size_type __n) {
		_begin = mng.allocate( __n ) ;
		_end = _begin + __n ;
	}

};

END_NAMESPACE
END_NAMESPACE
