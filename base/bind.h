/**
 * @file allows the binding of functions and classes
 */
#pragma once

namespace genecis {
namespace base {

template<class T> class bind_base{};

template<class T1, class T2>
struct bind2 : public bind_base<bind2<T1,T2> >
{
public:
    typedef T1  bound_obj ;
    typedef T2  bind_to ;
    typedef bound_obj::result_type  result_type ;
    typedef bound_obj::value_type   value_type ;
    // constructor
    bind2( const bound_obj& t1, const bind_to& t2 )
        : __t1(t1), __t2(t2)
    {}
    static result_type apply( value_type a ) {
        return bound_obj::apply( a ) ;
    }
    static bind_to get() { return __t2 ; }
private:
    bound_obj __t1 ;
    bind_to __t2 ;
};

}   // end of namespace base
}   // end of namespace genecis
