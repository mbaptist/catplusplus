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
#ifndef CAT_STORAGE_H
#define CAT_STORAGE_H

#include "cat_tvector.h"
#include <string>

using namespace std;

template <int D>
class cat_storage
  {
  protected:

    cat_tvector<int,D> ordering_;

    cat_tvector<int,D> shape_;
    int size_;
    cat_tvector<int,D> stride_;


    //Direct accessors to members
  public:

    //ordering
    cat_tvector<int,D> & ordering();
    const cat_tvector<int,D> & ordering() const;

    //shape
    cat_tvector<int,D> & shape();
    const cat_tvector<int,D> & shape() const;

    //size
    int & size();
    const int & size() const;

    //stride
    cat_tvector<int,D> & stride();
    const cat_tvector<int,D> & stride() const;


// Constructors / Destructor
  public:

    //Constructors
    cat_storage(const cat_tvector<int,D> & shape__);//default - initialises storage_order_ with the c order (row major)
    cat_storage(const cat_tvector<int,D> & shape__,string ordering_string__);//from string - fortran or c orders
    cat_storage(const cat_tvector<int,D> & shape__,cat_tvector<int,D> ordering__);//from cat_tvector with order
    cat_storage(const cat_tvector<int,D> & shape__,cat_tvector<int,D> ordering__,cat_tvector<int,D> stride__);
    //Destructor
    virtual ~cat_storage(){};
    
  
  //Forbidden Methods
  private:
    cat_storage();//forbids default constructor
    cat_storage(const cat_storage &);//forbids copy

    
    //Private Methods
  private:
    //Evaluates size
    int eval_size(const cat_tvector<int,D> & shape__);
    cat_tvector<int,D> eval_strides(const cat_tvector<int,D> & shape__);

    
  };

#include "cat_storage.C"

#endif
