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

//array.C
//Implementation of class array

#include "../globals.h"


#include "storage.h"
#include "memory_reference.h"

#include "../tiny/tiny.h"

#include "../traits/traits.h"

#include "array_iterator.h"


#include <iostream>
#include <cassert>
using namespace std;

namespace cat
{

  //Iterator related methods
  
  //beginning iterator function
  template <class T,int D>
  array_const_iterator<T,D> array<T,D>::begin() const
  {
    return array_const_iterator<T,D>(*this,0);
  }

  //end iterator function
  template <class T,int D>
  array_const_iterator<T,D> array<T,D>::end() const
  {
    //Note that the size of the array must be the size of the block of memory
    return array_const_iterator<T,D>(*this,this->length_);
  }

  //References and Copies

#if 0
  //create a reference to this array
  //returns a new array that shares the data with the current array
  
  template <class T,int D>
  array<T,D> array<T,D>::reference()
  {
    array<T,D> out;
    out.shape()=this->shape_;
    out.size()=this->size_;
    out.stride()=this->stride_;
    return array<T,D>(out);
  }

  //make this array a reference to a given array
  //the data pointer points to the data of the given array
  template <class T,int D>
  void array<T,D>::reference(array<T,D> & rhs)
  {
    this->shape_=rhs.shape();
    this->size_=rhs.size();
    this->stride_=rhs.stride();
  }
#endif


  //create a new array by copying this array
  //(the new array has its own data)
  template <class T,int D>
  array<T,D> array<T,D>::copy()
  {
#if PRT_DBG_MSG
    cout << "Return a copy of *this" << endl;
#endif
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
  }

  //make this array a copy of a given array
  //the data is actually copied
  template <class T,int D>
  void array<T,D>::copy(const array<T,D> & rhs)
  {
#if PRT_DBG_MSG
    cout << "Copying rhs to *this" << endl;
#endif 
    if (this==&rhs)
      return; 

    if(this->size()==rhs.size())
      {
	array_iterator<T,D> a_iterator(*this);
	array_const_iterator<T,D> rhs_iterator(rhs);
	for (a_iterator=this->begin(),
	       rhs_iterator=rhs.begin();
	     a_iterator!=this->end(),
	       rhs_iterator!=rhs.end();
	     ++a_iterator,
	       ++rhs_iterator)
	  (*a_iterator)=(*rhs_iterator);
      }
    else if (this->size()>rhs.size())
      {
	array_iterator<T,D> a_iterator(*this);
	array_const_iterator<T,D> rhs_iterator(rhs);
	for (a_iterator=this->begin(),
	       rhs_iterator=rhs.begin();
	     //a_iterator!=this->end();
	       rhs_iterator!=rhs.end();
	     ++a_iterator,
	       ++rhs_iterator)
	  {
	    while((a_iterator.indices())!=(rhs_iterator.indices()))
	      {
		++a_iterator;
		(*a_iterator)=0;
	      }
	    (*a_iterator)=(*rhs_iterator);
	  }
      }
    else
      {
	//cout << "HHHHHHHHHH" << endl;
	array_iterator<T,D> a_iterator(*this);
	array_const_iterator<T,D> rhs_iterator(rhs);
	for (a_iterator=this->begin(),
	       rhs_iterator=rhs.begin();
	     a_iterator!=this->end();
	     ++rhs_iterator,
	       ++a_iterator)
	  {
	    //cout << a_iterator.pos() << " " <<  rhs_iterator.pos() << endl;
	    while(
		  (a_iterator.indices())!=(rhs_iterator.indices())
		  )
	      {
	       	++rhs_iterator;
		//cout << a_iterator.pos() << " " <<  rhs_iterator.pos() << endl;
	      }
	      (*a_iterator)=(*rhs_iterator);
	  }
      }
  }
  
  
  //create a new array by copying this array
   //(the new array has its own data)
   template <class T,int D>
   template <class T1,int D1>
   array<T1,D1> array<T,D>::copy()
  {
    array<T1,D1> out(this->shape());
    array_iterator<T1,D1> out_iterator(out);
    array_const_iterator<T,D> a_iterator(*this);
    for (a_iterator=(*this).begin(),
           out_iterator=out.begin();
	 a_iterator!=(*this).end(),
           out_iterator!=out.end();
	 ++a_iterator,
           ++out_iterator)
      *out_iterator=*a_iterator;
    return array<T1,D1>(out);
  }

