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

//cat_array.h
//Implements Arrays

#ifndef CAT_ARRAY_H
#define CAT_ARRAY_H


#include "cat_storage.h"
#include "cat_memory_reference.h"

#include "cat_tvector.h"

#include "cat_numeric.h"
#include "cat_promote.h"
#include "cat_multi.h"

#include "cat_array_iterator.h"


#include <iostream>
#include <cassert>
using namespace std;



template <class T,int D>
class cat_array :
      public cat_storage<D>,
      public cat_memory_reference<T>
  {

  private:

    using cat_storage<D>::ordering_;
    using cat_storage<D>::shape_;
    using cat_storage<D>::size_;
    using cat_storage<D>::stride_;

    using cat_memory_reference<T>::data_;
    using cat_memory_reference<T>::length_;

  public:

    //Define an alias to element type
    typedef T Telement;



    //Iterator related methods

    //beginning iterator function
    cat_array_const_iterator<T,D> begin() const
      {
        return cat_array_const_iterator<T,D>(*this,0);
      };

    //end iterator function
    cat_array_const_iterator<T,D> end() const
      {
        //Note that the size of the array must be the size of the block of memory
        return cat_array_const_iterator<T,D>(*this,this->length_);
      };





    //References and Copies

#if 0
    //create a reference to this array
    //returns a new array that shares the data with the current array
    cat_array<T,D> reference()
    {
      cat_array<T,D> out;
      out.shape()=this->shape_;
      out.size()=this->size_;
      out.stride()=this->stride_;
      return cat_array<T,D>(out);
    };

    //make this array a reference to a given array
    //the data pointer points to the data of the given array
    void reference(cat_array<T,D> & rhs)
    {
      this->shape_=rhs.shape();
      this->size_=rhs.size();
      this->stride_=rhs.stride();
    };
#endif


    //create a new array by copying this array
    //(the new array has its own data)
    cat_array<T,D> copy()
    {
      cat_array<T,D> out(this->shape());
      cat_array_iterator<T,D> out_iterator(out);
      cat_array_const_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin(),
           out_iterator=out.begin();
           array_iterator!=(*this).end(),
           out_iterator!=out.end();
           ++array_iterator,
           ++out_iterator)
        *out_iterator=*array_iterator;
      return cat_array<T,D>(out);
    };

    //make this array a copy of a given array
    //the data is actually copied
    void copy(const cat_array<T,D> & rhs)
    {      
      if (this==&rhs)
	return;
      assert(this->size()==rhs.size());

      //cout << "InC" << endl; 
      cat_array_iterator<T,D> array_iterator(*this);
      cat_array_const_iterator<T,D> rhs_iterator(rhs);
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
    cat_array<T1,D> copy()
    {
      
      cat_array<T1,D> out(this->shape());
      cat_array_iterator<T1,D> out_iterator(out);
      cat_array_const_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin(),
           out_iterator=out.begin();
           array_iterator!=(*this).end(),
           out_iterator!=out.end();
           ++array_iterator,
           ++out_iterator)
        *out_iterator=*array_iterator;

      return cat_array<T1,D>(out);
    };

    //make this array a copy of a given array
    //the data is actually copied
    template <class T1>
    void copy(const cat_array<T1,D> & rhs)
    { 
      
      assert(this->size()==rhs.size());

      // cout << "InC" << endl; 
      cat_array_iterator<T,D> array_iterator(*this);
      cat_array_const_iterator<T1,D> rhs_iterator(rhs);
      for (array_iterator=(*this).begin(),
           rhs_iterator=rhs.begin();
           array_iterator!=(*this).end(),
           rhs_iterator!=rhs.end();
           ++array_iterator,
           ++rhs_iterator)
        *array_iterator=*rhs_iterator;
      //cout << "ExC" << endl; 
    };





    //Constructors of cat_array


    //default constructor
    //cat_storage is instantiated by default
    //corresponding to c (row major storage order)
    cat_array():
        cat_storage<D>(cat_tvector<int,D>(0))
    {
#if PRT_DBG_MSG
      cout << "Default Constructor" << endl;
#endif

    };

    //copy constructor (really copies the array to the new field)
    cat_array(const cat_array & rhs):
        cat_storage<D>(rhs.shape(),rhs.ordering()),
        cat_memory_reference<T>(rhs.size())
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
    explicit cat_array(const cat_array<T1,D> & rhs):
        cat_storage<D>(rhs.shape(),rhs.ordering()),
        cat_memory_reference<T>(rhs.size())
    {
#if PRT_DBG_MSG
      cout << "Conversion Constructor" << endl;
#endif
      //cout << "InC" << endl;

      this->copy(rhs);

      //cout << "ExC" << endl;
    };

    //constructor from shape
    explicit cat_array(cat_tvector<int,D> shape__):
        cat_storage<D>(shape__),
        cat_memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape" << endl;
#endif

    };

    //constructors from size
    //1D arrays
    explicit cat_array(int s1__):
        cat_storage<1>(cat_tvector<int,1>(s1__)),
        cat_memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=1)" << endl;
#endif

      assert(D==1);
    };
    //2D arrays
    explicit cat_array(int s1__,int s2__):
        cat_storage<2>(cat_tvector<int,2>(s1__,s2__)),
        cat_memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=2)" << endl;
