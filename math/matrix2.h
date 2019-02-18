#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math/row_major.h>
#include <algorithm>

template<class T, class I=row_major>
class matrix
{
public:
   typedef T            value_type;
   typedef T&           reference;
   typedef const T&     const_reference;
   typedef T*           pointer;
   typedef I            index_type;
   typedef typename I::size_type size_type;

   matrix(size_type n, size_type m, value_type v=value_type()) :
      _n(n), _m(m), _index(n,m)
   {
      initialize(v);
   }
   
   reference operator()(size_type i, size_type j)
   {
      return _data[_index(i,j)];
   }

   const_reference operator()(size_type i, size_type j) const
   {
      return _data[_index(i,j)];
   }
   
   pointer data()
   {
      return _data;
   }
   
protected:
   void initialize(const value_type& v)
   {
      _data = new value_type[_n*_m];
      std::fill_n(_data,_n*_m,v);
      //for(size_type i=0; i<_n; ++i)
      //{
      //   for(size_type j=0; j<_m; ++j)
      //   {
      //      _data[_index(i,j)] = v;
      //   }
      //}
   }

   size_type _n;
   size_type _m;
   pointer _data;
   index_type _index;
}; // end class matrix

#endif /* _MATRIX_H_ */ 
