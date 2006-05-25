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

#include "../tiny/tiny.h"

#include "arrayclass.h"

  namespace cat
  {


    //Forwarding declaration of class array<T,D>
  template <class T,int D>
	  class array;
  
    //Forwarding declaration of class tvector<T,N>
    template <class T,int N>
    class tvector;


    template <class T,int D> 
	  class array<T,D>::const_iterator
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
	    const_iterator(const array<T,D> & array__);
      //from array and position
	    const_iterator(const array<T,D> & array__,int pos__);

      //destructor
	    ~const_iterator();
  
      const T & operator*() const;
  
      const T & operator->() const;

  
	    const_iterator & operator++();

	    const_iterator & operator--();

	    bool operator==(const const_iterator & rhs);
  
  
	    bool operator!=(const const_iterator & rhs);
    
  
	    const_iterator & operator=(const const_iterator & rhs);
  
    
    };



    template <class T,int D> 
	  class array<T,D>::iterator: public array<T,D>::const_iterator
    {

	    using array<T,D>::const_iterator::data_;
	    using array<T,D>::const_iterator::length_;
	    using array<T,D>::const_iterator::pos_;

    public:
    
      //constructor
      //from array
	    iterator(array<T,D> & array_);

      //destructor
	    ~iterator();

  
      T & operator*();

      T & operator->();

	    bool operator==(const const_iterator & rhs);
  
  
	    bool operator!=(const const_iterator & rhs);
    
  
	    iterator & operator=(const const_iterator & rhs);

    };


  }


#include "array_iterator.C"


#endif
