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

//tvector.h
//Implements TinyVectors (small vectors of fixed size N and type T)

#ifndef TVECTOR_H
#define TVECTOR_H

#include <iostream>
using namespace std;



namespace cat
{

  template <class T,int N>
  class tvector
  {

  private:
    //Automatic array of size N containing data
    T vector_data[N];
    
  public:

    typedef T T_element;

    //Constructors
    
    //default constructor
    tvector();
      
    //copy constructor (really copies to the new vector)
    tvector<T,N>(const tvector<T,N> & rhs);

    template <class T1>
    tvector<T,N>(const tvector<T1,N> & rhs);

    //constructors from values
    //assigns 
    explicit tvector(const T & v1);
    explicit tvector(const T & v1,const T & v2);
    explicit tvector(const T & v1,const T & v2,const T & v3);
    explicit tvector(const T & v1,const T & v2,const T & v3,const T & v4);
    explicit tvector(const T & v1,const T & v2,const T & v3,const T & v4,const T & v5);
    explicit tvector(const T & v1,const T & v2,const T & v3,const T & v4,const T & v5,const T & v6);
    explicit tvector(const T & v1,const T & v2,const T & v3,const T & v4,const T & v5,const T & v6,const T & v7);
    
    //Destructor
    ~tvector();

    //Accessors  
    T & operator[](const int n);
    const T & operator[](const int n) const;
      
    T * data();
    const T * data() const;

    //returns the size of this tvector
    int size() const;
      
 
    //Assignement operators
    //to tvector
    tvector & operator=(const tvector<T,N> & rhs);
    template <class T1>
    tvector & operator=(const tvector<T1,N> & rhs);
    //to element
    tvector & operator=(const T & rhs);
    template <class T1>
    tvector & operator=(const T1 & rhs);

    //// One direction promotion needed for the sake of safety


#define TVECTOR_UPDATE(op) \
template <class T1> \
inline tvector & \
operator op(const tvector<T1,N> & rhs) \
{ \
   for(int i=0;i<N;++i) \
      (*this)[i] op rhs[i]; \
   return *this; \
} \
template <class T1> \
inline tvector & \
operator op(const T1 & rhs) \
{ \
   for(int i=0;i<N;++i) \
      (*this)[i] op rhs; \
   return *this; \
}

TVECTOR_UPDATE(+=)
TVECTOR_UPDATE(-=)
TVECTOR_UPDATE(*=)
TVECTOR_UPDATE(/=)

  };

}



#include "tvector.C"


#endif
