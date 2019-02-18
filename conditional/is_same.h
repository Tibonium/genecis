#ifndef __IS_SAME_H__
#define __IS_SAME_H__

#include <core/metalogical.h>

// is_same implementation
template<class T, class U>
struct is_same : public false_type {};

template<class T>
struct is_same<T,T> : public true_type {};

#endif /* __IS_SAME_H__ */
