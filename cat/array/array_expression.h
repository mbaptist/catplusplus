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

#ifndef ARRAY_EXPRESSION_H
#define ARRAY_EXPRESSION_H

template <class T1,class T2,int SelectT1 >
struct SelectByRank2
{
	typedef T1 selectedT;
	static T1 iter(const T1 & iter1__, const T2 & iter2__){return iter1__;};
};
template <class T1,class T2>
struct SelectByRank2<T1,T2,0>
{
	typedef T2 selectedT;
	static T2 iter(const T1 & iter1__, const T2 & iter2__){return iter2__;};
};
template <class T1,class T2>
struct SelectByRank
{
enum {selectT1 = (T1::Rank > T2::Rank ? 1 : 0)};
typedef typename SelectByRank2<T1,T2,selectT1>::selectedT selectedT;
	static selectedT iter(const T1 & iter1__, const T2 & iter2__)
	{return SelectByRank2<T1,T2,selectT1>::iter(iter1__, iter2__);};
};

//Array expression wrapper class
template<class Expression>
class ArrayExpression 
{
public:
	typedef typename Expression::elementT elementT;
	static const int Rank=Expression::Rank;
private:
  //Members
  Expression iter_;
public:
  //Accessors
  Expression & iter(){return iter_;};
  const Expression & iter() const {return iter_;};
	
	cat::tvector<int,Rank> & shape(){return iter_.shape();};
	const cat::tvector<int,Rank> & shape() const {return iter_.shape();};
	cat::tvector<int,Rank> & ordering(){return iter_.ordering();};
	const cat::tvector<int,Rank> & ordering() const {return iter_.ordering();};
	int & size(){return iter_.size();};
	const  int & size() const {return iter_.size();};

//Ctor from expresion
  ArrayExpression(const Expression & expression): 
    iter_(expression)
  { 
  };
  //Copy ctor
  ArrayExpression(const ArrayExpression & rhs):
    iter_(rhs.iter())
  {
  };
  //Dtor
  ~ArrayExpression()
  {
  };
private:
  //Forbidden ctors
  ArrayExpression();//default ctor
public:
  //Public Methods
  elementT operator*() const
  { return *iter_; }
  //Increment expression operator
  //(increments array expression iterator)
  void operator++()
  { ++iter_; }
};

//Array Expression for unary operators
template <class Op,class T>
class ArrayExpressionUnaryOp
{
public:
	typedef typename Op::returnT elementT;
	static const int Rank=T::Rank;
private:
  //Members
	T iter_;
	cat::tvector<int,Rank> shape_;
	cat::tvector<int,Rank> ordering_;
	int size_;
	
public:
  //Accessors
	T & iter(){return iter_;};
	const T & iter() const {return iter_;};
	
	cat::tvector<int,Rank> & shape(){return this->shape_;};
	const cat::tvector<int,Rank> & shape() const {return this->shape_;};
	cat::tvector<int,Rank> & ordering(){return this->ordering_;};
	const cat::tvector<int,Rank> & ordering() const {return this->ordering_;};
	int & size(){return this->size_;};
	const  int & size() const {return this->size_;};
	
	
//Ctor from iterators
ArrayExpressionUnaryOp(const T & iter__):
	iter_(iter__),
		shape_(iter_.shape()),
		ordering_(iter_.ordering()),
		size_(iter_.size())
	{
	};
  //Copy ctor
ArrayExpressionUnaryOp(const ArrayExpressionUnaryOp & rhs):
	iter_(rhs.iter()),
		shape_(rhs.shape()),
		ordering_(rhs.ordering()),
		size_(rhs.size())
	{
	};
  //Dtor
	~ArrayExpressionUnaryOp(){};
private:
  //Forbidden ctors
	ArrayExpressionUnaryOp();//default ctor
public:
  //Public Methods
	elementT operator*() const
	{
		return Op::apply(*iter_); }
  //Increment expression operator
  //(increments array expression iterator)
	void operator++()
	{
		++iter_;
	}
};


