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

#ifndef CAT_NUMERIC_H
#define CAT_NUMERIC_H
 
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


//Numeric Traits

template <class T>
struct numeric_traits
{
	typedef T T_numeric; 	
};

template <class T, int N>
struct numeric_traits<tvector<T,N> >
{
	typedef typename numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int D>
struct numeric_traits<array<T,D> >
{
	typedef typename numeric_traits<T>::T_numeric T_numeric; 	
};





//Real Numeric Traits

template <class T>
struct real_numeric_traits
{
	typedef T T_numeric; 
};

template <class T>
struct real_numeric_traits<complex<T> >
{
	typedef typename real_numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int N>
struct real_numeric_traits<tvector<T,N> >
{
	typedef typename real_numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int D>
struct real_numeric_traits<array<T,D> >
{
	typedef typename real_numeric_traits<T>::T_numeric T_numeric; 	
};



}

#endif













