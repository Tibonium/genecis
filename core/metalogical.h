#ifndef __METALOGICAL_H__
#define __METALOGICAL_H__

#include <cstddef>

// Integral const struct
template<class T, T val>
struct integral_const
{
   static const T value = val;
};

// true/false_type typedef
typedef integral_const<bool,true>   true_type;
typedef integral_const<bool,false>  false_type;

// yes/no tags
typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

// and conditional
template<bool T, bool U>
struct __and_ : public false_type {};

template<bool B>
struct __and_<B,B> : public true_type {};

// or conditional
template<bool T, bool U>
struct __or_ : public false_type {};

template<>
struct __or_<true,false> : public true_type {};

template<>
struct __or_<false,true> : public true_type {};

template<>
struct __or_<true,true> : public true_type {};

// if conditional
template<bool B, class T, class F>
struct __if_base_
{
   typedef F   type;
};

template<class T, class F>
struct __if_base_<true,T,F>
{
   typedef T   type;
};

template<class Cond, class T, class F>
struct __if_ : public __if_base_<Cond::value,T,F> {};

template<bool B, class T, class F>
struct __if_not_base
{
   typedef F   type;
};

template<class T, class F>
struct __if_not_base<true,T,F>
{
   typedef T   type;
};

template<class Cond, class T, class F>
struct __if_not : public __if_not_base<Cond::value,T,F> {};

// not operation
template<bool B>
struct __not_base_ : public integral_const<bool,!B> {};

template<class Cond>
struct __not_ : public __not_base_<Cond::value> {};

#endif /* __METALOGICAL_H__ */
