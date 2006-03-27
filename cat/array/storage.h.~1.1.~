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
#ifndef STORAGE_H
#define STORAGE_H

#include "tvector.h"
#include <string>

using namespace std;

namespace cat
{

template <int D>
class storage
  {
  protected:

    tvector<int,D> ordering_;

    tvector<int,D> shape_;
    int size_;
    tvector<int,D> stride_;


    //Direct accessors to members
  public:

    //ordering
    tvector<int,D> & ordering();
    const tvector<int,D> & ordering() const;

    //shape
    tvector<int,D> & shape();
    const tvector<int,D> & shape() const;

    //size
    int & size();
    const int & size() const;

    //stride
    tvector<int,D> & stride();
    const tvector<int,D> & stride() const;


// Constructors / Destructor
  public:

    //Constructors
    explicit storage(const tvector<int,D> & shape__);//default - initialises storage_order_ with the c order (row major)
    explicit storage(const tvector<int,D> & shape__,string ordering_string__);//from string - fortran or c orders
    explicit storage(const tvector<int,D> & shape__,tvector<int,D> ordering__);//from tvector with order
    explicit storage(const tvector<int,D> & shape__,tvector<int,D> ordering__,tvector<int,D> stride__);
    //Destructor
    ~storage(){};
    
  
  //Forbidden Methods
  private:
    storage();//forbids default constructor
    //storage(const storage &);//forbids copy

    
    //Private Methods
  private:
    //Evaluates size
    int eval_size(const tvector<int,D> & shape__);
    tvector<int,D> eval_strides(const tvector<int,D> & shape__);

    
  };

}

#include "storage.C"

#endif
