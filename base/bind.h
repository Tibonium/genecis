/**
 * @file allows the binding of functions and classes
 */
#pragma once

namespace genecis {
namespace base {

template<class T> class alias_base{};

template<class R, class F>
class f_arg0 : public alias_base<f_arg0<R,F> >
{
public:
    typedef R  result_type ;
    // constructor
    f_arg0( F f ) : __f(f) {}
    result_type operator() ()
    {
        return __f() ;
    }
    result_type operator() () const
    {
        return __f() ;
    }
private:
    F f ;
};

template<class R, class A1, class F>
class f_arg1 : public alias_base<f_arg1<R,A1,F> >
{
public:
    typedef R result_type ;
    // constructor
    f_arg1( F f ) : __f(f) {}
    result_type operator() ( A1 a1 )
    {
        return __f(a1) ;
    }
    result_type operator() ( A1 a1 ) const
    {
        return __f(a1) ;
    }
private:
    F f ;
};

template<class R, class A1, class A2, class F>
class f_arg2 : public alias_base<f_arg2<R,A1,A2,F> >
{
public:
    typedef R result_type ;
    // constructor
    f_arg2( F f ) : __f(f) {}
    result_type operator() ( A1 a1, A2 a2 )
    {
        return __f(a1,a2) ;
    }
    result_type operator() ( A1 a1, A2 a2 ) const
    {
        return __f(a1,a2) ;
    }
private:
    F f ;
};

template<class R, class A1, class A2, class A3, class F>
class f_arg3 : public alias_base<f_arg3<R,A1,A2,A3,F> >
{
public:
    typedef R result_type ;
    // constructor
    f_arg3( F f ) : __f(f) {}
    result_type operator() ( A1 a1, A2 a2, A3 a3 )
    {
        return __f(a1,a2,a3) ;
    }
    result_type operator() ( A1 a1, A2 a2, A3 a3 ) const
    {
        return __f(a1,a2,a3) ;
    }
private:
    F f ;
};

template<class R, class A1, class A2, class A3, class A4, class F>
class f_arg4 : public alias_base<f_arg4<R,A1,A2,A3,A4,F> >
{
public:
    typedef R result_type ;
    // constructor
    f_arg4( F f ) : __f(f) {}
    result_type operator() ( A1 a1, A2 a2, A3 a3, A4 a4 )
    {
        return __f(a1,a2,a3,a4) ;
    }
    result_type operator() ( A1 a1, A2 a2, A3 a3, A4 a4 ) const
    {
        return __f(a1,a2,a3,a4) ;
    }
private:
    F f ;
};

template<class R, class A1, class A2, class A3, class A4, class A5, class F>
class f_arg5 : public alias_base<f_arg5<R,A1,A2,A3,A4,A5,F> >
{
public:
    typedef R result_type ;
    // constructor
    f_arg5( F f ) : __f(f) {}
    result_type operator() ( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 )
    {
        return __f(a1,a2,a3,a4,a5) ;
    }
    result_type operator() ( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
    {
        return __f(a1,a2,a3,a4,a5) ;
    }
private:
    F f ;
};


}   // end of namespace base
}   // end of namespace genecis
