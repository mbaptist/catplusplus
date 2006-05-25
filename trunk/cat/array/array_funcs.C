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


}