  //make this array a copy of a given array
  //the data is actually copied
  template <class T,int D>
  template <class T1,int D1>
  void array<T,D>::copy(const array<T1,D1> & rhs)
  { 
    assert(this->size()==rhs.size());
    // cout << "InC" << endl; 
    array_iterator<T,D> a_iterator(*this);
    array_const_iterator<T1,D1> rhs_iterator(rhs);
    for (a_iterator=(*this).begin(),
           rhs_iterator=rhs.begin();
	 a_iterator!=(*this).end(),
           rhs_iterator!=rhs.end();
	 ++a_iterator,
           ++rhs_iterator)
      *a_iterator=*rhs_iterator;
    //cout << "ExC" << endl; 
  }






  //Constructors of array

  //default constructor
  //storage is instantiated by default
  //corresponding to c (row major storage order)
  template <class T,int D>
  array<T,D>::array():
    storage<D>(tvector<int,D>(0))
  {
#if PRT_DBG_MSG
    cout << "Default Constructor" << endl;
#endif  
  }

#if 1
  //copy constructor (really copies the array to the new field)
  template <class T,int D>
  array<T,D>::array(const array<T,D> & rhs):
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
  }
#endif




  //conversion constructor
  template <class T,int D>
  template <class T1,int D1>
  array<T,D>::array(const array<T1,D1> & rhs):
    storage<D>(rhs.shape(),rhs.ordering()),
    memory_reference<T>(rhs.size())
  {
#if PRT_DBG_MSG
    cout << "Conversion Constructor" << endl;
#endif
    //cout << "InC" << endl;
    
    this->copy(rhs);
    
    //cout << "ExC" << endl;
  }



  //constructor from shape
  template <class T,int D>
  array<T,D>::array(tvector<int,D> shape__):
    storage<D>(shape__),
    memory_reference<T>(size_)
  {
    #if PRT_DBG_MSG
    cout << "Constructor from shape" << endl;
    #endif
  }




  //constructors from size
  //1D arrays
  template <class T,int D>
  array<T,D>::array(int s1__):
    storage<1>(tvector<int,1>(s1__)),
    memory_reference<T>(size_)
  {
#if PRT_DBG_MSG
    cout << "Constructor from size (D=1)" << endl;
#endif
    assert(D==1);
  }
    //2D arrays
  template <class T,int D>
  array<T,D>::array(int s1__,int s2__):
    storage<2>(tvector<int,2>(s1__,s2__)),
    memory_reference<T>(size_)
  {
#if PRT_DBG_MSG
    cout << "Constructor from size (D=2)" << endl;
#endif
    assert(D==2);
  }
  //3D arrays
  template <class T,int D>
  array<T,D>::array(int s1__,int s2__,int s3__):
    storage<3>(tvector<int,3>(s1__,s2__,s3__)),
    memory_reference<T>(size_)
  {
#if PRT_DBG_MSG
    cout << "Constructor from size (D=3)" << endl;
#endif
    assert(D==3);
  }



#if 0
  //Constructor from shape and element of type T
  //Every element is initialised to T
  template <class T,int D>
  array<T,D>::array(const tvector<int,D> shape__,const T & element):
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
  }
#endif
    
  
  //THESE CONSTRUCTORS ARE FOR EXTRACTION
  
  //Constructor from shape,stride and data pointer
  template <class T,int D>
  array<T,D>::array(tvector<int,D> & shape__,
		    tvector<int,D> & ordering__,
		    tvector<int,D> & stride__,
		    size_t & length__,
		    T * data__):
    storage<D>(shape__,ordering__,stride__),
    memory_reference<T>(length__,data__)
  {
#if PRT_DBG_MSG
    cout << "Constructor from shape,stride and data pointer " << endl;
#endif
  }
      
  //Constructor from shape,stride and data pointer
  template <class T,int D>
  array<T,D>::array(const tvector<int,D> & shape__,
		    const tvector<int,D> & ordering__,
		    tvector<int,D> & stride__,
		    size_t & length__,
		    const T * data__):
    storage<D>(shape__,ordering__,stride__),
    memory_reference<T>(length__,const_cast<T*>(data__))
  {
#if PRT_DBG_MSG
    cout << "Constructor from shape,stride and data pointer - constant" << endl;
#endif
  }

      
  //Destructor
  template <class T,int D>
  array<T,D>::~array()
  {
  }

    //Other Accessors (indexing, pointers to data,...)




