// -*- C++ -*-
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

#include "array.h"
#include "array_macros.h"

#include "../tiny/tiny.h"
#include "../traits/traits.h"

#include "array_expression.h"
#include "../opstructs.h"

#include<complex>
#include<iostream>
#include<string>
using namespace std;

namespace cat
{

  //Unary -
  
  template <class T,int N>
  inline tvector<T,N>
  operator -(const tvector<T,N>& rhs)
  {
    tvector<T,N> out(rhs);
    for (int i=0;i<N;++i)
      out[i]*=-1;
    return out;
  }

  template <class T,int D>
  inline array<T,D>
  operator -(const array<T,D>& rhs)
  {
    array<T,D> out(rhs.shape());
    typename array<T,D>::iterator out_iterator(out);
    typename array<T,D>::const_iterator rhs_iterator(rhs);
    for (out_iterator=out.begin(),
	   rhs_iterator=rhs.begin();
	 out_iterator!=out.end(),
	   rhs_iterator!=rhs.end();
	 ++out_iterator,
	   ++rhs_iterator)
      (*out_iterator) = -(*rhs_iterator);
    return out;
  }




#define CAT_BINARY_OPERATOR(opsname,op)					\
  template <class T1,class T2,int D>					\
  inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,T2>,typename array<T1,D>::iterator,typename array<T2,D>::iterator> > \
  operator op(const cat::array<T1,D> & lhs,const cat::array<T2,D> & rhs) \
  {									\
    typedef ArrayExpressionBinOp<opsname<T1,T2>,typename array<T1,D>::iterator,typename array<T2,D>::iterator>  ExpressionT; \
    return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs.begin())); \
  };									

// \
//     template <class T1,int D,class ET>					\
//     inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,typename ET::returnT>,typename array<T1,D>::iterator,ET> > \
//     operator op(const cat::array<T1,D> & lhs,const ET & rhs)		\
//     {									\
//       typedef ArrayExpressionBinOp<opsname<T1,typename ET::returnT>,typename array<T1,D>::iterator,typename ET>  ExpressionT; \
//       return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs));	\
//     };





#if 0

