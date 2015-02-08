/**
 * @example numerics_test.cc
 */

#include <genecis/math/numerics.h>
#include <iostream>

using namespace genecis::math ;

int main() {
    
    double r = 5.0 ;
    double result = numerics::factorial(r) ;
    cout << r << "! = " << result << endl ;
    
    r = 100.0 ;
    double eps = 0.001 ;
    double stirling = numerics::stirling_approx(r) ;
    double fact = numerics::factorial(r) ;
    cout << "The result of " << r << "!:" << endl ;
    cout << "Stirling's approximation: " << stirling << endl ;
    cout << "Factorial: " << fact << endl ;
    if( (1.0 - stirling/fact) < eps ) {
        cout << "The two values are within epsilon, " << eps << endl ;
    } else {
        cout << "The two values are not within epsilon, " << eps << endl ;
    }
}
