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

//cat_memory_block.h
//Declares a referenced memory block class with reference counting
//The block is to be used by class cat_memory_reference (cat_memory_reference.h)

#ifndef CAT_MEMORY_BLOCK_H
#define CAT_MEMORY_BLOCK_H

#include <cassert>

#include "cat_multi.h"

//Forward decalration of cat_memory_reference
template <class T>
class cat_memory_reference;


//cat_memblock class
//Declares a referenced memory block.
//This class is no intended to be used directly,
//rather via class cat_memory_reference
template <class T>
class cat_memory_block
  {

    //forbid copy and assignement
  private:

    cat_memory_block(const cat_memory_block<T> &);

    void operator=(const cat_memory_block<T> &);

  private:

    //pointer of type T that will hold data when allocated or
    //associated with externally allocated data
    T * data_;

    //pointer that points to data unless the memory block is
    //associated with externally allocated data
    T * data_address_;

    //number of references existing to the block
    int references_;

    //Total size of the memory block
    size_t length_;

  public:

    //Accessors

    //pointer to data
    T * data();
    const T * data() const;

    //length
    size_t & length();
    const size_t & length() const;

    //references
    int & num_references();
    const int & num_references() const;


    //Constructors

    //default
    cat_memory_block();

    //from length
    cat_memory_block(size_t length__);

    //from length and pointer
    //data is unowned and hence will not be deallocated
    cat_memory_block(size_t length__, T * data__);

    //destructor
    virtual ~cat_memory_block();

    
    //void resize(size_t length__);
    

    //Other public methods

    //allocation
    void allocate(size_t length__);

    //deallocation
    void deallocate();

    //add reference
    void add_reference();

    //remove reference
    int remove_reference();


  };


//Unowned Memory Block
template<class T>
class cat_unowned_memory_block : public cat_memory_block<T> {
public:
    cat_unowned_memory_block(size_t length, T* data)
        : cat_memory_block<T>(length,data)
    {
    }

    virtual ~cat_unowned_memory_block()
    {
      //cout << "Destructing Unowned Block" << endl;
    }
};


//Declares a null memory block class
//to be used by the default constructor of cat_memory_reference<T>
template <class T>
class cat_null_memory_block : public cat_memory_block<T>
  {
  public:
    //constructor
    cat_null_memory_block();
    //destructor
    ~cat_null_memory_block();
  };


#include "cat_memory_block.C"



#endif
