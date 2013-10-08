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

#ifndef FUNCSTRUCTS_H
#define FUNCSTRUCTS_H

#include "traits/promote.h"


namespace cat
{

#define CAT_UNARY_FUNCS(funcsname,func) \
template<class T>					       \
	struct funcsname						       \
{							       \
		typedef T returnT;					       \
		static inline returnT apply(const T & a)			       \
	{							       \
	return  func(a);					       \
	}							       \
};							       

	CAT_UNARY_FUNCS(SIN,sin);

CAT_UNARY_FUNCS(SQRT,sqrt);

CAT_UNARY_FUNCS(CONJ,conj);

#define CAT_UNARY_FUNCS_RET(funcsname,func,ret) \
template<class T>					       \
	struct funcsname						       \
	{							       \
	typedef ret returnT;					       \
	static inline returnT apply(const T & a)			       \
	{							       \
	return  func(a);					       \
	}							       \
	};							       

  CAT_UNARY_FUNCS_RET(REAL,real,double);
  CAT_UNARY_FUNCS_RET(IMAG,imag,double);

CAT_UNARY_FUNCS_RET(NORM,norm,double);
CAT_UNARY_FUNCS_RET(NORM_SQ,norm_sq,double);

#define CAT_BINARY_FUNCS(funcsname,func)					\
template<typename T1, typename T2>					\
	struct funcsname							\
	{									\
	typedef typename promote_traits<T1,T2>::T_promote returnT;	\
	static inline returnT						\
	apply(const T1 & a, const T2 & b)							\
	{									\
	return returnT(func(a,b));							\
	}									\
	};

	
	CAT_BINARY_FUNCS(POW,pow)
	                  
	CAT_BINARY_FUNCS(CROSS_PRODUCT,cross_product)
	
#define CAT_BINARY_FUNCS_RET(funcsname,func,ret)			     \
	template<typename T1, typename T2>				     \
	struct funcsname						     \
	{								     \
	typedef ret returnT;					     \
	static inline returnT					     \
	apply(const T1 & a, const T2 & b)						     \
	{								     \
	return func(a,b);						     \
	}								     \
	};


#define CAT_BINARY_FUNCS_ELEMENT(funcsname,func)					\
	template<typename T1, typename T2>					\
	struct funcsname							\
	{									\
	typedef typename promote_traits<typename T1::T_element,typename T2::T_element>::T_promote returnT;	\
	static inline returnT						\
	apply(const T1 & a, const T2 & b)							\
	{									\
	return func(a,b);							\
	}									\
	};
	
CAT_BINARY_FUNCS_ELEMENT(DOT_PRODUCT,dot_product);


}

#endif
