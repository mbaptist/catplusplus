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

#include "array.h"

#include "array_macros.h" 
#include "array_iterator.h"

  namespace cat
  {
    
    //creates a reference to array rhs
    template <class T,int D>
    array<T,D> reference(const array<T,D> & rhs)
    {
      array<T,D> out;
      out.reference(rhs);
      return(out);
    }


    //Reductions
    
    ////LOOPS MUST BE REPLACED BY ITERATORS
    
    
    //max
    template <class T,int D>
    T max(const array<T,D> & a)
    {
      array_iterator<T,D> array_iterator(a);
      array_iterator=a.begin();
      T out(*array_iterator);
      for (array_iterator=a.begin();
	   array_iterator!=a.end();
	   ++array_iterator)      
	if(*array_iterator>out)
	  out=*array_iterator;
      return out;
    }
    
    //sum
    template <class T,int D>
    T sum(const array<T,D> & a)
    {
      T out=0;
      array_iterator<T,D> array_iterator(a);
      for (array_iterator=a.begin();
	   array_iterator!=a.end();
	   ++array_iterator)
	out+=*array_iterator;
      return out;
    }



  }

