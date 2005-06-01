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

//tvector.C
//Implements TinyVectors (small vectors of fixed size N and type T)


#include <iostream>
using namespace std;


namespace cat
{

   
  //default constructor
  template <class T,int N>
  tvector<T,N>::tvector()
  {
  }
      
  //copy constructor (really copies to the new vector)
  template <class T,int N>
  tvector<T,N>::tvector(const tvector& rhs)
  {
    if (this==&rhs)
      return;
    for (int i=0;i<N;++i)
      vector_data[i]=rhs[i];
  }

  //constructors from values
  //assigns 
  template <class T,int N>
  tvector<T,N>::tvector(const T & v1)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=v1;
  }
  template <class T,int N>
  tvector<T,N>::tvector(const T & v1,const T & v2)
  {
    if (N!=2)
      {
	cout << "Array is not 2D. Aborting programme ..." << endl;
	exit(1);
      }
    vector_data[0]=v1;
    vector_data[1]=v2;
  }
  template <class T,int N>
  tvector<T,N>::tvector(const T & v1,const T & v2,const T & v3)
  {
    if (N!=3)
      {
	cout << "Array is not 3D. Aborting programme ..." << endl;
	exit(1);
      }
    vector_data[0]=v1;
    vector_data[1]=v2;
    vector_data[2]=v3;  
  }
      

  //Destructor
  template <class T,int N>
  tvector<T,N>::~tvector()
  {
    //cout << "tvector destructor " << endl;  
  }

  //Accessors  
  template <class T,int N>
  T & tvector<T,N>::operator[](const int n)
  {
    return vector_data[n];
  }
  template <class T,int N>
  const T & tvector<T,N>::operator[](const int n) const
  {
    return vector_data[n];
  }
      
  template <class T,int N>
  T * tvector<T,N>::data()
  {
    return vector_data;
  }
  template <class T,int N>
  const T * tvector<T,N>::data() const 
  {
    return vector_data;
  }

  //returns the size of this tvector
  template <class T,int N>
  int tvector<T,N>::size() const 
  {
    return N;
  }
      

  //Assignement operators
  //to tvector
  template <class T,int N>
  template <class T1>
  tvector<T,N> & tvector<T,N>::operator=(const tvector<T1,N> & rhs)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=rhs[i];
    return *this;
  }
  //to scalar  
  template <class T,int N>
  template <class T1>
  tvector<T,N> & tvector<T,N>::operator=(const T1 & rhs)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=rhs;
    return *this;
  }









}

