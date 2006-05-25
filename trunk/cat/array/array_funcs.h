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
  
  
#include "array_macros.h" 
#include "array_iterator.h"

#include <cmath>
using namespace std;


  namespace cat
  {

    //Forward declaration of class array<T,D>
    template <class T,int D>
    class array;
    
    //creates a reference to array rhs
    template <class T,int D>
    array<T,D> reference(const array<T,D> & rhs);

  
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

  }

#include "array_funcs.C"


#endif
