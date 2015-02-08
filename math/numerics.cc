/**
 * @file numerics.cc
 */
 
#include <genecis/math/numerics.h>

using namespace genecis::math ;
typedef numerics::value_type    value_type ;

/**
 * Stirling's approximation for n!
 * when n is large.
 */
value_type
numerics::stirling_approx( const value_type& N )
{
    return exp( N * log(N) - N )
            * N * sqrt( 2.0*M_PI/N ) ;
}

/**
 * Computes the factorial of n
 */
value_type
numerics::factorial( const value_type& n )
{
    if( n < 2.0 ) {
        return 1.0 ;
    } else {
        return n*factorial(n-1) ;
    }
}
