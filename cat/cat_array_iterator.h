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

//cat_array_iterator.h


#ifndef CAT_ARRAY_ITERATOR
#define CAT_ARRAY_ITERATOR


//Forwarding declaration of class cat_array<T,D>
template <class T,int D>
class cat_array;

//Forwarding declaration of class cat_tvector<T,N>
template <class T,int N>
class cat_tvector;


template <class T,int D> 
class cat_array_const_iterator
{
protected:
  T * data_;
  int length_;
  int pos_;
  cat_tvector<int,D> stride_;
  int navstride_;
public:
  
  T * data(){return data_;};  
  const T * data() const {return data_;};
  
  //cat_tvector<int,D> & indexes(){return indexes_;};
  //const cat_tvector<int,D> & indexes() const {return indexes_;};
  
  int & pos(){return pos_;};  
  const int & pos() const {return pos_;};

  cat_tvector<int,D> & stride(){return stride_;};  
  const cat_tvector<int,D> & stride() const {return stride_;};

  int & navstride(){return navstride_;};  
  const int & navstride() const {return navstride_;};
  
  //constructor
  //from array
  cat_array_const_iterator(const cat_array<T,D> & array__):
    data_(const_cast<T *>(array__.data())),
    length_(array__.length()),
    stride_(array__.stride()),
    navstride_(stride_[array__.ordering()[0]])
  {
  };
  //from array and position
  cat_array_const_iterator(const cat_array<T,D> & array__,int pos__):
    data_(0),
    length_(array__.length()),
    pos_(pos__),
    stride_(array__.stride()),
    navstride_(stride_[array__.ordering()[0]])
  {
  };

  //destructor
  ~cat_array_const_iterator(){};
  
  const T & operator*() const 
  {
    assert((pos_>-1)&&(pos_<length_));
    return data_[pos_];
  };
  
  const T & operator->() const 
  {
    assert((pos_>-1)&&(pos_<length_));
    return data_[pos_];
  };

  
  cat_array_const_iterator & operator++()
  {
    this->pos_+=this->navstride_;
    return (*this);
  }

  cat_array_const_iterator & operator--()
  {
    this->pos_-=this->navstride_;
    return (*this);
  }

  bool operator==(const cat_array_const_iterator & rhs)
  {
    return bool((this->pos_)==(rhs.pos()));
  };
  
  
  bool operator!=(const cat_array_const_iterator & rhs)
  {
    return bool((this->pos_)!=(rhs.pos()));
  };
    
  
  cat_array_const_iterator & operator=(const cat_array_const_iterator & rhs)
  {
    this->pos_=rhs.pos();
    this->stride_=rhs.stride();
    this->navstride_=rhs.navstride();
    return (*this);
  };
  
    
};



template <class T,int D> 
class cat_array_iterator: public cat_array_const_iterator<T,D>
{

  using cat_array_const_iterator<T,D>::data_;
  using cat_array_const_iterator<T,D>::length_;
  using cat_array_const_iterator<T,D>::pos_;

public:
    
  //constructor
  //from array
  cat_array_iterator(cat_array<T,D> & array_):
    cat_array_const_iterator<T,D>(array_)
  {
  };

  //destructor
  ~cat_array_iterator(){};

  
  T & operator*()
  {
    assert((pos_>-1)&&(pos_<length_));
    return data_[pos_];
  };

  T & operator->()
  {
    assert((pos_>-1)&&(pos_<length_));
    return data_[pos_];
  };

  bool operator==(const cat_array_const_iterator<T,D> & rhs)
  {
    return bool((this->pos_)==(rhs.pos()));
  };
  
  
  bool operator!=(const cat_array_const_iterator<T,D> & rhs)
  {
    return bool((this->pos_)!=(rhs.pos()));
  };
    
  
  cat_array_iterator & operator=(const cat_array_const_iterator<T,D> & rhs)
  {
    this->pos_=rhs.pos();
    this->stride_=rhs.stride();
    this->navstride_=rhs.navstride();
    return (*this);
  };  

};




#endif