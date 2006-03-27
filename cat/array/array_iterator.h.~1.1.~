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

  //array_iterator.h


#ifndef CAT_ARRAY_ITERATOR
#define CAT_ARRAY_ITERATOR

#include "tvector.h"
#include "tvector_ops.h"

  namespace cat
  {


    //Forwarding declaration of class array<T,D>
    template <class T,int D>
    class array;
  
    //Forwarding declaration of class tvector<T,N>
    template <class T,int N>
    class tvector;


    template <class T,int D> 
    class array_const_iterator
    {
    protected:
      T * data_;
      int length_;
      int pos_;
      tvector<int,D> stride_;
      int navstride_;
    public:
  
      T * data();  
      const T * data() const;
  
      //tvector<int,D> & indexes();
      //const tvector<int,D> & indexes() const;
  
      int & pos();  
      const int & pos() const;

      tvector<int,D> & stride();  
      const tvector<int,D> & stride() const;

      int & navstride();  
      const int & navstride() const;
  
      //Return the inces of the current position
      const tvector<int,D> indices() const;

      //constructor
      //from array
      array_const_iterator(const array<T,D> & array__);
      //from array and position
      array_const_iterator(const array<T,D> & array__,int pos__);

      //destructor
      ~array_const_iterator();
  
      const T & operator*() const;
  
      const T & operator->() const;

  
      array_const_iterator & operator++();

      array_const_iterator & operator--();

      bool operator==(const array_const_iterator & rhs);
  
  
      bool operator!=(const array_const_iterator & rhs);
    
  
      array_const_iterator & operator=(const array_const_iterator & rhs);
  
    
    };



    template <class T,int D> 
    class array_iterator: public array_const_iterator<T,D>
    {

      using array_const_iterator<T,D>::data_;
      using array_const_iterator<T,D>::length_;
      using array_const_iterator<T,D>::pos_;

    public:
    
      //constructor
      //from array
      array_iterator(array<T,D> & array_);

      //destructor
      ~array_iterator();

  
      T & operator*();

      T & operator->();

      bool operator==(const array_const_iterator<T,D> & rhs);
  
  
      bool operator!=(const array_const_iterator<T,D> & rhs);
    
  
      array_iterator & operator=(const array_const_iterator<T,D> & rhs);  

    };


  }


#include "array_iterator.C"


#endif
