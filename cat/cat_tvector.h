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

//cat_tvector.h
//Implements TinyVectors (small vectors of fixed size N and type T)

#ifndef CAT_TVECTOR_H
#define CAT_TVECTOR_H

#include <iostream>
using namespace std;

template <class T,int N>
class cat_tvector
{

private:
  //Automatic array of size N containing data
  T vector_data[N];

public:
  //Constructors
  
  //default constructor
  cat_tvector(){};

  //copy constructor (really copies to the new vector)
  cat_tvector(const cat_tvector& rhs)
  {
    if (this==&rhs)
      return;
    for (int i=0;i<N;++i)
      vector_data[i]=rhs[i];
  };

  //constructors from values
  //assigns 
  explicit cat_tvector(const T & v1)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=v1;
  }
  explicit cat_tvector(const T & v1,const T & v2)
  {
    if (N!=2)
      {
	cout << "Array is not 2D. Aborting programme ..." << endl;
	exit(1);
      }
    vector_data[0]=v1;
    vector_data[1]=v2;
  }
  explicit cat_tvector(const T & v1,const T & v2,const T & v3)
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
  ~cat_tvector(){
	//cout << "cat_tvector destructor " << endl;  
	};

  //Accessors  
  T & operator[](const int n) {return vector_data[n];};
  const T & operator[](const int n) const {return vector_data[n];};

  T * data(){return vector_data;};
  const T * data() const {return vector_data;};

  //returns the size of this cat_vector
  int get_size() const {return N;};
  
  //IO
  //redefiniton of cout
  friend std::ostream& operator<<(std::ostream& output,const cat_tvector& ovector)
  {
    for(int i=0;i<N-1;++i)
      output << ovector[i] << " "; 
    output << ovector[N-1];
    return output;
  };
  friend std::ostream& operator<<(std::ostream& output,cat_tvector& ovector)
  {
    for(int i=0;i<N-1;++i)
      output << ovector[i] << " "; 
    output << ovector[N-1];
    return output;
  };
  //redefiniton of cin
  friend std::istream& operator>>(std::istream& input,cat_tvector& ivector)
  {
    for(int i=0;i<N;++i)
      input >> ivector[i];
    return input;
  }; 
 

  //Assignement operators
  //to cat_tvector
  template <class T1>
  cat_tvector& operator=(const cat_tvector<T1,N> & rhs)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=rhs[i];
    return *this;
  }
  //to scalar
  template <class T1>
  cat_tvector& operator=(const T1 & rhs)
  {
    for (int i=0;i<N;++i)
      vector_data[i]=rhs;
    return *this;
  };


#define CAT_TVECTOR_UPDATE(op) \
template <class T1> \
inline cat_tvector & \
operator op(const cat_tvector<T1,N> & rhs) \
{ \
   for(int i=0;i<N;++i) \
      (*this)[i] op rhs[i]; \
   return *this; \
} \
inline cat_tvector & \
operator op(const T& rhs) \
{ \
   for(int i=0;i<N;++i) \
      (*this)[i] op rhs; \
   return *this; \
}


CAT_TVECTOR_UPDATE(+=)
CAT_TVECTOR_UPDATE(-=)
CAT_TVECTOR_UPDATE(*=)
CAT_TVECTOR_UPDATE(/=)




};


#endif
