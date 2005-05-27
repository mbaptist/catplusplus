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

//array.h
//Implements Arrays

#ifndef CAT_ARRAY_H
#define CAT_ARRAY_H

#include "storage.h"
#include "memory_reference.h"

#include "tvector.h"

#include "numeric.h"
#include "promote.h"
#include "multi.h"

#include "array_iterator.h"


#include <iostream>
#include <cassert>
using namespace std;

namespace cat
{

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
    typedef T Telement;



    //Iterator related methods

    //beginning iterator function
    array_const_iterator<T,D> begin() const
      {
        return array_const_iterator<T,D>(*this,0);
      };

    //end iterator function
    array_const_iterator<T,D> end() const
      {
        //Note that the size of the array must be the size of the block of memory
        return array_const_iterator<T,D>(*this,this->length_);
      };





    //References and Copies

#if 0
    //create a reference to this array
    //returns a new array that shares the data with the current array
    array<T,D> reference()
    {
      array<T,D> out;
      out.shape()=this->shape_;
      out.size()=this->size_;
      out.stride()=this->stride_;
      return array<T,D>(out);
    };

    //make this array a reference to a given array
    //the data pointer points to the data of the given array
    void reference(array<T,D> & rhs)
    {
      this->shape_=rhs.shape();
      this->size_=rhs.size();
      this->stride_=rhs.stride();
    };
#endif


    //create a new array by copying this array
    //(the new array has its own data)
    array<T,D> copy()
    {
      array<T,D> out(this->shape());
      array_iterator<T,D> out_iterator(out);
      array_const_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin(),
           out_iterator=out.begin();
           array_iterator!=(*this).end(),
           out_iterator!=out.end();
           ++array_iterator,
           ++out_iterator)
        *out_iterator=*array_iterator;
      return array<T,D>(out);
    };

    //make this array a copy of a given array
    //the data is actually copied
    void copy(const array<T,D> & rhs)
    {      
      if (this==&rhs)
	return;
      assert(this->size()==rhs.size());

      //cout << "InC" << endl; 
      array_iterator<T,D> array_iterator(*this);
      array_const_iterator<T,D> rhs_iterator(rhs);
      for (array_iterator=(*this).begin(),
           rhs_iterator=rhs.begin();
           array_iterator!=(*this).end(),
           rhs_iterator!=rhs.end();
           ++array_iterator,
           ++rhs_iterator)
        *array_iterator=*rhs_iterator;
      //cout << "ExC" << endl; 
    };


    //create a new array by copying this array
    //(the new array has its own data)
    template <class T1>
    array<T1,D> copy()
    {
      
      array<T1,D> out(this->shape());
      array_iterator<T1,D> out_iterator(out);
      array_const_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin(),
           out_iterator=out.begin();
           array_iterator!=(*this).end(),
           out_iterator!=out.end();
           ++array_iterator,
           ++out_iterator)
        *out_iterator=*array_iterator;

      return array<T1,D>(out);
    };

    //make this array a copy of a given array
    //the data is actually copied
    template <class T1>
    void copy(const array<T1,D> & rhs)
    { 
      
      assert(this->size()==rhs.size());

      // cout << "InC" << endl; 
      array_iterator<T,D> array_iterator(*this);
      array_const_iterator<T1,D> rhs_iterator(rhs);
      for (array_iterator=(*this).begin(),
           rhs_iterator=rhs.begin();
           array_iterator!=(*this).end(),
           rhs_iterator!=rhs.end();
           ++array_iterator,
           ++rhs_iterator)
        *array_iterator=*rhs_iterator;
      //cout << "ExC" << endl; 
    };





    //Constructors of array


    //default constructor
    //storage is instantiated by default
    //corresponding to c (row major storage order)
    explicit array():
        storage<D>(tvector<int,D>(0))
    {
#if PRT_DBG_MSG
      cout << "Default Constructor" << endl;
#endif

    };

    //copy constructor (really copies the array to the new field)
     array(const array & rhs):
        storage<D>(rhs.shape(),rhs.ordering()),
        memory_reference<T>(rhs.size())
    {
#if PRT_DBG_MSG
      cout << "Copy Constructor" << endl;
#endif
      //cout << "InC" << endl;      
      if (this==&rhs)
	return;
      this->copy(rhs);
      //cout << "ExC" << endl;
    };


    //conversion constructor
    template <class T1>
    array(const array<T1,D> & rhs):
        storage<D>(rhs.shape(),rhs.ordering()),
        memory_reference<T>(rhs.size())
    {
#if PRT_DBG_MSG
      cout << "Conversion Constructor" << endl;
#endif
      //cout << "InC" << endl;

      this->copy(rhs);

      //cout << "ExC" << endl;
    };

    //constructor from shape
    explicit array(tvector<int,D> shape__):
        storage<D>(shape__),
        memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape" << endl;
#endif

    };

    //constructors from size
    //1D arrays
    explicit array(int s1__):
        storage<1>(tvector<int,1>(s1__)),
        memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=1)" << endl;
#endif

      assert(D==1);
    };
    //2D arrays
    explicit array(int s1__,int s2__):
        storage<2>(tvector<int,2>(s1__,s2__)),
        memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=2)" << endl;
#endif

      assert(D==2);
    };
    //3D arrays
    explicit array(int s1__,int s2__,int s3__):
        storage<3>(tvector<int,3>(s1__,s2__,s3__)),
        memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=3)" << endl;
#endif

      assert(D==3);
    };


    //Constructor from shape and element of type T
    //Every element is initialised to T
   explicit array(const tvector<int,D> shape__,const T & element):
        storage<D>(shape__),
        memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and element" << endl;
