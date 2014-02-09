/**
 * @file ovector.h
 */
 
#ifndef MATH_OVECTER_H
#define MATH_OVECTER_H

#include "math_vector.h"
#include "bvector.h"
/// THIS CLASS, OMNIVECTORS, DOES NOT WORK. DO NOT INSTANTIATE IT!

template <typename _T>
class ovector : public math_vector<_T>  {

	private:
	
		/** Base vectors for this space */
		static bvector _b1 ;
		static bvector _b2 ;
		static bvector _b3 ;

	public:
	
		/**
		 * Calculate the generalized dot product for vectors
		 * u = u1 /hat{b1} + u2 /hat{b2} + u3 /hat{b3}
		 * v = v1 /hat{b1} + v2 /hat{b2} + v3 /hat{b3}
		 *
		 * u dot v = u1*v1 (b1 dot b1) + u1*v2 (b1 dot b2) + u1*v3 (b1 dot b3) +
		 *		   u2*v1 (b2 dot b1) + u2*v2 (b2 dot b2) + u2*v3 (b2 dot b3) +
		 *		   u3*v1 (b3 dot b1) + u3*v2 (b3 dot b2) + u3*v3 (b3 dot b3)
		 *
		 *		 = u1*v1 (b1 dot b1) + u2*v2 (b2 dot b2) + u3*v3 (b3 dot b3) +
		 *		   2*u1*v2 (b1 dot b2) + 2*u1*v3 (b1 dot b3) + 2*u2*v3 (b2 dot b3)
		 */
		virtual inline _T dot(const math_vector<_T>& other) const {
			_T result = ( this->_u1 * other.u1() * this->_b1.dot(this->_b1) +
					    this->_u2 * other.u2() * this->_b2.dot(this->_b2) +
					    this->_u3 * other.u3() * this->_b3.dot(this->_b3) +
					    2.0 * ( this->_u1 * other.u2() * this->_b1.dot(this->_b2) ) +
					    2.0 * ( this->_u1 * other.u3() * this->_b1.dot(this->_b3) ) +
					    2.0 * ( this->_u2 * other.u3() * this->_b2.dot(this->_b3) ) ) ;
			return result ;
		}
	
		/**
		 * Constructor a generalized vector space from
		 * three orthogonal vectors
		 *
		 * @param u1	first component of the vector space
		 * @param u2	second component of the vector space
		 * @param u3	third component of the vector space
		 * @param base	three math_vectors to use as the 
		 *			bases for this vector space. They
		 *			need not be linearly independent or
		 *			unitary.
		 */
		ovector(_T u1, _T u2, _T u3, bvector b1, bvector b2, bvector b3) {
			this->_u1 = u1 ;
			this->_u2 = u2 ;
			this->_u3 = u3 ;
			this->_b1 = b1 ;
			this->_b2 = b2 ;
			this->_b3 = b3 ;
		}
		
		// Destructor
		virtual ~ovector() {}
		
		friend std::ostream& operator<< (std::ostream& os, const ovector<_T>& other) {
			os << "[u1,u2,u3]: ("
			   << other.u1() << ", "
			   << other.u2() << ", "
			   << other.u3() << ")"
			   << "\n[b1,b2,b3]: ( "
			   << _b1 << ", " << _b2
			   << ", " << _b3 << " )" ;
			   return os ;
		}

};

#endif
