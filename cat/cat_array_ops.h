// -\*- C\+\+ -\*-
/*

Copyright 2005 Manuel Baptista

This file is part of cat++

cat++ is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

cat++ is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

//Implements field operations based on Blitz++

#ifndef CAT_ARRAY_OPS_H
#define CAT_ARRAY_OPS_H


#include "cat_tvector.h"
#include "cat_array.h"
#include "cat_array_macros.h"
#include "cat_promote.h"


#include<complex>
#include<iostream>
#include<string>
using namespace std;




//Unary -

template <class T,int N>
inline cat_tvector<T,N>
operator -(const cat_tvector<T,N>& rhs)
{
  cat_tvector<T,N> out(rhs);
  for (int i=0;i<N;++i)
    out[i]=-rhs[i];
  return cat_tvector<T,N>(out);
};

template <class T,int D>
inline cat_array<T,D>
operator -(const cat_array<T,D>& rhs)
{
  cat_array<T,D> out(rhs);
  cat_array_iterator<T,D> out_iterator(out);
  cat_array_const_iterator<T,D> rhs_iterator(rhs);
  for (out_iterator=out.begin(),
       rhs_iterator=rhs.begin();
       out_iterator!=out.end(),
       rhs_iterator!=rhs.end();
       ++out_iterator,
       ++rhs_iterator)
    (*out_iterator) = -(*rhs_iterator);
  return cat_array<T,D>(out);
};



#define CAT_BINARY_OPERATOR(op) \
template <class T1,class T2> \
inline typename cat_promote_traits<T1,T2>::T_promote \
operator op(const T1 & lhs,const T2 & rhs) \
{ \
  return typename cat_promote_traits<T1,T2>::T_promote(lhs) op##= rhs; \
}


CAT_BINARY_OPERATOR(+)
CAT_BINARY_OPERATOR(-)
CAT_BINARY_OPERATOR(*)
CAT_BINARY_OPERATOR(/)








//under implementation

#define CAT_BINARY_OPERATOR_ELEMENT(op) \
template <class T,class T1,int D> \
cat_array<typename cat_promote_traits<T,T1>::T_promote,D> operator op(const cat_array<T,D> & a,const T1 & b) \
{ \
 cat_array<typename cat_promote_traits<T,T1>::T_promote,D> out(a); \
 cat_array_iterator<typename cat_promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=*a_iterator op b; \
 return out; \
} \
template <class T,class T1,int D> \
cat_array<typename cat_promote_traits<T,T1>::T_promote,D> operator op(const T1 & a,const cat_array<T,D> & b) \
{ \
 cat_array<typename cat_promote_traits<T,T1>::T_promote,D> out(b); \
 cat_array_iterator<typename cat_promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 cat_array_const_iterator<T,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++b_iterator) \
   *out_iterator=a op *b_iterator; \
 return out; \
} 

// CAT_BINARY_OPERATOR_ELEMENT(+)
// CAT_BINARY_OPERATOR_ELEMENT(-)
// CAT_BINARY_OPERATOR_ELEMENT(*)
// CAT_BINARY_OPERATOR_ELEMENT(/)




#endif
