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
//Implements class cat_memory_reference


//Definition of static members of cat_memory_reference
template <class T>
cat_null_memory_block<T> cat_memory_reference<T>::nullblock_;


//Private methods

template <class T>
void cat_memory_reference<T>::block_remove_reference()
{
  //cout << "Removing Reference!" << endl;
  int refcount = block_ -> remove_reference();
  if ((refcount == 0) && (block_ != &nullblock_ ))
    {
      //cout << "   Removing Block!" << endl;
      delete block_;
    }
}


//Accessors to members

template <class T>
cat_memory_block<T> * cat_memory_reference<T>::block()
{
  return block_;
}
template <class T>
const cat_memory_block<T> * cat_memory_reference<T>::block() const
  {
    return block_;
  }

template <class T>
T * cat_memory_reference<T>::data()
{
  return data_;
}
template <class T>
const T * cat_memory_reference<T>::data() const
  {
    return data_;
  }


template <class T>
size_t & cat_memory_reference<T>::length()
{
  return length_;
}
template <class T>
const size_t & cat_memory_reference<T>::length() const
{
  return length_;
}



//Constructors

//default
template <class T>
cat_memory_reference<T>::cat_memory_reference():
    block_(&nullblock_)
{
  //cout << "Default reference constr" << endl;
  block_ -> add_reference();
};
  


//constructor from reference to a memory block
template <class T>
cat_memory_reference<T>::cat_memory_reference(cat_memory_reference<T> & ref):
    block_(ref.block()),
    data_(block_->data()),
    length_(block_->length_)
{
  //cout << "Const ref from ref" << endl;
  block_ -> add_reference();
};


//allocates a new memory block of size t and creates a reference to it
template <class T>
cat_memory_reference<T>::cat_memory_reference(const size_t & length__):
    block_(new cat_memory_block<T> (length__)),
    data_(block_->data()),
    length_(block_->length())
{
  //cout << "reference from size constr" << endl;
  block_ -> add_reference();
};



//Create reference to existing data 
template <class T>
cat_memory_reference<T>::cat_memory_reference(const size_t & length__, T * data__):
  block_(new cat_unowned_memory_block<T> (length__,data__)),
  data_(block_->data()),
  length_(block_->length())
{
  //cout << "reference to unowned block constr" << endl;
  block_ -> add_reference();
};


#if 0
    MemoryBlockReference(size_t length, T_type* data, 
        preexistingMemoryPolicy deletionPolicy)
    {
        // Create a memory block using already allocated memory. 

        // Note: if the deletionPolicy is duplicateData, this must
        // be handled by the leaf class.  In MemoryBlockReference,
        // this is treated as neverDeleteData; the leaf class (e.g. Array)
        // must duplicate the data.

        if ((deletionPolicy == neverDeleteData) 
          || (deletionPolicy == duplicateData))
            block_ = new UnownedMemoryBlock<T_type>(length, data);
        else if (deletionPolicy == deleteDataWhenDone)
            block_ = new MemoryBlock<T_type>(length, data);
        block_->addReference();

#ifdef BZ_DEBUG_LOG_ALLOCATIONS
    cout << "MemoryBlockReference: created MemoryBlock at "
         << ((void*)block_) << endl;
#endif

        data_ = data;
    }

#endif






//Destructor
template <class T>
cat_memory_reference<T>::~cat_memory_reference()
{
  block_remove_reference();
};


//Other accessors


//references
template <class T>
int & cat_memory_reference<T>::num_references()
{
  return this -> block_ -> cat_memory_reference<T>::num_references();
}
template <class T>
const int & cat_memory_reference<T>::num_references() const
  {
    return this -> block_ -> cat_memory_reference<T>::num_references();
  }

  
  
//   template <class T>
//   void cat_memory_reference<T>::cat_memory_block_resize(const size_t & length__)
//    {
//     block_ -> resize(length__);
//     length_=length__;   
//    }
    

