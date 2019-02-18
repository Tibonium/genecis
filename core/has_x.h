#ifndef __HAS_X_H__
#define __HAS_X_H__

#include <wrappers.h>
#include <core/metalogical.h>
#include <core/preprocessor.h>

//#define USE_WEAK_CHECK

#ifdef USE_WEAK_CHECK
   // Has typedef
#  define HAS_TYPEDEF( trait )                                    \
   template<class T>                                              \
   struct PP_CAT(has_,trait)                                      \
   {                                                              \
      struct weak                                                 \
      {                                                           \
         template<class U>                                        \
         static yes_tag test(type_wrapper<U> const volatile*,     \
            type_wrapper<typename U::trait>* = 0);                \
         static no_tag test(...);                                 \
      };                                                          \
      static const bool value =                                   \
         ( sizeof(weak::test(static_cast<type_wrapper<T>*>(0)))   \
            == sizeof(yes_tag) );                                 \
      typedef integral_const<bool,value> type;                    \
   };

#  define EXTRACT_TRAIT( trait )                                  \
   HAS_TYPEDEF( trait )                                           \
   template<class U, bool B = PP_CAT(has_,trait)<U>::value>       \
   struct PP_CAT(extract_,trait)                                  \
   {};                                                            \
   template<class U>                                              \
   struct PP_CAT(extract_,trait)<U,true>                          \
   { typedef typename U::trait type; };
#else
#  define EXTRACT_TRAIT( trait )          \
   template<class U>                      \
   struct PP_CAT(extract_,trait)          \
   { typedef typename U::trait type; };
#endif

#define HAS_MEMBER( member )                                         \
template<class T>                                                    \
struct PP_CAT(has_member_,member)                                    \
{                                                                    \
   struct fallback {int member;};                                    \
   struct derived : T, fallback {};                                  \
   template<class U>                                                 \
   static no_tag test(type_check<int fallback::*,&U::member>*);      \
   template<class U>                                                 \
   static yes_tag test(...);                                         \
   static const bool value =                                         \
      sizeof(test<derived>(0)) == sizeof(yes_tag);                   \
};

#endif /* __HAS_X_H__ */
