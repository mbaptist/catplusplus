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

//cat_memory_block.C
//Implements a referenced memory block class with reference counting
//The block is to be used by class cat_memory_reference (cat_memory_reference.h)


//Accessors

//pointer to data
template <class T>
T * cat_memory_block<T>::data()
{
  return this -> data_;
}
template <class T>
const T * cat_memory_block<T>::data() const
  {
    return this -> data_;
  }


//length
template <class T>
size_t & cat_memory_block<T>::length()
{
  return this->length_;
}
template <class T>
const size_t & cat_memory_block<T>::length() const
{
  return this->length_;
}

//references
template <class T>
int & cat_memory_block<T>::num_references()
{
  return this -> references_;
}
template <class T>
const int & cat_memory_block<T>::num_references() const
  {
    return this -> references_;
  }



//Constructors

//default
template <class T>
cat_memory_block<T>::cat_memory_block():
    data_(0),
    data_address_(0),
    references_(0),
    length_(0)
{
  //cout << "MB default" << endl;
}


//from length
template <class T>
cat_memory_block<T>::cat_memory_block(size_t length__):
    references_(0),
    length_(length__)
{
  // cout << "slmr_cs pl: " << length__ << endl;
  
  allocate(length_);
  //cout << "MB length" << endl;
  assert(data_address_!=0);
}

//from length and pointer
//data is unowned and hence will not be deallocated
template <class T>
cat_memory_block<T>::cat_memory_block(size_t length__, T * data__):
    data_(data__),
    data_address_(0),
    references_(0),
    length_(length__)
{}


//destructor
template <class T>
cat_memory_block<T>::~cat_memory_block()
{
  if (data_address_)
    deallocate();
  //cout << "Destructing Block" << endl; 
}


// template <class T>
// void cat_memory_block<T>::resize(size_t length__)
// {
//   deallocate();
//   length_=length__;
//   allocate(length_);
// }

//Other public methods


//allocation
template <class T>
void cat_memory_block<T>::allocate(size_t length__)
{
  data_address_ = new T [length__];
  data_ = data_address_;
}

//deallocation
template <class T>
void cat_memory_block<T>::deallocate()
{
  delete [] data_address_;
}

//add reference
template <class T>
void cat_memory_block<T>::add_reference()
{
  ++references_;
}

//remove reference
template <class T>
int cat_memory_block<T>::remove_reference()
{
  return int(--references_);
}







//cat_null_memory_block<T> constructor
template <class T>
cat_null_memory_block<T>::cat_null_memory_block()
{
  cat_memory_block<T>::add_reference();
}

//cat_null_memory_block<T> destructor
template <class T>
cat_null_memory_block<T>::~cat_null_memory_block()
{
  //cout << "Destructing Null Block" << endl;
}



