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

#define USE_EXPRESSIONS
//#define USE_TEMPORARIES

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


//Binary Operators

#ifdef USE_EXPRESSIONS

#define CAT_BINARY_OPERATOR(opsname,op)					\
  template <class T1,int D1,class T2,int D2>					\
  inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,T2>,typename array<T1,D1>::const_iterator,typename array<T2,D2>::const_iterator> > \
  operator op(const cat::array<T1,D1> & lhs,const cat::array<T2,D2> & rhs) \
  {									\
    typedef ArrayExpressionBinOp<opsname<T1,T2>,typename array<T1,D1>::const_iterator,typename array<T2,D2>::const_iterator>  ExpressionT; \
    return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs.begin())); \
	}; 	\
	template <class ET,class T2,int D2>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator> > \
	 	operator op(const ET & lhs,const cat::array<T2,D2> & rhs)		\
	 {									\
	 	typedef ArrayExpressionBinOp<opsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator>  ExpressionT; \
	 		return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs.begin()));	\
	 }; \
	template <class ET1,class ET2>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<typename ET1::elementT,typename ET1::elementT>,ET1,ET2> > \
	operator op(const ET1 & lhs,const ET2 & rhs)		\
	{									\
	typedef ArrayExpressionBinOp<opsname<typename ET1::elementT,typename ET1::elementT>,ET1,ET2>  ExpressionT; \
	return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs));	\
	};


/*\
	template <class T1,int D1,class ET>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,typename ET::elementT>,typename array<T1,D1>::const_iterator,ET > > \
	operator op(const cat::array<T1,D1> & lhs,const ET & rhs)		\
{									\
		typedef ArrayExpressionBinOp<opsname<T1,typename ET::elementT>,typename array<T1,D1>::const_iterator, ET >  ExpressionT; \
		return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs));	\
}; \*/
// 	\
// 	template <class ET,class T2,int D2>					\
// 	inline ArrayExpression<ArrayExpressionBinOp<opsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator> > \
// 	operator op(const ET & lhs,const cat::array<T2,D2> & rhs)		\
// {									\
// 	typedef ArrayExpressionBinOp<opsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator>  ExpressionT; \
// 		return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs.begin()));	\
// };

CAT_BINARY_OPERATOR(Add,+);
CAT_BINARY_OPERATOR(Subtract,-);
CAT_BINARY_OPERATOR(Multiply,*);
CAT_BINARY_OPERATOR(Divide,/);


#define CAT_BINARY_OPERATOR_CONSTANT(opsname,op,CT)					\
template <class T1,int D1>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,typename ArrayExpressionConstant<CT>::elementT>,typename array<T1,D1>::const_iterator,ArrayExpressionConstant<CT> > > \
	operator op(const cat::array<T1,D1> & lhs,const CT & rhs)		\
	{									\
	typedef ArrayExpressionBinOp<opsname<T1,typename ArrayExpressionConstant<CT>::elementT>,typename array<T1,D1>::const_iterator, ArrayExpressionConstant<CT> >  ExpressionT; \
	return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs));	\
	}; \
	template <class T2,int D2>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<typename ArrayExpressionConstant<CT>::elementT,T2>,ArrayExpressionConstant<CT>,typename array<T2,D2>::const_iterator> > \
	operator op(const CT & lhs,const cat::array<T2,D2> & rhs)		\
	{									\
	typedef ArrayExpressionBinOp<opsname<typename ArrayExpressionConstant<CT>::elementT,T2>,ArrayExpressionConstant<CT>,typename array<T2,D2>::const_iterator>  ExpressionT; \
	return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs.begin()));	\
	};

#define CAT_BINARY_OPERATOR_CONSTANT_ALL(opsname,op) \
	CAT_BINARY_OPERATOR_CONSTANT(opsname,op,int) \
	CAT_BINARY_OPERATOR_CONSTANT(opsname,op,float) \
	CAT_BINARY_OPERATOR_CONSTANT(opsname,op,double) \
	CAT_BINARY_OPERATOR_CONSTANT(opsname,op,long double)

CAT_BINARY_OPERATOR_CONSTANT_ALL(Add,+);
CAT_BINARY_OPERATOR_CONSTANT_ALL(Subtract,-);
CAT_BINARY_OPERATOR_CONSTANT_ALL(Multiply,*);
CAT_BINARY_OPERATOR_CONSTANT_ALL(Divide,/);


#define CAT_BINARY_OPERATOR_CONSTANT_COMPLEX(opsname,op)					\
template <class T1,int D1,class T>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<T1,typename ArrayExpressionConstant<std::complex<T> >::elementT>,typename array<T1,D1>::const_iterator,ArrayExpressionConstant<std::complex<T> > > > \
	operator op(const cat::array<T1,D1> & lhs,const std::complex<T> & rhs)		\
	{									\
	typedef ArrayExpressionBinOp<opsname<T1,typename ArrayExpressionConstant<std::complex<T> >::elementT>,typename array<T1,D1>::const_iterator, ArrayExpressionConstant<std::complex<T> > >  ExpressionT; \
	return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs));	\
	}; \
	template <class T2,int D2,class T>					\
	inline ArrayExpression<ArrayExpressionBinOp<opsname<typename ArrayExpressionConstant<std::complex<T> >::elementT,T2>,ArrayExpressionConstant<std::complex<T> >,typename array<T2,D2>::const_iterator> > \
	operator op(const std::complex<T> & lhs,const cat::array<T2,D2> & rhs)		\
	{									\
	typedef ArrayExpressionBinOp<opsname<typename ArrayExpressionConstant<std::complex<T> >::elementT,T2>,ArrayExpressionConstant<std::complex<T> >,typename array<T2,D2>::const_iterator>  ExpressionT; \
	return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs.begin()));	\
	};
	
	CAT_BINARY_OPERATOR_CONSTANT_COMPLEX(Add,+);
CAT_BINARY_OPERATOR_CONSTANT_COMPLEX(Subtract,-);
CAT_BINARY_OPERATOR_CONSTANT_COMPLEX(Multiply,*);
CAT_BINARY_OPERATOR_CONSTANT_COMPLEX(Divide,/);

#endif

#ifdef USE_TEMPORARIES

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

CAT_BINARY_OPERATOR(+);
CAT_BINARY_OPERATOR(-);
CAT_BINARY_OPERATOR(*);
CAT_BINARY_OPERATOR(/);

#endif

}

#endif