//Array Expression for binary operators
template <class Op,class T1,class T2>
class ArrayExpressionBinOp
{
private:
	static const int Rank1=T1::Rank;
	static const int Rank2=T2::Rank;
 public:
	typedef typename Op::returnT elementT;
	static const int Rank=(Rank1 > Rank2 ? Rank1 : Rank2);
private:
  //Members
  T1 iter1_;
  T2 iter2_;
	cat::tvector<int,Rank> shape_;
	cat::tvector<int,Rank> ordering_;
	int size_;
	
public:
  //Accessors
  T1 & iter1(){return iter1_;};
  T2 & iter2(){return iter2_;};
  const T1 & iter1() const {return iter1_;};
  const T2 & iter2() const {return iter2_;};


	
	cat::tvector<int,Rank> & shape(){return this->shape_;};
	const cat::tvector<int,Rank> & shape() const {return this->shape_;};
	cat::tvector<int,Rank> & ordering(){return this->ordering_;};
	const cat::tvector<int,Rank> & ordering() const {return this->ordering_;};
	int & size(){return this->size_;};
	const  int & size() const {return this->size_;};


//Ctor from iterators
  ArrayExpressionBinOp(const T1 & iter1__,const T2 & iter2__):
    iter1_(iter1__),
    iter2_(iter2__),
		shape_(cat::tvector<int,Rank>(0)),
		ordering_(cat::tvector<int,Rank>(0)),
		size_(0)
  {
	  typename SelectByRank<T1,T2>::selectedT iter(SelectByRank<T1,T2>::iter(iter1__,iter2__));
	  this->shape_=iter.shape();
	  this->ordering_=iter.ordering();
	  this->size_=iter.size();
  };
  //Copy ctor
  ArrayExpressionBinOp(const ArrayExpressionBinOp & binop):
    iter1_(binop.iter1()),
    iter2_(binop.iter2()),
		                       shape_(binop.shape()),
		                       ordering_(binop.ordering()),
		                       size_(binop.size())
  {
  };
  //Dtor
  ~ArrayExpressionBinOp(){};
private:
  //Forbidden ctors
  ArrayExpressionBinOp();//default ctor
public:
  //Public Methods
  elementT operator*() const
  {
	  return Op::apply(*iter1_,*iter2_); }
  //Increment expression operator
  //(increments array expression iterator)
  void operator++()
  { 
    ++iter1_;
    ++iter2_;
  }
};


//Array Expression for constants
template <class T>
class ArrayExpressionConstant
{
public:
	typedef T elementT;
	static const int Rank=0;
private:
  //Members
	T iter_;
	cat::tvector<int,Rank> shape_;
	cat::tvector<int,Rank> ordering_;
	int size_;
	
public:
  //Accessors
	T & iter(){return iter_;};
	const T & iter() const {return iter_;};

	
	cat::tvector<int,Rank> & shape(){return this->shape_;};
	const cat::tvector<int,Rank> & shape() const {return this->shape_;};
	cat::tvector<int,Rank> & ordering(){return this->ordering_;};
	const cat::tvector<int,Rank> & ordering() const {return this->ordering_;};
	int & size(){return this->size_;};
	const  int & size() const {return this->size_;};
	

//Ctor from iterators
ArrayExpressionConstant(const T & iter__):
	iter_(iter__),
		shape_(cat::tvector<int,Rank>(0)),
		ordering_(cat::tvector<int,Rank>(0)),
		size_(0)
	{
	};
  //Copy ctor
ArrayExpressionConstant(const ArrayExpressionConstant & rhs):
	iter_(rhs.iter()),
		shape_(rhs.shape()),
		ordering_(rhs.ordering()),
		size_(rhs.size())
	{
	};
  //Dtor
	~ArrayExpressionConstant(){};
private:
  //Forbidden ctors
	ArrayExpressionConstant();//default ctor
public:
  //Public Methods
	elementT operator*() const
	{
		return iter_;
	}
  //Increment expression operator
  //(increments array expression iterator)
	void operator++()
	{
	}
};





#endif


