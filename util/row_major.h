#ifndef _ROWMAJOR_H_ 
#define _ROWMAJOR_H_

#include <cstddef>
#include <stdexcept>

class row_major
{
public:
   typedef std::size_t  size_type;
   
   row_major(size_type i, size_type j) :
      _i(i), _j(j)
   {}
   
   size_type operator()(size_type i, size_type j) const
   {
      if(_i < i)
      {
         throw std::invalid_argument("Invalid index i");
      }
      if(_j < j)
      {
         throw std::invalid_argument("Invalid index j");
      }
      return j + _j * i;
   }
protected:
   size_type _i;
   size_type _j;
}; // end class row_major

#endif /* _ROWMAJOR_H_ */
