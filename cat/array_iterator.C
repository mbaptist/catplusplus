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

  //array_iterator.C


#include "tvector.h"
#include "array.h"


  namespace cat
  {

    //// CONSTANT ITERATOR
  
    template <class T,int D>   
    T * array_const_iterator<T,D>::data()
    {
      return data_;
    }
    
    template <class T,int D> 
    const T * array_const_iterator<T,D>::data() const 
    {
      return data_;
    }
  
    //tvector<int,D> & indexes(){return indexes_;};
    //const tvector<int,D> & indexes() const {return indexes_;};
    
    template <class T,int D> 
    int & array_const_iterator<T,D>::pos()
    {
      return pos_;
    }    
    template <class T,int D> 
    const int & array_const_iterator<T,D>::pos() const 
    {
      return pos_;
    }
  
    template <class T,int D> 
    tvector<int,D> & array_const_iterator<T,D>::stride(){
      return stride_;
    }   
    template <class T,int D>  
    const tvector<int,D> & array_const_iterator<T,D>::stride() const 
    {
      return stride_;
    }
  
    template <class T,int D> 
    int & array_const_iterator<T,D>::navstride()
    {
      return navstride_;
    }    
    template <class T,int D> 
    const int & array_const_iterator<T,D>::navstride() const 
    {
      return navstride_;
    }
  
    //constructor
    //from array  
    template <class T,int D> 
    array_const_iterator<T,D>::array_const_iterator(const array<T,D> & array__):
      data_(const_cast<T *>(array__.data())),
      length_(array__.length()),
      stride_(array__.stride()),
      navstride_(stride_[array__.ordering()[0]])
    {
    }
    //from array and position  
    template <class T,int D> 
    array_const_iterator<T,D>::array_const_iterator(const array<T,D> & array__,
						    int pos__):
      data_(0),
      length_(array__.length()),
      pos_(pos__),
      stride_(array__.stride()),
      navstride_(stride_[array__.ordering()[0]])
    {
    }

    //destructor  
    template <class T,int D> 
    array_const_iterator<T,D>::~array_const_iterator()
    {
    }
    
    template <class T,int D> 
    const T & array_const_iterator<T,D>::operator*() const 
    {
      assert((pos_>-1)&&(pos_<length_));
      return data_[pos_];
    }
    
    template <class T,int D> 
    const T & array_const_iterator<T,D>::operator->() const 
    {
      assert((pos_>-1)&&(pos_<length_));
      return data_[pos_];
    }

    
    template <class T,int D> 
    array_const_iterator<T,D> & array_const_iterator<T,D>::operator++()
    {
      this->pos_+=this->navstride_;
      return (*this);
    }
  
    template <class T,int D> 
    array_const_iterator<T,D> & array_const_iterator<T,D>::operator--()
    {
      this->pos_-=this->navstride_;
      return (*this);
    }
  
    template <class T,int D> 
    bool array_const_iterator<T,D>::operator==(const array_const_iterator & rhs)
    {
      return bool((this->pos_)==(rhs.pos()));
    }
  
    
    template <class T,int D> 
    bool array_const_iterator<T,D>::operator!=(const array_const_iterator & rhs)
    {
      return bool((this->pos_)!=(rhs.pos()));
    }
    
    
    template <class T,int D> 
    array_const_iterator<T,D> & array_const_iterator<T,D>::operator=(const array_const_iterator & rhs)
    {
      this->pos_=rhs.pos();
      this->stride_=rhs.stride();
      this->navstride_=rhs.navstride();
      return (*this);
    }
  
    


    //// ITERATOR


    template <class T,int D> 
    array_iterator<T,D>::array_iterator(array<T,D> & array_):
      array_const_iterator<T,D>(array_)
    {
    }

    //destructor  
    template <class T,int D> 
    array_iterator<T,D>::~array_iterator()
    {
    }

    
    template <class T,int D> 
    T & array_iterator<T,D>::operator*()
    {
      assert((pos_>-1)&&(pos_<length_));
      return data_[pos_];
    }
  
    template <class T,int D> 
    T & array_iterator<T,D>::operator->()
    {
      assert((pos_>-1)&&(pos_<length_));
      return data_[pos_];
    }
  
    template <class T,int D> 
    bool array_iterator<T,D>::operator==(const array_const_iterator<T,D> & rhs)
    {
      return bool((this->pos_)==(rhs.pos()));
    }
  
    
    template <class T,int D> 
    bool array_iterator<T,D>::operator!=(const array_const_iterator<T,D> & rhs)
    {
      return bool((this->pos_)!=(rhs.pos()));
    }
    
    
    template <class T,int D> 
    array_iterator<T,D> & array_iterator<T,D>::operator=(const array_const_iterator<T,D> & rhs)
    {
      this->pos_=rhs.pos();
      this->stride_=rhs.stride();
      this->navstride_=rhs.navstride();
      return (*this);
    }  



  }

