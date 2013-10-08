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

//memory_reference.h

#ifndef CAT_MEMORY_REFERENCE_H
#define CAT_MEMORY_REFERENCE_H

#include <cassert>

#include "memory_block.h"


  namespace cat
{

//declares class memory_reference
template <class T>
class memory_reference
  {

  private:
  
    //Private Members
    
    //Null block for use by the default constructor
    static null_memory_block<T> nullblock_;
    
    //Pointer to a memory block (it is allocated by the constructor by size)
    memory_block<T> * block_;

  protected:  
        
    //Pointer to first element of data
    T * data_;
    
    //size of the block of memory
    size_t length_;
    
  private:  
      
    //Private Methods
    
    void block_remove_reference();
    
  public:

    //Accessors to members
    
    memory_block<T> * block();
    const memory_block<T> * block() const; 
    
    T * data();
    const T * data() const;

    size_t & length();
    const size_t & length() const;
    
    //Constructors

    //default
    memory_reference();
    
    //constructor from reference to a memory block
    explicit memory_reference(memory_reference & ref);

  private:
    //     explicit memory_reference(const memory_reference & ref);
  public:


    //allocates a new memory block of size t and creates a reference to it  
    explicit memory_reference(const size_t & length__);

    //Create reference to existing data 
    explicit memory_reference(const size_t & length__, T * data__);
    
    //Destructor
    
    ~memory_reference();

    
    
    //void memory_block_resize(const size_t & length__);
    

    
    //Other accessors
    
    //references
    int & num_references();
    const int & num_references() const;

  };

}

#include "memory_reference.C"


#endif