#if 0
  //Function for the extraction of components
  template<class T, int D>
  array<typename multicomponent_traits<T>::T_element,D> 
  extract_component(array<T,D> & a,
		    int component, 
		    int num_components)
  {
    typename multicomponent_traits<T>::T_element * ptr;
    ptr=&((*(a.data()))[component]);
    int nn = int( multicomponent_traits<T>::numComponents );
    tvector<int,D> new_stride(a.stride()*nn);
    size_t new_length(nn*a.length());
    return array<typename multicomponent_traits<T>::T_element,D>
      (
       a.shape(),
       a.ordering(),
       new_stride,
       new_length,
       ptr
       );
  }
  //Function for the extraction of components (constant version)
  template<class T, int D>
  array<typename multicomponent_traits<T>::T_element,D> 
  extract_component(const array<T,D> & a,
		    int component, 
		    int num_components)
  {
    typename multicomponent_traits<T>::T_element * ptr;
    ptr=&((*(a.data()))[component]);
    int nn = int( multicomponent_traits<T>::numComponents );
    tvector<int,D> new_stride(a.stride()*nn);
    size_t new_length(nn*a.length());
    return array<typename multicomponent_traits<T>::T_element,D>
      (
       a.shape(),
       a.ordering(),
       new_stride,
       new_length,
       ptr
       );
  }
  //Extraction operator
  template <class T,int D>
  array<typename multicomponent_traits<T>::T_element,D> 
  array<T,D>::operator[](const int component)
  {
    typedef typename multicomponent_traits<T>::T_element T_component;
    return array<T_component,D>
      (extract_component(*this,
			 component,
			 multicomponent_traits<T>::numComponents));
  }
  //Extraction operator(constant version)
  template <class T,int D>
  array<typename multicomponent_traits<T>::T_element,D>
  array<T,D>::operator[] (const int component) const
  {
    typedef const typename multicomponent_traits<T>::T_element T_component;
    return array<T_component,D>
      (extract_component(*this,
			 component,
			 multicomponent_traits<T>::numComponents));
  }