#define CAT_BINARY_OPERATOR(op)				\
  template <class T1,class T2>				\
  inline typename promote_traits<T1,T2>::T_promote		\
  operator op(const T1 & lhs,const T2 & rhs)			\
  {								       \
    return (typename promote_traits<T1,T2>::T_promote(lhs) op##= rhs);	\
  }									\
    template <class T1,class T2,int D>					\
  inline cat::array<typename promote_traits<T1,T2>::T_promote,D>	\
  operator op(const cat::array<T1,D> & lhs,const cat::array<T2,D> & rhs) \
  {									\
    cat::array<typename promote_traits<T1,T2>::T_promote,D> out(lhs.shape()); \
	typename array<typename promote_traits<T1,T2>::T_promote,D>::iterator out_iterator(out); \
	typename array<T1,D>::const_iterator lhs_iterator(lhs);			\
	typename array<T2,D>::const_iterator rhs_iterator(rhs);			\
    for (out_iterator=out.begin(),					\
	   lhs_iterator=lhs.begin(),					\
	   rhs_iterator=rhs.begin();					\
	 out_iterator!=out.end(),					\
	   lhs_iterator!=lhs.end(),					\
	   rhs_iterator!=rhs.end(); 					\
	 ++out_iterator,						\
	   ++lhs_iterator,						\
	   ++rhs_iterator)						\
      (*out_iterator) = static_cast<typename promote_traits<T1,T2>::T_promote>(*lhs_iterator) op static_cast<typename promote_traits<T1,T2>::T_promote>(*rhs_iterator); \
    return out;								\
  }									\
    template <class T1,class T2,int D>					\
    inline cat::array<typename promote_traits<T1,T2>::T_promote,D>	\
    operator op(const cat::array<T1,D> & lhs,const T2 & rhs)		\
    {									\
      cat::array<typename promote_traits<T1,T2>::T_promote,D> out(lhs.shape()); \
	typename array<typename promote_traits<T1,T2>::T_promote,D>::iterator out_iterator(out); \
	typename array<T2,D>::const_iterator lhs_iterator(lhs);			\
      for (out_iterator=out.begin(),					\
	     lhs_iterator=rhs.begin();					\
	   out_iterator!=out.end(),					\
	     lhs_iterator!=rhs.end();					\
	   ++out_iterator,						\
	     ++lhs_iterator)						\
	(*out_iterator) = typename promote_traits<T1,T2>::T_promote(*lhs_iterator) op typename promote_traits<T1,T2>::T_promote(rhs); \
      return out;							\
    }									\
    template <class T1,class T2,int D>					\
    inline cat::array<typename promote_traits<T1,T2>::T_promote,D>	\
    operator op(const T1 & lhs,const cat::array<T2,D> & rhs)		\
    {									\
      cat::array<typename promote_traits<T1,T2>::T_promote,D> out(rhs.shape()); \
	typename array<typename promote_traits<T1,T2>::T_promote,D>::iterator out_iterator(out); \
	typename array<T2,D>::const_iterator rhs_iterator(rhs);			\
      for (out_iterator=out.begin(),					\
	     rhs_iterator=rhs.begin();					\
	   out_iterator!=out.end(),					\
	     rhs_iterator!=rhs.end();					\
	   ++out_iterator,						\
	     ++rhs_iterator)						\
	(*out_iterator) = typename promote_traits<T1,T2>::T_promote(lhs) op typename promote_traits<T1,T2>::T_promote(*rhs_iterator); \
      return out;							\
    }	

#endif

// 								\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const T1 & lhs,const typename multicomponent_traits<T1>::T_element & rhs) \
//     {									\
//       T1 out(lhs);							\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       for (out_iterator=out.begin();					\
// 	   out_iterator!=out.end();					\
// 	   ++out_iterator)						\
// 	(*out_iterator) op##= rhs;					\
//       return out;							\
//     }									\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const typename multicomponent_traits<T1>::T_element & lhs,const T1 rhs) \
//     {									\
//       T1 out(rhs.shape());						\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       typename array<T1,D>::const_iterator rhs_iterator(rhs);			\
//       for (out_iterator=out.begin(),					\
// 	     rhs_iterator=rhs.begin();					\
// 	   out_iterator!=out.end(),					\
// 	     rhs_iterator!=rhs.end();					\
// 	   ++out_iterator,						\
// 	     ++rhs_iterator)						\
// 	(*out_iterator) = lhs op (*rhs_iterator);			\
//       return out;							\
//     }									\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const T1 & lhs,const typename numeric_traits<T1>::T_element & rhs) \
//     {									\
//       T1 out(lhs);							\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       for (out_iterator=out.begin();					\
// 	   out_iterator!=out.end();					\
// 	   ++out_iterator)						\
// 	(*out_iterator) op##= rhs;					\
//       return out;							\
//     }									\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const typename numeric_traits<T1>::T_element & lhs,const T1 rhs) \
//     {									\
//       T1 out(rhs.shape());						\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       typename array<T1,D>::const_iterator rhs_iterator(rhs);			\
//       for (out_iterator=out.begin(),					\
// 	     rhs_iterator=rhs.begin();					\
// 	   out_iterator!=out.end(),					\
// 	     rhs_iterator!=rhs.end();					\
// 	   ++out_iterator,						\
// 	     ++rhs_iterator)						\
// 	(*out_iterator) = lhs op (*rhs_iterator);			\
//       return out;							\
//     }									\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const T1 & lhs,const typename real_numeric_traits<T1>::T_element & rhs) \
//     {									\
//       T1 out(lhs);							\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       for (out_iterator=out.begin();					\
// 	   out_iterator!=out.end();					\
// 	   ++out_iterator)						\
// 	(*out_iterator) op##= rhs;					\
//       return out;							\
//     }									\
//     template <class T1,int D>						\
//     inline T1								\
//     operator op(const typename real_numeric_traits<T1>::T_element & lhs,const T1 rhs) \
//     {									\
//       T1 out(rhs.shape());						\
//       typename array<T1,D>::iterator out_iterator(out);				\
//       typename array<T1,D>::const_iterator rhs_iterator(rhs);			\
//       for (out_iterator=out.begin(),					\
// 	     rhs_iterator=rhs.begin();					\
// 	   out_iterator!=out.end(),					\
// 	     rhs_iterator!=rhs.end();					\
// 	   ++out_iterator,						\
// 	     ++rhs_iterator)						\
// 	(*out_iterator) = lhs op (*rhs_iterator);			\
//       return out;							\
//     }	
  
  CAT_BINARY_OPERATOR(Add,+);
  CAT_BINARY_OPERATOR(Subtract,-);
  CAT_BINARY_OPERATOR(Multiply,*);
  CAT_BINARY_OPERATOR(Divide,/);

}

#endif
