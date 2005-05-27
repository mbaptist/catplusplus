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

 
#ifndef CAT_ARRAY_MACROS_H
#define CAT_ARRAY_MACROS_H


#include "numeric.h"
#include "multi.h"
#include "promote.h"


namespace cat
{

//Forward decalration of class array
template <class T,int D>
class array;

#define CAT_DECLARE_FUNCTION(func) \
template <class T,int D> \
array<T,D> func(const array<T,D> & a) \
{ \
 array<T,D> out(a); \
 array_iterator<T,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator); \
 return out; \
}

#define CAT_DECLARE_FUNCTION_RET(type,func) \
template <class T1,class T,int D> \
array<type,D> func(const array<T,D> & a) \
{ \
 array<type,D> out(a); \
 array_iterator<type,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator); \
 return out; \
}


#define CAT_DECLARE_FUNCTION_NUMERIC(func) \
template <class T,int D> \
array<typename numeric_traits<T>::T_numeric,D> func(const array<T,D> & a) \
{ \
 array<typename numeric_traits<T>::T_numeric,D> out(a.shape()); \
 array_iterator<typename numeric_traits<T>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator); \
 return out; \
} 



#define CAT_DECLARE_FUNCTION_REAL_NUMERIC(func) \
template <class T,int D> \
array<typename real_numeric_traits<T>::T_numeric,D> func(const array<T,D> & a) \
{ \
 array<typename real_numeric_traits<T>::T_numeric,D> out(a.shape()); \
 array_iterator<typename real_numeric_traits<T>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator); \
 return out; \
} 






#define CAT_DECLARE_FUNCTION2(func) \
template <class T,class T1,int D> \
array<T,D> func(const array<T,D> & a,const array<T1,D> & b) \
{ \
 array<T,D> out(a); \
 array_iterator<T,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 array_const_iterator<T1,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(), \
	b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++a_iterator, \
        ++b_iterator) \
   *out_iterator=func(*a_iterator,*b_iterator); \
 return out; \
} 



// Elementary extensions

#define CAT_DECLARE_FUNCTION2_ELEMENT(func) \
template <class T,class T1,int D> \
array<typename promote_traits<T,T1>::T_promote,D> func(const array<T,D> & a,const T1 & b) \
{ \
 array<typename promote_traits<T,T1>::T_promote,D> out(a); \
 array_iterator<typename promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator,b); \
 return out; \
} \
template <class T,class T1,int D> \
array<typename promote_traits<T,T1>::T_promote,D> func(const T1 & a,const array<T,D> & b) \
{ \
 array<typename promote_traits<T,T1>::T_promote,D> out(b); \
 array_iterator<typename promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 array_const_iterator<T,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++b_iterator) \
   *out_iterator=func(a,*b_iterator); \
 return out; \
} 


#define CAT_DECLARE_FUNCTION2_ELEMENT_NUMERIC(func) \
template <class T,class T1,int D> \
array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const array<T,D> & a,const T1 & b) \
{ \
 array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
 array_iterator<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator,b); \
 return out; \
} \
template <class T,class T1,int D> \
array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const array<T,D> & b) \
{ \
 array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
 array_iterator<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++b_iterator) \
   *out_iterator=func(a,*b_iterator); \
 return out; \
} 


#define CAT_DECLARE_FUNCTION2_ELEMENT_REAL_NUMERIC(func) \
template <class T,class T1,int D> \
array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const array<T,D> & a,const T1 & b) \
{ \
 array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
 array_iterator<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> a_iterator(a); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(); \
      ++out_iterator, \
	++a_iterator) \
   *out_iterator=func(*a_iterator,b); \
 return out; \
} \
template <class T,class T1,int D> \
array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const array<T,D> & b) \
{ \
 array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
 array_iterator<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++b_iterator) \
   *out_iterator=func(a,*b_iterator); \
 return out; \
} 



#define CAT_DECLARE_FUNCTION2_RET(type,func) \
template <typename T1,typename T,int D> \
array<type,D> func(const array<T1,D> & a,const array<T,D> & b) \
{ \
 array<type,D> out(a); \
 array_iterator<type,D> out_iterator(out); \
 array_const_iterator<T1,D> a_iterator(a); \
 array_const_iterator<T,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(), \
	b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++a_iterator, \
        ++b_iterator) \
   *out_iterator=func(*a_iterator,*b_iterator); \
 return out; \
}


#define CAT_DECLARE_FUNCTION2_NUMERIC(func) \
template <class T1,class T2,int D> \
array<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D> func(const array<T1,D> & a,const array<T2,D> & b) \
{ \
 array<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D> out(a.shape()); \
 array_iterator<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T1,D> a_iterator(a); \
 array_const_iterator<T2,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(), \
	b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++a_iterator, \
        ++b_iterator) \
   *out_iterator=func(*a_iterator,*b_iterator); \
 return out; \
}



#define CAT_DECLARE_FUNCTION2_REAL_NUMERIC(func) \
template <class T1,class T2,int D> \
array<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> func(const array<T1,D> & a,const array<T2,D> & b) \
{ \
 array<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> out(a.shape()); \
 array_iterator<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> out_iterator(out); \
 array_const_iterator<T1,D> a_iterator(a); \
 array_const_iterator<T2,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(), \
	b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++a_iterator, \
        ++b_iterator) \
   *out_iterator=func(*a_iterator,*b_iterator); \
 return out; \
}




#define CAT_DECLARE_FUNCTION2_PROMOTE(func) \
template <class T1,class T2,int D> \
array<typename promote_traits<T1,T2>::T_promote,D> func(const array<T1,D> & a,const array<T2,D> & b) \
{ \
 array<typename promote_traits<T1,T2>::T_promote,D> out(a.shape()); \
 array_iterator<typename promote_traits<T1,T2>::T_promote,D> out_iterator(out); \
 array_const_iterator<T1,D> a_iterator(a); \
 array_const_iterator<T2,D> b_iterator(b); \
 for (out_iterator=out.begin(), \
        a_iterator=a.begin(), \
	b_iterator=b.begin(); \
      out_iterator!=out.end(), \
	a_iterator!=a.end(), \
	b_iterator!=b.end(); \
      ++out_iterator, \
	++a_iterator, \
        ++b_iterator) \
   *out_iterator=func(*a_iterator,*b_iterator); \
 return out; \
}









}







#endif
