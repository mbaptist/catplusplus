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


#ifndef CAT_TVECTOR_OPS_H
#define CAT_TVECTOR_OPS_H

#include "tvector.h"
#include "../traits/traits.h"

namespace cat
{

#define CAT_TVECTOR_BINARY_OPERATOR(op)					\
  template <class T1,class T2,int N>					\
  inline cat::tvector<typename promote_traits<T1,T2>::T_promote,N>	\
  operator op(const cat::tvector<T1,N> & lhs,const cat::tvector<T2,N> & rhs)	\
  {									\
    return cat::tvector<typename promote_traits<T1,T2>::T_promote,N>(lhs) op##= rhs; \
  }									\
    template <class T1,class T2,int N>					\
    inline cat::tvector<typename promote_traits<T1,T2>::T_promote,N>		\
    operator op(const cat::tvector<T1,N> & lhs,				\
		const typename cat::tvector<T2,N>::T_element & rhs)		\
    {									\
      return cat::tvector<typename promote_traits<T1,T2>::T_promote,N>(lhs) op##= rhs; \
    }									\
    template <class T1,class T2,int N>					\
    inline cat::tvector<typename promote_traits<T1,T2>::T_promote,N>		\
    operator op(const typename cat::tvector<T1,N>::T_element & lhs,		\
		const cat::tvector<T2,N> & rhs)				\
    {									\
      tvector<typename promote_traits<T1,T2>::T_promote,N> out;		\
      for (int i=0;i<N;++i)						\
	out[i]= lhs op rhs[i];						\
      return out;							\
    }										


  CAT_TVECTOR_BINARY_OPERATOR(+);
  CAT_TVECTOR_BINARY_OPERATOR(-);
  CAT_TVECTOR_BINARY_OPERATOR(*);
  CAT_TVECTOR_BINARY_OPERATOR(/);

  
  template <class T1,class T2,int N>
  bool operator==(const tvector<T1,N> & lhs,const tvector<T2,N> & rhs)
  {
    bool out=1;
    for (int i=0;i<N;++i)
      out*=(lhs[i]==rhs[i]);
    return out;
  };

  template <class T1,class T2,int N>
  bool operator!=(const tvector<T1,N> & lhs,const tvector<T2,N> & rhs)
  {
    return !(lhs==rhs);
  };


}

#endif