#endif

      assert(D==2);
    };
    //3D arrays
    explicit cat_array(int s1__,int s2__,int s3__):
        cat_storage<3>(cat_tvector<int,3>(s1__,s2__,s3__)),
        cat_memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from size (D=3)" << endl;
#endif

      assert(D==3);
    };


    //Constructor from shape and element of type T
    //Every element is initialised to T
    cat_array(const cat_tvector<int,D> shape__,const T & element):
        cat_storage<D>(shape__),
        cat_memory_reference<T>(size_)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and element" << endl;
#endif
      cat_array_iterator<T,D> array_iterator(*this);
      for (array_iterator=(*this).begin();
           array_iterator!=(*this).end();
           ++array_iterator)
        *array_iterator=element;
    };

    
    
    
    //THESE CONSTRUCTORS ARE FOR EXTRACTION

    //Constructor from shape,stride and data pointer
    cat_array(cat_tvector<int,D> & shape__,cat_tvector<int,D> & ordering__,cat_tvector<int,D> & stride__,size_t & length__,T * data__):
      cat_storage<D>(shape__,ordering__,stride__),
      cat_memory_reference<T>(length__,data__)
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and reference" << endl;
#endif
    };
    
    
   //Constructor from shape,stride and data pointer
    cat_array(const cat_tvector<int,D> & shape__,const cat_tvector<int,D> & ordering__,cat_tvector<int,D> & stride__,size_t & length__,const T * data__):
      cat_storage<D>(shape__,ordering__,stride__),
      cat_memory_reference<T>(length__,const_cast<T*>(data__))
    {
#if PRT_DBG_MSG
      cout << "Constructor from shape and reference" << endl;
#endif
    };

    
    
    //Destructor
    ~cat_array()
    {}
    ;



    
    
//     void reshape(const cat_tvector<int,D> & shape__)
//     {
//         cat_storage_reshape(shape__);
//         cat_memory_block_resize(size_);
//     }    
    
    
    




    //Other Accessors (indexing, pointers to data,...)


    //Extract component operator
#if 1

    cat_array<typename cat_multicomponent_traits<T>::T_element,D> 
    operator[](const int component)
    {
      typename cat_multicomponent_traits<T>::T_element * ptr;
      ptr=&((*(this->data()))[component]);
      int nn = int( cat_multicomponent_traits<T>::numComponents );
      cat_tvector<int,D> new_stride(this->stride()*nn);
      size_t new_length(nn*length_);

      return cat_array<typename cat_multicomponent_traits<T>::T_element,D>
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

    const cat_array<typename cat_multicomponent_traits<T>::T_element,D>
    operator[] (const int component) const
      {
        const typename cat_multicomponent_traits<T>::T_element * ptr;
        ptr=&((*(this->data()))[component]);
        int nn = int( cat_multicomponent_traits<T>::numComponents );
        cat_tvector<int,D> new_stride(this->stride()*nn);
        size_t new_length(nn*length_);


        return cat_array<typename cat_multicomponent_traits<T>::T_element,D>
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
      if(!(index>-1&&index<static_cast<int>(length_)))
	cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl;
      assert(index>-1&&index<static_cast<int>(length_));
      return this->data()[index];
    };

    //3D (constant)
    const T & operator()(const int i1,const int i2,const int i3) const
      {
	int index=stride_[2]*i3+stride_[1]*i2+stride_[0]*i1;
	//cout << index << endl;
	if(!(index>-1&&index<static_cast<int>(length_)))
	  cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl;
	assert(index>-1&&index<static_cast<int>(length_));
	return this->data()[index];
      };







    //IO

    //redefiniton of cout

    //constant version
    friend std::ostream & operator<<(std::ostream& output,const cat_array & oarray)
    {
      cat_array_const_iterator<T,D> array_iterator(oarray);
      for (array_iterator=(oarray).begin();
           array_iterator!=--(oarray.end());
           ++array_iterator)
        output << *array_iterator << "\n";
      output << *array_iterator;
      return output;
    };

    //non-constant version
    friend std::ostream & operator<<(std::ostream& output,cat_array & oarray)
    {
      cat_array_iterator<T,D> array_iterator(oarray);
      for (array_iterator=oarray.begin();
           array_iterator!=--(oarray.end());
           ++array_iterator)
        output << *array_iterator << "\n";
      output << *array_iterator;
      return output;
    };

    //redefiniton of cin

    friend std::istream & operator>>(std::istream& input,cat_array & iarray)
    {
      cat_array_iterator<T,D> array_iterator(iarray);
      for (array_iterator=(iarray).begin();
           array_iterator!=(iarray).end();
           ++array_iterator)
        input >> *array_iterator;
      return input;
    };



    //Assignement operators
    //to cat_array
    cat_array & operator=(const cat_array & rhs)
    {
      copy(rhs);
      return *this;
    }
    template <class T1>
    cat_array & operator=(const cat_array<T1,D> & rhs)
    {
      copy(rhs);
      return *this;
    }

    //to scalar
    template <class T1>
    cat_array& operator=(const T1 & rhs)
    {
      cat_array_iterator<T,D> array_iterator(*this);
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
  cat_array<T,D> & operator op(const cat_array<T1,D> & rhs) \
  { \
    cat_array_iterator<T,D> array_iterator(*this); \
    cat_array_const_iterator<T1,D> rhs_iterator(rhs); \
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
  cat_array<T,D> & operator op(const T1 & rhs) \
  { \
    cat_array_iterator<T,D> array_iterator(*this); \
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


#endif
