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


#ifndef CAT_PROMOTE_H
#define CAT_PROMOTE_H

#define CAT_ENUM_CAST(X)   (int)X
//#define CAT_ENUM_CAST(X)   X


#include <complex>
using namespace std;


namespace cat
{


template<class T>
struct precision_traits 
{
  enum
    { 
      precisionRank = 0,
      knowPrecisionRank = 0 
    };
};

#define CAT_DECLARE_PRECISION(T,rank)          \
    template<>                                \
    struct precision_traits< T > {             \
        enum { precisionRank = rank,          \
           knowPrecisionRank = 1 };           \
    };

CAT_DECLARE_PRECISION(int,100)
CAT_DECLARE_PRECISION(unsigned int,200)
CAT_DECLARE_PRECISION(long,300)
CAT_DECLARE_PRECISION(unsigned long,400)
CAT_DECLARE_PRECISION(float,500)
CAT_DECLARE_PRECISION(double,600)
CAT_DECLARE_PRECISION(long double,700)
CAT_DECLARE_PRECISION(complex<float>,800)
CAT_DECLARE_PRECISION(complex<double>,900)
CAT_DECLARE_PRECISION(complex<long double>,1000)




template<class T>
struct autopromote_trait 
{
  typedef T T_numtype;
};

#define CAT_DECLARE_AUTOPROMOTE(T1,T2)     \
    template<>                            \
    struct autopromote_trait<T1> {        \
      typedef T2 T_numtype;               \
    };

// These are the odd cases where small integer types
// are automatically promoted to int or unsigned int for
// arithmetic.
CAT_DECLARE_AUTOPROMOTE(bool, int)
CAT_DECLARE_AUTOPROMOTE(char, int)
CAT_DECLARE_AUTOPROMOTE(unsigned char, int)
CAT_DECLARE_AUTOPROMOTE(short int, int)
CAT_DECLARE_AUTOPROMOTE(short unsigned int, unsigned int)

template<class T1, class T2, int promoteToT1>
struct promote2 
{
  typedef T1 T_promote;
};

template<class T1, class T2>
struct promote2<T1,T2,0>
{
  typedef T2 T_promote;
};


template<class T1_orig, class T2_orig>
struct promote_traits {
    // Handle promotion of small integers to int/unsigned int
    typedef typename autopromote_trait<T1_orig>::T_numtype T1;
    typedef typename autopromote_trait<T2_orig>::T_numtype T2;

    // True if T1 is higher ranked
    enum {
      T1IsBetter =
        CAT_ENUM_CAST(precision_traits<T1>::precisionRank) >
          CAT_ENUM_CAST(precision_traits<T2>::precisionRank),

    // True if we know ranks for both T1 and T2
      knowBothRanks =
        CAT_ENUM_CAST(precision_traits<T1>::knowPrecisionRank)
      && CAT_ENUM_CAST(precision_traits<T2>::knowPrecisionRank),

    // True if we know T1 but not T2
      knowT1butNotT2 =  CAT_ENUM_CAST(precision_traits<T1>::knowPrecisionRank)
        && !(CAT_ENUM_CAST(precision_traits<T2>::knowPrecisionRank)),

    // True if we know T2 but not T1
      knowT2butNotT1 =  CAT_ENUM_CAST(precision_traits<T2>::knowPrecisionRank)
        && !(CAT_ENUM_CAST(precision_traits<T1>::knowPrecisionRank)),

    // True if T1 is bigger than T2
      T1IsLarger = sizeof(T1) >= sizeof(T2),

    // We know T1 but not T2: true
    // We know T2 but not T1: false
    // Otherwise, if T1 is bigger than T2: true
      defaultPromotion = knowT1butNotT2 ? 0 : 
         (knowT2butNotT1 ? 1 : T1IsLarger)
    };

    // If we have both ranks, then use them.
    // If we have only one rank, then use the unknown type.
    // If we have neither rank, then promote to the larger type.

    enum {
      promoteToT1 = (CAT_ENUM_CAST(knowBothRanks) ? CAT_ENUM_CAST(T1IsBetter)
        : CAT_ENUM_CAST(defaultPromotion)) ? 1 : 0
    };

    typedef typename promote2<T1,T2,promoteToT1>::T_promote T_promote;
};


}


#endif