#endif


  //Extraction operator
  template <class T,int D>
  array<typename cat::multicomponent_traits<T>::T_element,D> 
  array<T,D>::operator[](const int component)
  {
    typename cat::multicomponent_traits<T>::T_element * ptr;
    ptr=&((*(this->data()))[component]);
    int nn = int( cat::multicomponent_traits<T>::numComponents );
    cat::tvector<int,D> new_stride(this->stride()*nn);
    size_t new_length(nn*length_);

    return array<typename cat::multicomponent_traits<T>::T_element,D>
      (
       this->shape(),
       this->ordering(),
       new_stride,
       new_length,
       ptr
       );
  }
  //Extraction operator(constant version)
  template <class T,int D>
  const array<typename cat::multicomponent_traits<T>::T_element,D>
  array<T,D>::operator[] (const int component) const
  {
    const typename cat::multicomponent_traits<T>::T_element * ptr;
    ptr=&((*(this->data()))[component]);
    int nn = int( cat::multicomponent_traits<T>::numComponents );
    cat::tvector<int,D> new_stride(this->stride()*nn);
    size_t new_length(nn*length_);
    
    return array<typename cat::multicomponent_traits<T>::T_element,D>
      (
       this->shape(),
       this->ordering(),
       new_stride,
       new_length,
       ptr
       );
  }




  
  //returns the element specfied by the indexes
  
  //1D
  template <class T,int D>
  T & array<T,D>::operator()(const int i1)
  {
    //assert(D==1);
    int index=stride_[0]*i1;
    assert(index>-1&&index<size_);
    return this->data()[index];
  }
  //1D (constant)
  template <class T,int D>
  const T & array<T,D>::operator()(const int i1) const
  {
    //assert(D==1);
    int index=stride_[0]*i1;
    assert(index>-1&&index<size_);
    return this->data()[index];
  }
  
  //2D
  template <class T,int D>
  T& array<T,D>::operator()(const int i1,const int i2)
  {
    int index=stride_[1]*i2+stride_[0]*i1;
    assert(index>-1&&index<size_);
    return this->data()[index];
  }

  //2D (constant)
  template <class T,int D>
  const T & array<T,D>::operator()(const int i1,const int i2) const
  {
    int index=stride_[1]*i2+stride_[0]*i1;
    assert(index>-1&&index<size_);
    return this->data()[index];
  }

  //3D
  template <class T,int D>
  T& array<T,D>::operator()(const int i1,const int i2,const int i3)
  {
    int index=stride_[2]*i3+stride_[1]*i2+stride_[0]*i1;
    //cout << index << endl;
    /* if(!(index>-1&&index<static_cast<int>(length_))) */
    /* 	cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl; */
    /*       assert(index>-1&&index<static_cast<int>(length_)); */
    return this->data()[index];
  }

  //3D (constant)
  template <class T,int D>
  const T & array<T,D>::operator()(const int i1,const int i2,const int i3) const
  {
    int index=stride_[2]*i3+stride_[1]*i2+stride_[0]*i1;
    //cout << index << endl;
    /* 	if(!(index>-1&&index<static_cast<int>(length_))) */
    /* 	  cout << i1 << " " << i2 << " " << i3 << " " << index << " " << stride_ << endl; */
    /* 	assert(index>-1&&index<static_cast<int>(length_)); */
    return this->data()[index];
  }

  //DD
  template <class T,int D>
  T & array<T,D>::operator()(const cat::tvector<int,D> shp)
  {
    int index=0;
    for(int i=0;i<D;++i)
      index+=stride_[i]*shp[i];
    return this->data()[index];
  }
  //DD (constant)
  template <class T,int D>
  const T & array<T,D>::operator()(const cat::tvector<int,D> shp) const
  {
    int index=0;
    for(int i=0;i<D;++i)
      index+=stride_[i]*shp[i];
    return this->data()[index];
  }
 




  //Assignement operators
  //to array
  template <class T,int D>
  array<T,D> & array<T,D>::operator=(const array & rhs)
    {
      copy(rhs);
      return *this;
    }

  template <class T,int D>
   template <class T1>
   array<T,D> & array<T,D>::operator=(const array<T1,D> & rhs)
   {
     copy(rhs);
     return *this;
   }

  //to scalar
  template <class T,int D>
  array<T,D> & array<T,D>::operator=(const T & rhs)
  {
    array_iterator<T,D> array_iterator(*this);
    for (array_iterator=(*this).begin();
	 array_iterator!=(*this).end();
	 ++array_iterator)
      {
	*array_iterator=rhs;
      }
    return *this;
  }


  template <class T,int D> 
  template <class T1>
  array<T,D> & array<T,D>::operator=(const T1 & rhs)
  {
    array_iterator<T,D> array_iterator(*this);
    for (array_iterator=(*this).begin();
	 array_iterator!=(*this).end();
	 ++array_iterator)
      {
	*array_iterator=rhs;
      }
    return *this;
  }



  //IO
  
  //redefiniton of cout
  
  //constant version
  template <class T,int D>
  std::ostream & operator<<(std::ostream& output,
					const array<T,D> & oarray)
  {
    array_const_iterator<T,D> array_iterator(oarray);
    for (array_iterator=(oarray).begin();
	 array_iterator!=--(oarray.end());
	 ++array_iterator)
      output << *array_iterator << "\n";
    output << *array_iterator;
    return output;
  }

  //non-constant version
  template <class T,int D>
  std::ostream & operator<<(std::ostream& output,
			    array<T,D> & oarray)
  {
    array_iterator<T,D> array_iterator(oarray);
    for (array_iterator=oarray.begin();
	 array_iterator!=--(oarray.end());
	 ++array_iterator)
      output << *array_iterator << "\n";
    output << *array_iterator;
    return output;
  }

  //redefiniton of cin
  template <class T,int D>
  std::istream & operator>>(std::istream& input,
			    array<T,D> & iarray)
  {
    array_iterator<T,D> array_iterator(iarray);
    for (array_iterator=(iarray).begin();
	 array_iterator!=(iarray).end();
	 ++array_iterator)
      input >> *array_iterator;
    return input;
  }




  




}

