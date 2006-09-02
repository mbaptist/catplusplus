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

#ifndef CAT_ARRAYCLASS_H
#define CAT_ARRAYCLASS_H


#include "../traits/traits.h"

//#include "array_iterator.h"

#include "array_expression.h"


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

    public:
	    //Subclasses
	    //Declared in array_iterator.h and Implemented in array_iterator.C
	    class iterator;
	    class const_iterator;
	    
    private:

      using storage<D>::ordering_;
      using storage<D>::shape_;
      using storage<D>::size_;
      using storage<D>::stride_;

//       using storage<D>::ordering;
//       using storage<D>::shape;
//       using storage<D>::size;
//       using storage<D>::stride;

      using memory_reference<T>::data_;
      using memory_reference<T>::length_;

//       using memory_reference<T>::data;
//       using memory_reference<T>::length;

    public:

      //Define an alias to element type
	    typedef T T_element;
	    //	    static const int Rank=D;
	    
      //Iterator related methods
      //begin iterator function
	    iterator begin();
      //end iterator function
	    iterator end();
	    //constant versions
      //begin iterator function
      const_iterator begin() const;
      //end iterator function
      const_iterator end() const;

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
      template <class T1,int D1>
      array<T1,D1> copy();

      //make this array a copy of a given array
      //the data is actually copied
      template <class T1,int D1>
      void copy(const array<T1,D1> & rhs);



      //Constructors of array


      //default constructor
      //storage is instantiated by default
      //corresponding to c (row major) storage order
      array();

      //copy constructor (really copies the array to the new field)
      array(const array & rhs);


      //conversion constructor
      template <class T1,int D1>
		    array(const array<T1,D1> & rhs);


	    template<class Expression>
		    array(ArrayExpression<Expression> rhs):
		    storage<D>(rhs.shape(),rhs.ordering()),
		    memory_reference<T>(rhs.size())
	    {		    
	// Get a beginning and end iterator for the vector
		    typename array<T,D>::iterator iter(*this);
		    typename array<T,D>::const_iterator endIter=this->end();
		    iter = this->begin();
		    
	// Store the result in the vector
		    do
		    {
			    *iter = *rhs;   // Inlined expression
			    //cout << *iter <<endl;
			    ++rhs;
		    } while (++iter != endIter);
	    };

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
      //explicit array(const tvector<int,D> shape__,const T & element);

	    explicit array( tvector<int,D> shape__,
	                    T * data__);	                    
    
    
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



      // template<class T1>
      //array<T1,D> extract_component
      //(T1,int component, int num_components);

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

      //DD
      T & operator()(const cat::tvector<int,D> shp);
      //DD (constant)
      const T & operator()(const cat::tvector<int,D> shp) const;

      //Assignement operators
      //to array
      array<T,D> & operator=(const array<T,D> & rhs);
      
      template <class T1>
      array<T,D> & operator=(const array<T1,D> & rhs);

      
      //to element
      array<T,D> & operator=(const T & rhs);
      template <class T1>
      array<T,D> & operator=(const T1 & rhs);



      template<class Expression>
      array<T,D> & operator=(ArrayExpression<Expression> result)
      {
	// Get a beginning and end iterator for the vector
	      typename array<T,D>::iterator iter(*this);
	      typename array<T,D>::const_iterator endIter=this->end();
	      iter = this->begin();
	      
	// Store the result in the vector
	      do
	      {
		      *iter = *result;   // Inlined expression
		//cout << *iter <<endl;
		      ++result;
	      } while (++iter != endIter);
	      
	return *this;
      };



      



      //For safety an unidirectional promotion should be implemented
      //in the code that follows

#define CAT_ARRAY_UPDATE(op) \
  template <class T1> \
  array<T,D> & operator op(const array<T1,D> & rhs) \
  { \
		   typename  array<T,D>::iterator array_iterator(*this); \
		    typename array<T1,D>::const_iterator rhs_iterator(rhs); \
    for (array_iterator=this->begin(), \
	   rhs_iterator=rhs.begin(); \
	 array_iterator!=this->end(), \
	   rhs_iterator!=rhs.end(); \
	 ++array_iterator, \
	   ++rhs_iterator) \
      (*array_iterator) op (*rhs_iterator); \
    return *this; \
  } \
  template <class T1>		  \
  array<T,D> & operator op(const T1 & rhs) \
  { \
		    typename array<T,D>::iterator array_iterator(*this); \
    for (array_iterator=this->begin(); \
	 array_iterator!=this->end(); \
	 ++array_iterator) \
      (*array_iterator) op rhs; \
    return *this; \
  }



	    CAT_ARRAY_UPDATE(+=);
	    CAT_ARRAY_UPDATE(-=);
	    CAT_ARRAY_UPDATE(*=);
	    CAT_ARRAY_UPDATE(/=);




	};


  }

#include "array_iterator.h"
#include "arrayclass.C"



#endif
