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

#ifndef OPSTRUCTS_H
#define OPSTRUCTS_H

#include "traits/promote.h"


namespace cat
{

  // Unary operators that return same type as argument

#define CAT_UNARY_OPS(opsname,op)				       \
  template<class T>					       \
  struct opsname						       \
  {							       \
    typedef T returnT;					       \
    static inline returnT apply(const T & a)			       \
      {							       \
	return op a;					       \
      }							       \
  };							       

  CAT_UNARY_OPS(BitwiseNot,~);
  CAT_UNARY_OPS(UnaryPlus,+);
  CAT_UNARY_OPS(UnaryMinus,-);


// Unary operators that return specified type


#define CAT_UNARY_OPS_RET(opsname,op,ret)			       \
  template<class T>						       \
  struct opsname						       \
  {								       \
    typedef ret returnT;					       \
    static inline returnT apply(const T & a)				       \
    {								       \
      return op a;						       \
    }								       \
  };

  CAT_UNARY_OPS_RET(LogicalNot,!,bool)

    

  // Binary operators that return type based on type promotion
    
#define CAT_BINARY_OPS(opsname,op)					\
    template<typename T1, typename T2>					\
    struct opsname							\
    {									\
      typedef typename promote_traits<T1,T2>::T_promote returnT;	\
      static inline returnT						\
      apply(const T1 & a, const T2 & b)							\
	{									\
	return a op b;							\
      }									\
    };

    
    CAT_BINARY_OPS(Add,+);
  CAT_BINARY_OPS(Subtract,-);
  CAT_BINARY_OPS(Multiply,*);
  CAT_BINARY_OPS(Divide,/);
  CAT_BINARY_OPS(Modulo,%);
  CAT_BINARY_OPS(BitwiseXor,^);
  CAT_BINARY_OPS(BitwiseAnd,&);
  CAT_BINARY_OPS(BitwiseOr,|);
  CAT_BINARY_OPS(ShiftRight,>>);
  CAT_BINARY_OPS(ShiftLeft,<<);



// Binary operators that return specified type

#define CAT_BINARY_OPS_RET(opsname,op,ret)			     \
  template<typename T1, typename T2>				     \
  struct opsname						     \
  {								     \
    typedef ret returnT;					     \
    static inline returnT					     \
    apply(const T1 & a, const T2 & b)						     \
    {								     \
      return a op b;						     \
    }								     \
  };


  CAT_BINARY_OPS_RET(Greater,>,bool);
  CAT_BINARY_OPS_RET(Less,<,bool);
  CAT_BINARY_OPS_RET(GreaterOrEqual,>=,bool);
  CAT_BINARY_OPS_RET(LessOrEqual,<=,bool);
  CAT_BINARY_OPS_RET(Equal,==,bool);
  CAT_BINARY_OPS_RET(NotEqual,!=,bool);
  CAT_BINARY_OPS_RET(LogicalAnd,&&,bool);
  CAT_BINARY_OPS_RET(LogicalOr,||,bool);


};

#endif
