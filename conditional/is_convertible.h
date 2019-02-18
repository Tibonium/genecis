#ifndef __IS_CONVERTIBLE_H__
#define __IS_CONVERTIBLE_H__

#include <core/metalogical.h>

// is_convertible implementation
template<class T, class F>
struct is_convertible : public false_type {};

template<class T>
struct is_convertible<T,T> : public true_type {};

template<>
struct is_convertible<std::size_t,int> : public true_type {};

template<>
struct is_convertible<std::size_t,long> : public true_type {};

template<>
struct is_convertible<std::size_t,double> : public true_type {};

template<>
struct is_convertible<std::size_t,float> : public true_type {};

template<>
struct is_convertible<int,double> : public true_type {};

template<>
struct is_convertible<double,int> : public true_type {};

template<>
struct is_convertible<int,float> : public true_type {};

template<>
struct is_convertible<float,int> : public true_type {};

template<>
struct is_convertible<double,float> : public true_type {};

template<>
struct is_convertible<float,double> : public true_type {};

template<>
struct is_convertible<long,double> : public true_type {};

template<>
struct is_convertible<double,long> : public true_type {};

template<>
struct is_convertible<long,float> : public true_type {};

template<>
struct is_convertible<float,long> : public true_type {};

#endif /* __IS_CONVERTIBLE_H__ */
