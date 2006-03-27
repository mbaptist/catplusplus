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


#include "tvector.h"

#include "../traits/traits.h"

#include<complex>
#include<iostream>
#include<cmath>
  using namespace std;

namespace cat
{

  //IO
  //overloading <<
  template <class T,int N>
  std::ostream & operator<<(std::ostream & output,
			   const tvector<T,N> & ovector)
  {
    for(int i=0;i<N-1;++i)
      output << ovector[i] << " "; 
    output << ovector[N-1];
    return output;
  }
  template <class T,int N>
  std::ostream & operator<<(std::ostream & output,
			   tvector<T,N> & ovector)
  {
    for(int i=0;i<N-1;++i)
      output << ovector[i] << " "; 
    output << ovector[N-1];
    return output;
  }
  //overloading >>
  template <class T,int N>
  std::istream & operator>>(std::istream & input,
			   tvector<T,N> & ivector)
  {
    for(int i=0;i<N;++i)
      input >> ivector[i];
    return input;
  }


  //Operations on tvectors of complex
  //real part
  template <class T,int N>
  tvector<T,N> real(const tvector<complex<T>,N> & a)
  {
    tvector<T,N> aux;
    for(int i=0;i<N;++i)
      aux[i]=a[i].real();
    return tvector<T,N>(aux);
  }
  //imaginary part
  template <class T,int N>
  tvector<T,N> imag(const tvector<complex<T>,N> & a)
  {
    tvector<T,N> aux;
    for(int i=0;i<N;++i)
      aux[i]=a[i].imag();
    return tvector<T,N>(aux);
  }
  //conjugate
  template <class T,int N>
  tvector<complex<T>,N> conj(const tvector<complex<T>,N> & a)
  {
    tvector<complex<T>,N> aux;
    for(int i=0;i<N;++i)
	aux[i]=conj(a[i]);
    return tvector<complex<T>,N>(aux);
  }



  //Dot product
  template <class T1,class T2,int N>
  typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::
  T_numeric dot_product(const tvector<T1,N> & a,const tvector<T2,N> & b)
  {
    typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::
      T_numeric out;
    out=0;
    for(int i=0;i<N;++i)
      out+=a[i]*b[i];
    return out;
  }


  //Square of Norm
  template <class T,int N>
  typename real_numeric_traits<T>::T_numeric norm_sq(const tvector<T,N> & a)
  {
    return typename real_numeric_traits<T>::T_numeric(dot_product(a,a));
  }
  
  //Square of Norm for complex numbers
  template <class T,int N>
  typename real_numeric_traits<complex<T> >::T_numeric 
  norm_sq(const tvector<complex<T>,N> & a)
  {
    return typename real_numeric_traits<complex<T> >::
      T_numeric((dot_product(a,conj(a))).real());
  }
  

  //Norm
  template <class T,int N>
  typename real_numeric_traits<T>::T_numeric norm(const tvector<T,N> & a)
  {
    return typename real_numeric_traits<T>::T_numeric(std::sqrt(norm_sq(a)));
  }


  //Cross product
  template <class T1, class T2>
  tvector<typename promote_traits<T1,T2>::T_promote,3> 
  cross_product(const tvector<T1,3> & a,const tvector<T2,3> & b)
  {
    return tvector<typename promote_traits<T1,T2>::T_promote,3>
	(
	 a[1]*b[2]-a[2]*b[1],
	 a[2]*b[0]-a[0]*b[2],
	 a[0]*b[1]-a[1]*b[0]
	 );
  }

  
}



