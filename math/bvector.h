/**
 * @file bvector.h
 */
 
#ifndef GENECIS_MATH_BVECTOR
#define GENECIS_MATH_BVECTOR

#include <genecis/math/vector_io.h>

namespace genecis {
namespace math {

	template<typename T>
	class bvector : public vector_expression<bvector, T> {

		public:
	
			typedef T		value_type ;
	

			/**
			 * Constructor for a vector in cartesian coordinates
			 *
			 * @param x 	x component
			 * @param y 	y component
			 * @param z 	z component
			 */
			bvector(value_type x=0.0, value_type y=0.0, value_type z=0.0) {
				_u1 = x ;
				_u2 = y ;
				_u3 = z ;
			}
		
			// Destructor
			virtual ~bvector() {}

			/**
			 * Returns the inner product of two bvectors
			 *
			 *  dot product =
			 *		x*x + y*y + z*z
			 */
			value_type dot(const bvector& other) const {
				value_type result = ( _u1 * other.u1() + 
							   _u2 * other.u2() +
							   _u3 * other.u3() ) ;
				return result ;
			}

			/**
			 * Returns the cross product of two math_vectors, with
			 * basis vectors that are linearly independent.
			 *
			 *  Cross product =
			 *			| i   j   k  |
			 *		det	| u1  u2  u3 |   =
			 *			| v1  v2  v3 |
			 * 
			 *  (u2*v3-u3*v2) i - (u1*v3-u3*v1) j + (u1*v2-u2*v1) k
			 */
			bvector cross(const bvector& v) const {
				value_type u1 = _u2 * v.u3() - _u3 * v.u2() ;
				if( abs(u1) < 1e-20 ) u1 = 0 ;
				value_type u2 = _u1 * v.u3() - _u3 * v.u1() ;
				u2 *= -1.0 ;
				if( abs(u2) < 1e-20 ) u2 = 0 ;
				value_type u3 = _u1 * v.u2() - _u2 * v.u1() ;
				if( abs(u3) < 1e-20 ) u3 = 0 ;
				return bvector(u1,u2,u3) ;
			}

			/**
			 * Adds two bvectors together
			 */
			bvector operator+ (const bvector& rhs) const {
				return bvector(_u1+rhs.u1(),_u2+rhs.u2(),_u3+rhs.u3()) ;
			}
			
			/**
			 * Adds two bvectors together
			 */
			bvector operator- (const bvector& rhs) {
				bvector tmp = rhs ;
				tmp = tmp * -1 ;
				return operator+(tmp) ;
			}
			
			/** =========== Scalar Operations =========== **/
			bvector operator* (const value_type& c) {
				return bvector(_u1*c,_u2*c,_u3*c) ;
			}
			
			bvector operator+ (const value_type& c) {
				return bvector(_u1+c,_u2+c,_u3+c) ;
			}

			bvector operator- (const value_type& c) {
				return bvector(_u1-c,_u2-c,_u3-c) ;
			}

			bvector operator/ (const value_type& c) {
				return bvector(_u1/c,_u2/c,_u3/c) ;
			}
			
			/**
			 * Functions for accessing and modifying the first component
			 */
			value_type u1() const {
				return _u1 ;
			}

			void u1(value_type _t) {
				_u1 = _t ;
			}
		
			/**
			 * Functions for accessing and modifying the second component
			 */
			value_type u2() const {
				return _u2 ;
			}
		
			void u2(value_type _t) {
				_u2 = _t ;
			}
		
		
			/**
			 * Functions for accessing and modifying the third component
			 */
			value_type u3() const {
				return _u3 ;
			}
		
			void u3(value_type _t) {
				_u3 = _t ;
			}
			
					
		protected:
		
			value_type _u1 ;
			value_type _u2 ;
			value_type _u3 ;

	};

}	// end of namespace math
}	// end of namespace genecis

#endif
