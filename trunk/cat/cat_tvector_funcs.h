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


#ifndef CAT_TVECTOR_FUNCS_H
#define CAT_TVECTOR_FUNCS_H

#include "cat_tvector.h"

#include "cat_numeric.h"
#include "cat_promote.h"

#include<complex>
#include<iostream>
#include<cmath>
using namespace std;


//Operations on cat_tvectors of complex
//real part
template <class T,int N>
cat_tvector<T,N> real(const cat_tvector<complex<T>,N> & a)
{
  cat_tvector<T,N> aux;
  for(int i=0;i<N;++i)
    aux[i]=a[i].real();
  return cat_tvector<T,N>(aux);
}
//imaginary part
template <class T,int N>
cat_tvector<T,N> imag(const cat_tvector<complex<T>,N> & a)
{
  cat_tvector<T,N> aux;
  for(int i=0;i<N;++i)
    aux[i]=a[i].imag();
  return cat_tvector<T,N>(aux);
}
//conjugate
template <class T,int N>
cat_tvector<complex<T>,N> conj(const cat_tvector<complex<T>,N> & a)
{
  cat_tvector<complex<T>,N> aux;
  for(int i=0;i<N;++i)
    aux[i]=conj(a[i]);
  return cat_tvector<complex<T>,N>(aux);
}



//Dot product
template <class T1,class T2,int N>
typename cat_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric dot_product(const cat_tvector<T1,N> & a,const cat_tvector<T2,N> & b)
{
  typename cat_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric out;
  out=0;
  for(int i=0;i<N;++i)
    out+=a[i]*b[i];
  return out;
}


//Square of Norm
template <class T,int N>
typename cat_real_numeric_traits<T>::T_numeric norm_sq(const cat_tvector<T,N> & a)
{
  return typename cat_real_numeric_traits<T>::T_numeric(dot_product(a,a));
}

//Square of Norm for complex numbers
template <class T,int N>
typename cat_real_numeric_traits<complex<T> >::T_numeric norm_sq(const cat_tvector<complex<T>,N> & a)
{
  return typename cat_real_numeric_traits<complex<T> >::T_numeric((dot_product(a,conj(a))).real());
}



//Norm
template <class T,int N>
typename cat_real_numeric_traits<T>::T_numeric norm(const cat_tvector<T,N> & a)
{
  return typename cat_real_numeric_traits<T>::T_numeric(sqrt(norm_sq(a)));
}




//Cross product
template <class T1, class T2>
cat_tvector<typename cat_promote_traits<T1,T2>::T_promote,3> cross_product(const cat_tvector<T1,3> & a,const cat_tvector<T2,3> & b)
{
  return cat_tvector<typename cat_promote_traits<T1,T2>::T_promote,3>
    (
     a[1]*b[2]-a[2]*b[1],
     a[2]*b[0]-a[0]*b[2],
     a[0]*b[1]-a[1]*b[0]
     );
}





#if 0

//Cross product
//real or complex cat_tvectors
template <class T>
cat_tvector<T,3> cross_product(const cat_tvector<T,3> & a,const cat_tvector<T,3> & b)
{
  return cat_tvector<T,3>
    (
     a[1]*b[2]-a[2]*b[1],
     a[2]*b[0]-a[0]*b[2],
     a[0]*b[1]-a[1]*b[0]
     );
}



//real,complex cat_tvectors
template <class T>
cat_tvector<complex<T>,3> cross_product(const cat_tvector<T,3> & a,const cat_tvector<complex<T>,3> & b)
{
  return cat_tvector<complex<T>,3>
    (
     complex<T>(a[1]*b[2].real()-a[2]*b[1].real(),
		a[1]*b[2].imag()-a[2]*b[1].imag()),
     complex<T>(a[2]*b[0].real()-a[0]*b[2].real(),
		a[2]*b[0].imag()-a[0]*b[2].imag()),
     complex<T>(a[0]*b[1].real()-a[1]*b[0].real(),
		a[0]*b[1].imag()-a[1]*b[0].imag())
     );
}
//complex,real cat_tvectors
template <class T>
cat_tvector<complex<T>,3> cross_product(const cat_tvector<complex<T>,3> & a,const cat_tvector<T,3> & b)
{
  return -cross_product(b,a);
}
#endif

#endif
