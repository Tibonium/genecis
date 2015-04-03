/**
 * @file casting.h
 * A class that defines many useful ways of casting
 * types and redefining type casts on per-use basis.
 */
#pragma once

namespace genecis {
namespace base {

/***** Remove type templates *****/
template<class T>
struct remove_const {
    typedef T type;
};

template<class T>
struct remove_const<const T> {
    typedef T type;
};

// remove volatile Template
template<class T>
struct remove_volatile {
    typedef T type;
};

// remove volatile
template<class T>
struct remove_volatile<volatile T> {
    typedef T type;
};

// remove pointer Template
template<class T>
struct remove_pointer {
    typedef T type;
};

// remove pointer
template<class T>
struct remove_pointer<T*> {
    typedef T type;
};

// remove reference Template
template<class T>
struct remove_reference {
    typedef T type;
};

// remove reference
template<class T>
struct remove_reference<T&> {
    typedef T type;
};

// Remove rvalue reference
template<class T>
struct remove_reference<T&&> {
    typedef T type;
};


template<class T>
struct remove_cv {
    typedef typename remove_const<
            typename remove_volatile<T>::type
            >::type type;
};

/***** Add type templates *****/
template<class T>
struct add_const {
    typedef const T type;
};

template<class T>
struct add_volatile {
    typedef volatile T type;
};

template<class T>
struct add_cv {
    typedef const volatile T type;
};

template<class T>
struct add_reference {
    typedef T& type;
};

template<class T>
struct add_pointer {
    typedef typename remove_reference<T>::type *type;
};

}   // end of namespace base
}   // end of namespace genecis
