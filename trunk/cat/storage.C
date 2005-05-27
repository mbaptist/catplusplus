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

namespace cat
{

//Direct accessors to members

//ordering
template <int D>
tvector<int,D> & storage<D>::ordering()
{
  return ordering_;
};
template <int D>
const tvector<int,D> & storage<D>::ordering() const
  {
    return ordering_;
  };


//shape
template <int D>
tvector<int,D> & storage<D>::shape()
{
  return shape_;
};
template <int D>
const tvector<int,D> & storage<D>::shape() const
  {
    return shape_;
  };

//size
template <int D>
int & storage<D>::size()
{
  return size_;
};
template <int D>
const int & storage<D>::size() const
  {
    return size_;
  };

//stride
template <int D>
tvector<int,D> & storage<D>::stride()
{
  return stride_;
};
template <int D>
const tvector<int,D> & storage<D>::stride() const
  {
    return stride_;
  };




//Constructors (Note that destructor is virtual)


template <int D>
storage<D>::storage(const tvector<int,D> & shape__):
    shape_(shape__),
    size_(eval_size(shape_))
{
  for(int i=0;i<D;++i)
    ordering_[i]=D-i-1;
      stride_=eval_strides(shape_);
}



template <int D>
storage<D>::storage(const tvector<int,D> & shape__,string ordering_string__):
    shape_(shape__),
    size_(eval_size(shape_))
{
  if (ordering_string__==string("fortran")||ordering_string__==string("f"))
    for(int i=0;i<D;++i)
      ordering_[i]=i;
  else if (ordering_string__==string("c"))
    for(int i=0;i<D;++i)
      ordering_[i]=D-i-1;
  else
    {
      cout << "Undefined Storage Order " << ordering_string__ << " ! - aborting..." << endl;
      exit(1);
    }
  stride_=eval_strides(shape_);
}


template <int D>
storage<D>::storage(const tvector<int,D> & shape__,tvector<int,D> ordering__):
    ordering_(ordering__),
    shape_(shape__),
    size_(eval_size(shape_)),
    stride_(eval_strides(shape_))
{}

template <int D>
storage<D>::storage(const tvector<int,D> & shape__,tvector<int,D> ordering__,tvector<int,D> stride__):
    ordering_(ordering__),
    shape_(shape__),
    size_(eval_size(shape_)),
    stride_(stride__)
{

//   cout << stride_ << endl;
//   int lixo;
//   cin >> lixo;

}


//Private Methods

//Evaluates size
template <int D>
int storage<D>::eval_size(const tvector<int,D> & shape__)
{
  int size__=1;
  for(int i=0;i<D;++i)
    size__ *= shape__[i];
  return int(size__);
}


template <int D>
tvector<int,D> storage<D>::eval_strides(const tvector<int,D> & shape__)
{
  tvector<int,D> out;
  out[ordering_[0]]=1;
  for(int i=1;i<D;++i)    
    out[ordering_[i]]=shape__[ordering_[i-1]]*out[ordering_[i-1]];
    
//   out[0]=1;  
//   for(int i=1;i<D;++i)    
//     out[i]=shape__[i]*out[i-1];
    
//     cout << out << endl;
//     cout << endl;
//     int lixo;
//     cin >> lixo;
  
  return out;
  
}


}
