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

  //Array.h
  //Declaration of class Array

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
    class Tvector;
    //storage
    template <int D>
    class storage;
    //memory reference
    template <class T>
    class memory_reference;



    //Declaration of class Array

    template <class T,int D>
    class Array :
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

      //create a reference to this Array
      //returns a new Array that shares the data with the current Array
      Array<T,D> reference();

      //make this Array a reference to a given Array
      //the data pointer points to the data of the given Array
      void reference(Array<T,D> & rhs);

      //create a new Array by copying this Array
      //(the new Array has its own data)
      Array<T,D> copy();

      //make this Array a copy of a given Array
      //the data is actually copied
      void copy(const Array<T,D> & rhs);

      //create a new Array by copying this Array
      //(the new Array has its own data)
      template <class T1,int D1>
      Array<T1,D1> copy();

      //make this Array a copy of a given Array
      //the data is actually copied
      template <class T1,int D1>
      void copy(const Array<T1,D1> & rhs);



      //Constructors of Array


      //default constructor
      //storage is instantiated by default
      //corresponding to c (row major) storage order
      Array();

      //copy constructor (really copies the Array to the new field)
      Array(const Array & rhs);


      //conversion constructor
      template <class T1,int D1>
		    Array(const Array<T1,D1> & rhs);


	    template<class Expression>
		    Array(ArrayExpression<Expression> rhs):
		    storage<D>(rhs.shape(),rhs.ordering()),
		    memory_reference<T>(rhs.size())
	    {		    
	// Get a beginning and end iterator for the vector
		    typename Array<T,D>::iterator iter(*this);
		    typename Array<T,D>::const_iterator endIter=this->end();
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
      
      explicit Array(Tvector<int,D> shape__);

      //constructors from size
      //1D Arrays
      explicit Array(int s1__);
      //2D Arrays
      explicit Array(int s1__,int s2__);
      //3D Arrays
      explicit Array(int s1__,int s2__,int s3__);


      //Constructor from shape and element of type T
      //Every element is initialised to T
      //explicit Array(const Tvector<int,D> shape__,const T & element);

	    explicit Array( Tvector<int,D> shape__,
	                    T * data__);	                    
    
    
      //THESE CONSTRUCTORS ARE FOR EXTRACTION

      //Constructor from shape,stride and data pointer
      explicit Array(Tvector<int,D> & shape__,
		     Tvector<int,D> & ordering__,
		     Tvector<int,D> & stride__,
		     size_t & length__,
		     T * data__);
    
      //Constructor from shape,stride and data pointer
      explicit Array(const Tvector<int,D> & shape__,
		     const Tvector<int,D> & ordering__,
		     Tvector<int,D> & stride__,
		     size_t & length__,
		     const T * data__);

      //Destructor
      ~Array();




      //Other Accessors (indexing, pointers to data,...)



      // template<class T1>
      //Array<T1,D> extract_component
      //(T1,int component, int num_components);

      //Extract component operator
      Array<typename multicomponent_traits<T>::T_element,D> 
      operator[](const int component);
      const Array<typename multicomponent_traits<T>::T_element,D>
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
      T & operator()(const cat::Tvector<int,D> shp);
      //DD (constant)
      const T & operator()(const cat::Tvector<int,D> shp) const;

      //Assignement operators
      //to Array
      Array<T,D> & operator=(const Array<T,D> & rhs);
      
      template <class T1>
      Array<T,D> & operator=(const Array<T1,D> & rhs);

      
      //to element
      Array<T,D> & operator=(const T & rhs);
      template <class T1>
      Array<T,D> & operator=(const T1 & rhs);



      template<class Expression>
      Array<T,D> & operator=(ArrayExpression<Expression> result)
      {
	// Get a beginning and end iterator for the vector
	      typename Array<T,D>::iterator iter(*this);
	      typename Array<T,D>::const_iterator endIter=this->end();
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
  Array<T,D> & operator op(const Array<T1,D> & rhs) \
  { \
		   typename  Array<T,D>::iterator array_iterator(*this); \
		    typename Array<T1,D>::const_iterator rhs_iterator(rhs); \
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
  Array<T,D> & operator op(const T1 & rhs) \
  { \
		    typename Array<T,D>::iterator array_iterator(*this); \
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


#define CAT_ARRAY_UPDATE_EXPRESSION(op) \
	    template <class Expression> \
		    Array & operator op(ArrayExpression<Expression> rhs) \
		    { \
		    typename  Array<T,D>::iterator array_iterator(*this); \
		    for (array_iterator=this->begin(); \
		    array_iterator!=this->end(); \
		    ++array_iterator, \
		    ++rhs) \
		    (*array_iterator) op (*rhs); \
		    return *this; \
    }

#ifdef USE_EXPRESSIONS
	    CAT_ARRAY_UPDATE_EXPRESSION(+=);
	    CAT_ARRAY_UPDATE_EXPRESSION(-=);
	    CAT_ARRAY_UPDATE_EXPRESSION(*=);
	    CAT_ARRAY_UPDATE_EXPRESSION(/=);
#endif

	};


  }

#include "array_iterator.h"
#include "arrayclass.C"



#endif
