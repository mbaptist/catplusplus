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
  
#ifndef CAT_ARRAY_FUNCS_H
#define CAT_ARRAY_FUNCS_H

#include "../globals.h"

#include "array_macros.h" 
#include "array_iterator.h"

#include <cmath>
using namespace std;

#include "array_expression.h"
#include "../funcstructs.h"


  namespace cat
  {

    //Forward declaration of class array<T,D>
    template <class T,int D>
    class array;
    
    //creates a reference to array rhs
    template <class T,int D>
    array<T,D> reference(const array<T,D> & rhs);

#ifdef USE_EXPRESSIONS
  
  //FUNC(ARRAY)
#define CAT_UNARY_FUNCTION_ARRAY(opsname,op) \
  template <class T,int D>					 \
	  inline ArrayExpression<ArrayExpressionUnaryOp<opsname<T>,typename array<T,D>::const_iterator> >\
	  op(const cat::array<T,D> & rhs) \
	  {									\
	  typedef ArrayExpressionUnaryOp<opsname<T>,typename array<T,D>::const_iterator>  ExpressionT; \
	  return ArrayExpression<ExpressionT>(ExpressionT(rhs.begin())); \
	  };
	//FUNC(ARRAYEXPRESSION)
#define CAT_UNARY_FUNCTION_ARRAYEXPRESSION(opsname,op) \
	  template <class ET>                                 \
	  inline ArrayExpression<ArrayExpressionUnaryOp<opsname<typename ET::elementT>,ET > > \
	  op(const ET & rhs)               \
	  {                                                                   \
	  typedef ArrayExpressionUnaryOp<opsname<typename ET::elementT>, ET >  ExpressionT; \
	  return ArrayExpression<ExpressionT>(ExpressionT(rhs));        \
	  };
	  
#define CAT_UNARY_FUNCTION(opsname,op)  \
	  CAT_UNARY_FUNCTION_ARRAY(opsname,op) \
	  CAT_UNARY_FUNCTION_ARRAYEXPRESSION(opsname,op)

	  CAT_UNARY_FUNCTION(SIN,sin);

  CAT_UNARY_FUNCTION(SQRT,sqrt);
  
  
  CAT_UNARY_FUNCTION(REAL,real);
  CAT_UNARY_FUNCTION(IMAG,imag);
  CAT_UNARY_FUNCTION(CONJ,conj);

  CAT_UNARY_FUNCTION(NORM,norm);
  CAT_UNARY_FUNCTION(NORM_SQ,norm_sq);

  
//ARRAY OP ARRAY
#define CAT_BINARY_FUNCTION_ARRAY_ARRAY(funcsname,func)					\
  template <class T1,int D1,class T2,int D2>					\
	  inline ArrayExpression<ArrayExpressionBinOp<funcsname<T1,T2>,typename array<T1,D1>::const_iterator,typename array<T2,D2>::const_iterator> > \
	  func(const cat::array<T1,D1> & lhs,const cat::array<T2,D2> & rhs) \
	  {									\
	  typedef ArrayExpressionBinOp<funcsname<T1,T2>,typename array<T1,D1>::const_iterator,typename array<T2,D2>::const_iterator>  ExpressionT; \
	  return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs.begin())); \
	  };
	//ARRAY OP ARRAYEXPRESSION
#define CAT_BINARY_FUNCTION_ARRAY_ARRAYEXPRESSION(funcsname,func) \
	  template <class T1,int D1,class ET>                                 \
	  inline ArrayExpression<ArrayExpressionBinOp<funcsname<T1,typename ET::elementT>,typename array<T1,D1>::const_iterator,ET > > \
	  func(const cat::array<T1,D1> & lhs,const ET & rhs)               \
	  {                                                                   \
	  typedef ArrayExpressionBinOp<funcsname<T1,typename ET::elementT>,typename array<T1,D1>::const_iterator, ET >  ExpressionT; \
	  return ArrayExpression<ExpressionT>(ExpressionT(lhs.begin(),rhs));        \
	  };
	//ARRAYEXPRESSION OP ARRAY
