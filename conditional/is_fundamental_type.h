#ifndef __IS_FUNDAMENTAL_TYPE_H__
#define __IS_FUNDAMENTAL_TYPE_H__

#include <core/metalogical.h>

// is_fundamental_type
template<class T>
struct is_fundamental_type : public false_type {};

template<>
struct is_fundamental_type<int> : public true_type {};

template<>
struct is_fundamental_type<double> : public true_type {};

template<>
struct is_fundamental_type<float> : public true_type {};

template<>
struct is_fundamental_type<long> : public true_type {};

template<>
struct is_fundamental_type<std::size_t> : public true_type {};

template<>
struct is_fundamental_type<bool> : public true_type {};

#endif /* __IS_FUNDAMENTAL_TYPE_H__ */
