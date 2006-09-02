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
  public:
		  static const int Rank=D;
    protected:
      T * data_;
      int length_;
      int pos_;
      tvector<int,D> stride_;
      int navstride_;
	    
	    cat::tvector<int,Rank> shape_;
	    cat::tvector<int,Rank> ordering_;
	    int size_;
	    
    public:
	    cat::tvector<int,Rank> & shape(){return shape_;};
	    const cat::tvector<int,Rank> & shape() const {return shape_;};
	    cat::tvector<int,Rank> & ordering(){return ordering_;};
	    const cat::tvector<int,Rank> & ordering() const {return ordering_;};
	    int & size(){return size_;};
	    const  int & size() const {return size_;};
	    

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
	    const_iterator(const array<T,D> & array__,int pos__);/*
	    //copy ctor
	    const_iterator(const const_iterator & rhs);*/

      //destructor
	    ~const_iterator();
  
    private:
	    const_iterator();
    public:

	    
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

	    using array<T,D>::const_iterator::shape_;
	    using array<T,D>::const_iterator::ordering_;
	    using array<T,D>::const_iterator::size_;
	    
    public:
	    static const int Rank=D;
	    
	    cat::tvector<int,Rank> & shape(){return shape_;};
	    const cat::tvector<int,Rank> & shape() const {return shape_;};
	    cat::tvector<int,Rank> & ordering(){return ordering_;};
	    const cat::tvector<int,Rank> & ordering() const {return ordering_;};
	    int & size(){return size_;};
	    const  int & size() const {return size_;};
	    
	    
      //constructor
      //from array
	    iterator(array<T,D> & array_);

	    //from array and position
	    iterator(array<T,D> & array__,int pos__);
	    //copy
	    //const_iterator(const const_iterator & rhs);

      //destructor
	    ~iterator();

	    
    private:
	    iterator();
    public:
	    
      T & operator*();

      T & operator->();

	    bool operator==(const const_iterator & rhs);
  
	    bool operator!=(const const_iterator & rhs);
    
	    iterator & operator=(const const_iterator & rhs);
	    
	    bool operator==(const iterator & rhs);
	    
	    bool operator!=(const iterator & rhs);
	    
	    iterator & operator=(const iterator & rhs);
	    
    };


  }


#include "array_iterator.C"


#endif
