/**
 * @file ovector.h
 */
 
#ifndef MATH_OVECTER_H
#define MATH_OVECTER_H

template <typename _T>
class ovector : public math_vector<_T>  {

	public:
	
		virtual inline _T dot(const math_vector<_T>& other) const {
			_T result = ( this->_u1 * other.u1() +
					    this->_u2 * other.u2() +
					    this->_u3 * other.u3() ) ;
			return result ;
		}
	
		/**
		 * Constructor a generalized vector space from
		 * three orthogonal vectors
		 *
		 * @param u1	first component of the vector space
		 * @param u2	second component of the vector space
		 * @param u3	third component of the vector space
		 */
		ovector(_T u1, _T u2, _T u3) {
			this->_u1 = u1 ;
			this->_u2 = u2 ;
			this->_u3 = u3 ;
		}
		
		// Destructor
		virtual ~ovector() {}
		
		friend std::ostream& operator<< (std::ostream& os, const ovector<_T>& other) {
			os << "[u1,u2,u3]: ("
			   << other.u1() << ", "
			   << other.u2() << ", "
			   << other.u3() << ")" ;
			   return os ;
		}

};

#endif
