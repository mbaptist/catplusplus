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

  //array_iterator.C

#include "arrayclass.h"

#include "../tiny/tiny.h"

#include <cassert>

using namespace std;

namespace cat
{

    //// CONSTANT ITERATOR

template <class T,int D>
	T * Array<T,D>::const_iterator::data()
{
	return data_;
}

template <class T,int D>
	const T * Array<T,D>::const_iterator::data() const
{
	return data_;
}

    //Tvector<int,D> & indexes(){return indexes_;};
    //const Tvector<int,D> & indexes() const {return indexes_;};

template <class T,int D>
	int & Array<T,D>::const_iterator::pos()
{
	return pos_;
}
template <class T,int D>
	const int & Array<T,D>::const_iterator::pos() const
{
	return pos_;
}

template <class T,int D>
	Tvector<int,D> & Array<T,D>::const_iterator::stride()
{
	return stride_;
}
template <class T,int D>
	const Tvector<int,D> & Array<T,D>::const_iterator::stride() const
{
	return stride_;
}

template <class T,int D>
	int & Array<T,D>::const_iterator::navstride()
{
	return navstride_;
}
template <class T,int D>
	const int & Array<T,D>::const_iterator::navstride() const
{
	return navstride_;
}

    //constructor
    //from Array
template <class T,int D>
	Array<T,D>::const_iterator::const_iterator(const Array<T,D> & array__):
	data_(const_cast<T *>(array__.data())),
	length_(array__.length()),
	stride_(array__.stride()),
	navstride_(stride_[array__.ordering()[0]]),
	shape_(array__.shape()),
	ordering_(array__.ordering()),
	size_(array__.size())
{
	//cout << 	shape_ << ordering_ << size_ << endl;
}
    //from Array and position
template <class T,int D>
	Array<T,D>::const_iterator::const_iterator(const Array<T,D> & array__,
	                                           int pos__):
	data_(const_cast<T *>(array__.data())),
	length_(array__.length()),
	pos_(pos__),
	stride_(array__.stride()),
	navstride_(stride_[array__.ordering()[0]]),
	shape_(array__.shape()),
	ordering_(array__.ordering()),
	size_(array__.size())
{
	//cout << 	shape_ << ordering_ << size_ << endl;
}

// //copy ctor
// const_iterator(const const_iterator & rhs):
// data_(0),
// 	length_(array__.length()),
// 	pos_(pos__),
// 	stride_(array__.stride()),
// 	navstride_(stride_[array__.ordering()[0]])
// {
// }


	
    //destructor
template <class T,int D>
	Array<T,D>::const_iterator::~const_iterator()
{
}

template <class T,int D>
	const T & Array<T,D>::const_iterator::operator*() const
{
	assert((pos_>-1)&&(pos_<length_));
	return data_[pos_];
}

template <class T,int D>
	const T & Array<T,D>::const_iterator::operator->() const
{
	assert((pos_>-1)&&(pos_<length_));
	return data_[pos_];
}


template <class T,int D>
	typename Array<T,D>::const_iterator & Array<T,D>::const_iterator::operator++()
{
	this->pos_+=this->navstride_;
	return (*this);
}

template <class T,int D>
	typename Array<T,D>::const_iterator & Array<T,D>::const_iterator::operator--()
{
	this->pos_-=this->navstride_;
	return (*this);
}

template <class T,int D>
	bool Array<T,D>::const_iterator::operator==(const Array<T,D>::const_iterator & rhs)
{
	return bool((this->pos_)==(rhs.pos()));
}


template <class T,int D>
	bool Array<T,D>::const_iterator::operator!=(const Array<T,D>::const_iterator & rhs)
{
	return bool((this->pos_)!=(rhs.pos()));
}


template <class T,int D>
	typename Array<T,D>::const_iterator & Array<T,D>::const_iterator::operator=(const Array<T,D>::const_iterator & rhs)
{
	this->pos_=rhs.pos();
	this->stride_=rhs.stride();
	this->navstride_=rhs.navstride();
	return (*this);
}

template <class T,int D>
	const Tvector<int,D> Array<T,D>::const_iterator::indices() const
{
	Tvector<int,D> out;
	out[0]=this->pos()/this->stride()[0];
	int mod=this->pos()%this->stride()[0];
	for (int i=1;i<D;++i)
	{
		out[i]=mod/this->stride()[i];
		mod=mod%this->stride()[i];
	}
	return out;
}



    //// ITERATOR


template <class T,int D>
	Array<T,D>::iterator::iterator(Array<T,D> & array_):
	Array<T,D>::const_iterator(array_)
{
}
 //from Array and position
template <class T,int D>
	Array<T,D>::iterator::iterator(Array<T,D> & array__,
	                                           int pos__):
	Array<T,D>::const_iterator(array__,pos__)
{
}


    //destructor
template <class T,int D>
	Array<T,D>::iterator::~iterator()
{
}


template <class T,int D>
	T & Array<T,D>::iterator::operator*()
{
	assert((pos_>-1)&&(pos_<length_));
	return data_[pos_];
}

template <class T,int D>
	T & Array<T,D>::iterator::operator->()
{
	assert((pos_>-1)&&(pos_<length_));
	return data_[pos_];
}

template <class T,int D>
	bool Array<T,D>::iterator::operator==(const Array<T,D>::const_iterator & rhs)
{
	return bool((this->pos_)==(rhs.pos()));
}


template <class T,int D>
	bool Array<T,D>::iterator::operator!=(const Array<T,D>::const_iterator & rhs)
{
	return bool((this->pos_)!=(rhs.pos()));
}


template <class T,int D>
	typename Array<T,D>::iterator & Array<T,D>::iterator::operator=(const Array<T,D>::const_iterator & rhs)
{
	this->pos_=rhs.pos();
	this->stride_=rhs.stride();
	this->navstride_=rhs.navstride();
	return (*this);
}

template <class T,int D>
	bool Array<T,D>::iterator::operator==(const Array<T,D>::iterator & rhs)
{
	return bool((this->pos_)==(rhs.pos()));
}


template <class T,int D>
	bool Array<T,D>::iterator::operator!=(const Array<T,D>::iterator & rhs)
{
	return bool((this->pos_)!=(rhs.pos()));
}


template <class T,int D>
	typename Array<T,D>::iterator & Array<T,D>::iterator::operator=(const Array<T,D>::iterator & rhs)
{
	this->pos_=rhs.pos();
	this->stride_=rhs.stride();
	this->navstride_=rhs.navstride();
	return (*this);
}

}
