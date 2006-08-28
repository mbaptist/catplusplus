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


//Wrapper array expression class
template<class Expression>
class ArrayExpression 
{          
private:
  //Members
  Expression iter_;  
public:
  //Accessors
  Expression & iter(){return iter_;};
  const Expression & iter() const {return iter_;};
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
  double operator*() const
  { return *iter_; }
  //Increment expression operator
  //(increments array expression iterator)
  void operator++()
  { ++iter_; }
};



//Array Expression for binary operators
template <class Op,class T1,class T2>
class ArrayExpressionBinOp
{
public:
  typedef typename Op::returnT returnT;
private:
  //Members
  T1 iter1_;
  T2 iter2_;
public:
  //Accessors
  T1 & iter1(){return iter1_;};
  T2 & iter2(){return iter2_;};
  const T1 & iter1() const {return iter1_;};
  const T2 & iter2() const {return iter2_;};
  //Ctor from iterators
  ArrayExpressionBinOp(const T1 & iter1__,const T2 & iter2__):
    iter1_(iter1__),
    iter2_(iter2__)
  {
  };
  //Copy ctor
  ArrayExpressionBinOp(const ArrayExpressionBinOp & binop):
    iter1_(binop.iter1()),
    iter2_(binop.iter2())
  {
  };
  //Dtor
  ~ArrayExpressionBinOp(){};
private:
  //Forbidden ctors
  ArrayExpressionBinOp();//default ctor
public:
  //Public Methods
  double operator*() const
  { return Op::apply(*iter1_,*iter2_); }
  //Increment expression operator
  //(increments array expression iterator)
  void operator++()
  { 
    ++iter1_;
    ++iter2_;
  }
};






#endif