#endif
      array_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin();
           array_iterator!=(*this).end();
           ++array_iterator)
        *array_iterator=element;
    };

    
    
    
    //THESE CONSTRUCTORS ARE FOR EXTRACTION

    //Constructor from shape,stride and data pointer
    explicit array(tvector<int,D> & shape__,tvector<int,D> & ordering__,tvector<int,D> & stride__,size_t & length__,T * data__):
      storage<D>(shape__,ordering__,stride__),
      memory_reference<T>(length__,data__)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and reference" << endl;
#endif
    };
    
    
   //Constructor from shape,stride and data pointer
    explicit array(const tvector<int,D> & shape__,const tvector<int,D> & ordering__,tvector<int,D> & stride__,size_t & length__,const T * data__):
      storage<D>(shape__,ordering__,stride__),
      memory_reference<T>(length__,const_cast<T*>(data__))
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and reference" << endl;
#endif
    };

    

    


    
    //Destructor
    ~array()
    {}
    ;



    
    
//     void reshape(const tvector<int,D> & shape__)
//     {
//         storage_reshape(shape__);
//         memory_block_resize(size_);
//     }    
    
    
    




    //Other Accessors (indexing, pointers to data,...)


    //Extract component operator
#if 1

    array<typename multicomponent_traits<T>::T_element,D> 
    operator[](const int component)
    {
      typename multicomponent_traits<T>::T_element * ptr;
      ptr=&((*(this->data()))[component]);
      int nn = int( multicomponent_traits<T>::numComponents );
      tvector<int,D> new_stride(this->stride()*nn);
      size_t new_length(nn*length_);

      return array<typename multicomponent_traits<T>::T_element,D>
             (
               this->shape(),
               this->ordering(),
               new_stride,
               new_length,
               ptr
             );

    };
#endif
    #if 1

    const array<typename multicomponent_traits<T>::T_element,D>
    operator[] (const int component) const
      {
        const typename multicomponent_traits<T>::T_element * ptr;
        ptr=&((*(this->data()))[component]);
        int nn = int( multicomponent_traits<T>::numComponents );
        tvector<int,D> new_stride(this->stride()*nn);
        size_t new_length(nn*length_);


        return array<typename multicomponent_traits<T>::T_element,D>
               (
                 this->shape(),
                 this->ordering(),
                 new_stride,
                 new_length,
                 ptr
               );
      };
#endif


    //returns the element specfied by the indexes

    //1D
    T & operator()(const int i1)
    {
      //assert(D==1);
      int index=stride_[0]*i1;
      assert(index>-1&&index<size_);
      return this->data()[index];
    };
    //1D (constant)
    const T & operator()(const int i1) const
      {
        //assert(D==1);
	int index=stride_[0]*i1;
	assert(index>-1&&index<size_);
        return this->data()[index];
      };

    //2D
    T& operator()(const int i1,const int i2)
    {
      int index=stride_[1]*i2+stride_[0]*i1;
      assert(index>-1&&index<size_);
      return this->data()[index];
    };

    //2D (constant)
    const T & operator()(const int i1,const int i2) const
      {
	int index=stride_[1]*i2+stride_[0]*i1;
	assert(index>-1&&index<size_);
        return this->data()[index];
      };

    //3D
    T& operator()(const int i1,const int i2,const int i3)
    {
      int index=stride_[2]*i3+stride_[1]*i2+stride_[0]*i1;
      //cout << index << endl;
      /* if(!(index>-1&&index<static_cast<int>(length_))) */
/* 	cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl; */
/*       assert(index>-1&&index<static_cast<int>(length_)); */
      return this->data()[index];
    };

    //3D (constant)
    const T & operator()(const int i1,const int i2,const int i3) const
      {
	int index=stride_[2]*i3+stride_[1]*i2+stride_[0]*i1;
	//cout << index << endl;
/* 	if(!(index>-1&&index<static_cast<int>(length_))) */
/* 	  cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl; */
/* 	assert(index>-1&&index<static_cast<int>(length_)); */
	return this->data()[index];
      };







    //IO

    //redefiniton of cout

    //constant version
    friend std::ostream & operator<<(std::ostream& output,const array & oarray)
    {
      array_const_iterator<T,D> array_iterator(oarray);
      for (array_iterator=(oarray).begin();
           array_iterator!=--(oarray.end());
           ++array_iterator)
        output << *array_iterator << "\n";
      output << *array_iterator;
      return output;
    };

    //non-constant version
    friend std::ostream & operator<<(std::ostream& output,array & oarray)
    {
      array_iterator<T,D> array_iterator(oarray);
      for (array_iterator=oarray.begin();
           array_iterator!=--(oarray.end());
           ++array_iterator)
        output << *array_iterator << "\n";
      output << *array_iterator;
      return output;
    };

    //redefiniton of cin

    friend std::istream & operator>>(std::istream& input,array & iarray)
    {
      array_iterator<T,D> array_iterator(iarray);
      for (array_iterator=(iarray).begin();
           array_iterator!=(iarray).end();
           ++array_iterator)
        input >> *array_iterator;
      return input;
    };



    //Assignement operators
    //to array
    array & operator=(const array & rhs)
    {
      copy(rhs);
      return *this;
    }
    template <class T1>
    array & operator=(const array<T1,D> & rhs)
    {
      copy(rhs);
      return *this;
    }

    //to scalar
    template <class T1>
    array& operator=(const T1 & rhs)
    {
      array_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin();
           array_iterator!=(*this).end();
           ++array_iterator)
        {
          *array_iterator=rhs;
        }
      return *this;
    };



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

#endif
