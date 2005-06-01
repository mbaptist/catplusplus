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

  //array.h
  //Declaration of class array

#ifndef CAT_ARRAY_H
#define CAT_ARRAY_H


#include "numeric.h"
#include "promote.h"
#include "multi.h"

#include "array_iterator.h"


#include <iostream>
#include <cassert>

  namespace cat
  {


    //Forwarding declarations
    //tiny vectors
    template <class T,int N>
    class tvector;
    //storage
    template <int D>
    class storage;
    //memory reference
    template <class T>
    class memory_reference;



    //Declaration of class array

    template <class T,int D>
    class array :
      public storage<D>,
      public memory_reference<T>
    {

    private:

      using storage<D>::ordering_;
      using storage<D>::shape_;
      using storage<D>::size_;
      using storage<D>::stride_;

      using memory_reference<T>::data_;
      using memory_reference<T>::length_;

    public:

      //Define an alias to element type
      typedef T T_element;

      //Iterator related methods

      //begin iterator function
      array_const_iterator<T,D> begin() const;

      //end iterator function
      array_const_iterator<T,D> end() const;

      //References and Copies

      //create a reference to this array
      //returns a new array that shares the data with the current array
      array<T,D> reference();

      //make this array a reference to a given array
      //the data pointer points to the data of the given array
      void reference(array<T,D> & rhs);

      //create a new array by copying this array
      //(the new array has its own data)
      array<T,D> copy();

      //make this array a copy of a given array
      //the data is actually copied
      void copy(const array<T,D> & rhs);

      //create a new array by copying this array
      //(the new array has its own data)
      template <class T1>
      array<T1,D> copy();

      //make this array a copy of a given array
      //the data is actually copied
      template <class T1>
      void copy(const array<T1,D> & rhs);



      //Constructors of array


      //default constructor
      //storage is instantiated by default
      //corresponding to c (row major) storage order
      explicit array();

      //copy constructor (really copies the array to the new field)
      array(const array & rhs);

      //conversion constructor
      template <class T1>
      array(const array<T1,D> & rhs);

      //constructor from shape
      explicit array(tvector<int,D> shape__);

      //constructors from size
      //1D arrays
      explicit array(int s1__);
      //2D arrays
      explicit array(int s1__,int s2__);
      //3D arrays
      explicit array(int s1__,int s2__,int s3__);


      //Constructor from shape and element of type T
      //Every element is initialised to T
      explicit array(const tvector<int,D> shape__,const T & element);

    
    
    
      //THESE CONSTRUCTORS ARE FOR EXTRACTION

      //Constructor from shape,stride and data pointer
      explicit array(tvector<int,D> & shape__,
		     tvector<int,D> & ordering__,
		     tvector<int,D> & stride__,
		     size_t & length__,
		     T * data__);
    
      //Constructor from shape,stride and data pointer
      explicit array(const tvector<int,D> & shape__,
		     const tvector<int,D> & ordering__,
		     tvector<int,D> & stride__,
		     size_t & length__,
		     const T * data__);

      //Destructor
      ~array();




      //Other Accessors (indexing, pointers to data,...)


      //Extract component operator
      array<typename multicomponent_traits<T>::T_element,D> 
      operator[](const int component);
      const array<typename multicomponent_traits<T>::T_element,D>
      operator[] (const int component) const;


      //returns the element specfied by the indexes
      //1D
      T & operator()(const int i1);
      //1D (constant)
      const T & operator()(const int i1) const;
      //2D
      T& operator()(const int i1,const int i2);
      //2D (constant)
      const T & operator()(const int i1,const int i2) const;
      //3D
      T& operator()(const int i1,const int i2,const int i3);
      //3D (constant)
      const T & operator()(const int i1,const int i2,const int i3) const;


      //Assignement operators
      //to array
      array & operator=(const array & rhs);
      template <class T1>
      array & operator=(const array<T1,D> & rhs);


      //to scalar
      template <class T1>
      array& operator=(const T1 & rhs);



#define CAT_ARRAY_UPDATE(op) \
  template <class T1> \
  array<T,D> & operator op(const array<T1,D> & rhs) \
  { \
    array_iterator<T,D> array_iterator(*this); \
    array_const_iterator<T1,D> rhs_iterator(rhs); \
    for (array_iterator=(*this).begin(), \
	   rhs_iterator=rhs.begin(); \
	 array_iterator!=(*this).end(), \
	   rhs_iterator!=rhs.end(); \
	 ++array_iterator, \
	   ++rhs_iterator) \
      (*array_iterator) op (*rhs_iterator); \
    return *this; \
  } \
  template <class T1> \
  array<T,D> & operator op(const T1 & rhs) \
  { \
    array_iterator<T,D> array_iterator(*this); \
    for (array_iterator=(*this).begin(); \
	 array_iterator!=(*this).end(); \
	 ++array_iterator) \
      (*array_iterator) op rhs; \
    return *this; \
  }



      CAT_ARRAY_UPDATE(+=)
	CAT_ARRAY_UPDATE(-=)
	CAT_ARRAY_UPDATE(*=)
	CAT_ARRAY_UPDATE(/=)




	};


  }


#include "array.C"


#endif
