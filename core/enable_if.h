#ifndef __ENABLE_IF_H__
#define __ENABLE_IF_H__

template<bool B, class T = void>
struct enable_if_base
{
   typedef T   type;
};

template<class T>
struct enable_if_base<false,T> {};

// enable_if implementation
template<class Cond, class T = void>
struct enable_if : public enable_if_base<Cond::value,T> {};

template<bool B, class T = void>
struct disable_if_base
{
   typedef T   type;
};

template<class T>
struct disable_if_base<true,T> {};

template<class Cond, class T>
struct disable_if : public disable_if_base<Cond::value,T> {};

#endif /* __ENABLE_IF_H__ */
