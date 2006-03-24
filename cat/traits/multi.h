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

#ifndef CAT_MULTI_H
#define CAT_MULTI_H

//Complex number support
#include <complex>
using namespace std; 

namespace cat
{

//Forward declaration of class tvector<T,N>
template <class T,int N>
class tvector;

//Forward declaration of class array<T,D>
template <class T,int D>
class array;


//MULTI COMPONENT TRAITS

// By default, produce a harmless component type, and zero components.
template<class T_component>
struct multicomponent_traits 
{
  typedef T_component T_element;
  enum { numComponents = 0 };
};

// TinyVector
template <class T_numtype, int N_rank>
struct multicomponent_traits<tvector<T_numtype,N_rank> > 
{
  typedef T_numtype T_element;
  enum { numComponents = N_rank };
};


// complex<T>
template<class T>
struct multicomponent_traits<complex<T> >
{
  typedef T T_element;
  enum { numComponents = 2 };
};


}

#endif