#define CAT_BINARY_FUNCTION_ARRAYEXPRESSION_ARRAY(funcsname,func) \
	  template <class ET,class T2,int D2>					\
	  inline ArrayExpression<ArrayExpressionBinOp<funcsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator> > \
	  func(const ET & lhs,const cat::array<T2,D2> & rhs)		\
	  {									\
	  typedef ArrayExpressionBinOp<funcsname<typename ET::elementT,T2>,ET,typename array<T2,D2>::const_iterator>  ExpressionT; \
	  return ArrayExpression<ExpressionT>(ExpressionT(lhs,rhs.begin()));	\
	  };

#define CAT_BINARY_FUNCTION(funcsname,func) \
	  CAT_BINARY_FUNCTION_ARRAY_ARRAY(funcsname,func) \
	  CAT_BINARY_FUNCTION_ARRAY_ARRAYEXPRESSION(funcsname,func) \
	  CAT_BINARY_FUNCTION_ARRAYEXPRESSION_ARRAY(funcsname,func) 
	  

	  CAT_BINARY_FUNCTION(POW,pow);
  CAT_BINARY_FUNCTION(CROSS_PRODUCT,cross_product);
  CAT_BINARY_FUNCTION(DOT_PRODUCT,dot_product);



//Reductions
  
//max
  template <class T,int D>
	  T max(const array<T,D> & a)
  {
	  typename array<T,D>::const_iterator array_iterator(a);
	  array_iterator=a.begin();
	  
	  T out(*array_iterator);
	  out=0;
	  for (array_iterator=a.begin();
	       array_iterator!=a.end();
	       ++array_iterator)
		  
		  if(*array_iterator>out)
			  out=*array_iterator;
	  return out;
  }
//   template <class T>
// 	  ArrayExpression<T>::elementT max(const ArrayExpression<T> & a)
//   {
// 	  typename array<T,D>::const_iterator array_iterator(a);
// 	  array_iterator=a.begin();
// 	  
// 	  T out(*array_iterator);
// 	  out=0;
// 	  for (array_iterator=a.begin();
// 	       array_iterator!=a.end();
// 	       ++array_iterator)
// 		  
// 		  if(*array_iterator>out)
// 			  out=*array_iterator;
// 	  return out;
//   }
	//min
  template <class T,int D>
	  T min(const array<T,D> & a)
  {
	  typename array<T,D>::const_iterator array_iterator(a);
	  array_iterator=a.begin();
	  T out(*array_iterator);
	  out=0;
	  for (array_iterator=a.begin();
	       array_iterator!=a.end();
	       ++array_iterator)
		  if(*array_iterator<out)
			  out=*array_iterator;
	  return out;
  }
  
//sum
  template <class T,int D>
	  T sum(const array<T,D> & a)
  {
	  T out;
	  out=0;
	  typename array<T,D>::const_iterator a_iterator(a);
	  for (a_iterator=a.begin();
	       a_iterator!=a.end();
	       ++a_iterator)
		  out+=(*a_iterator);
	  return out;
  }

  template <class T>
	  typename T::elementT sum(T a)
  {
	  typename T::elementT out;
	  out=0;
	  for (int i=0;i<a.size();++i)
	  {
		  out+=(*a);
		  ++a;
	  }
	  return out;
  }

#endif
  
#ifdef USE_TEMPORARIES
    //Operations on tvector - extending for arrays of tvectors

  CAT_DECLARE_FUNCTION_REAL_NUMERIC(real);
  CAT_DECLARE_FUNCTION_REAL_NUMERIC(imag);
  CAT_DECLARE_FUNCTION_NUMERIC(conj);
  
  CAT_DECLARE_FUNCTION2_NUMERIC(dot_product);  
  CAT_DECLARE_FUNCTION2_ELEMENT_NUMERIC(dot_product);
  
  CAT_DECLARE_FUNCTION_REAL_NUMERIC(norm_sq);
  
  CAT_DECLARE_FUNCTION_REAL_NUMERIC(norm);

  CAT_DECLARE_FUNCTION2_PROMOTE(cross_product);
  CAT_DECLARE_FUNCTION2_ELEMENT(cross_product);

//Extending Math Functions
  
  CAT_DECLARE_FUNCTION(sqrt);
  CAT_DECLARE_FUNCTION2_ELEMENT(pow);

  
//Reductions
 
//max
  template <class T,int D>
	  T max(const array<T,D> & a);
  
//min
  template <class T,int D>
	  T min(const array<T,D> & a);
  
//sum
  template <class T,int D>
	  T sum(const array<T,D> & a);

#endif
  
  }



#include "array_funcs.C"


#endif
