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


//Forward declaration of class cat_tvector<T,N>
template <class T,int N>
class cat_tvector;

//Forward declaration of class cat_array<T,D>
template <class T,int D>
class cat_array;

//Complex number support
#include <complex>
using namespace std; 



//Numeric Traits

template <class T>
struct cat_numeric_traits
{
	typedef T T_numeric; 	
};

template <class T, int N>
struct cat_numeric_traits<cat_tvector<T,N> >
{
	typedef typename cat_numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int D>
struct cat_numeric_traits<cat_array<T,D> >
{
	typedef typename cat_numeric_traits<T>::T_numeric T_numeric; 	
};





//Real Numeric Traits

template <class T>
struct cat_real_numeric_traits
{
	typedef T T_numeric; 
};

template <class T>
struct cat_real_numeric_traits<complex<T> >
{
	typedef typename cat_real_numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int N>
struct cat_real_numeric_traits<cat_tvector<T,N> >
{
	typedef typename cat_real_numeric_traits<T>::T_numeric T_numeric; 	
};

template <class T, int D>
struct cat_real_numeric_traits<cat_array<T,D> >
{
	typedef typename cat_real_numeric_traits<T>::T_numeric T_numeric; 	
};


#endif













