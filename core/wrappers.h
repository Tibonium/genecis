#ifndef __TYPE_WRAPPER_H__
#define __TYPE_WRAPPER_H__

template<class T>
struct type_wrapper
{
   typedef T type;
};

template<class U, U>
struct type_check {};

template<class U>
struct name_wrapper
{
   static const char* name() { return U::name; }
};

template<>
struct name_wrapper<int>
{
   static const char* name() { return "int"; }
};

#endif /* __TYPE_WRAPPER_H__ */
