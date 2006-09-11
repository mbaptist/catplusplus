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

#ifndef TVECTOREXPRESSION_H
#define TVECTOREXPRESSION_H

//tvector expression wrapper class
template <class Expression> 
class tvectorExpression
{
private:
	Expression iter_;
public:
	Expression & iter(){return iter_;};
	const Expression & iter() const {return iter_;};
  //typedef Expr iterT;
	tvectorExprexpression(const Expression & expression)
		: iter_(expression)
	{ }
	
	tvectorExpression(const tvectorExpression & rhs)
		: iter_(rhs.iter())
	{ }
	
	double operator*() const
	{ return *iter_; }
	
	void operator++()
	{ ++iter_; }
};







#endif