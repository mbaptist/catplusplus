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

 
#ifndef CAT_ARRAY_MACROS_H
#define CAT_ARRAY_MACROS_H


#include "../traits/traits.h"


namespace cat
{

//Forward decalration of class Array
template <class T,int D>
class Array;

#define CAT_DECLARE_FUNCTION(func) \
template <class T,int D> \
Array<T,D> func(const Array<T,D> & a) \
{ \
 Array<T,D> out(a); \
 typename Array<T,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<type,D> func(const Array<T,D> & a) \
{ \
 Array<type,D> out(a); \
	typename Array<type,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<typename numeric_traits<T>::T_numeric,D> func(const Array<T,D> & a) \
{ \
 Array<typename numeric_traits<T>::T_numeric,D> out(a.shape()); \
	typename Array<typename numeric_traits<T>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<typename real_numeric_traits<T>::T_numeric,D> func(const Array<T,D> & a) \
{ \
 Array<typename real_numeric_traits<T>::T_numeric,D> out(a.shape()); \
	typename Array<typename real_numeric_traits<T>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<T,D> func(const Array<T,D> & a,const Array<T1,D> & b) \
{ \
 Array<T,D> out(a); \
 typename Array<T,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
 typename Array<T1,D>::const_iterator b_iterator(b); \
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
Array<typename promote_traits<T,T1>::T_promote,D> func(const Array<T,D> & a,const T1 & b) \
{ \
 Array<typename promote_traits<T,T1>::T_promote,D> out(a); \
	typename Array<typename promote_traits<T,T1>::T_promote,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<typename promote_traits<T,T1>::T_promote,D> func(const T1 & a,const Array<T,D> & b) \
{ \
 Array<typename promote_traits<T,T1>::T_promote,D> out(b); \
	typename Array<typename promote_traits<T,T1>::T_promote,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator b_iterator(b); \
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
Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const Array<T,D> & a,const T1 & b) \
{ \
 Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
	typename Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const Array<T,D> & b) \
{ \
 Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
	typename Array<typename numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator b_iterator(b); \
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
Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const Array<T,D> & a,const T1 & b) \
{ \
 Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
	typename Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator a_iterator(a); \
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
Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const Array<T,D> & b) \
{ \
 Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
	typename Array<typename real_numeric_traits<typename promote_traits<T,T1>::T_promote>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T,D>::const_iterator b_iterator(b); \
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
Array<type,D> func(const Array<T1,D> & a,const Array<T,D> & b) \
{ \
 Array<type,D> out(a); \
	typename Array<type,D>::iterator out_iterator(out); \
 typename Array<T1,D>::const_iterator a_iterator(a); \
 typename Array<T,D>::const_iterator b_iterator(b); \
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
Array<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D> func(const Array<T1,D> & a,const Array<T2,D> & b) \
{ \
 Array<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D> out(a.shape()); \
	typename Array<typename numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T1,D>::const_iterator a_iterator(a); \
 typename Array<T2,D>::const_iterator b_iterator(b); \
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
Array<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> func(const Array<T1,D> & a,const Array<T2,D> & b) \
{ \
 Array<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> out(a.shape()); \
	typename Array<typename real_numeric_traits<typename promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D>::iterator out_iterator(out); \
 typename Array<T1,D>::const_iterator a_iterator(a); \
 typename Array<T2,D>::const_iterator b_iterator(b); \
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
Array<typename promote_traits<T1,T2>::T_promote,D> func(const Array<T1,D> & a,const Array<T2,D> & b) \
{ \
 Array<typename promote_traits<T1,T2>::T_promote,D> out(a.shape()); \
	typename Array<typename promote_traits<T1,T2>::T_promote,D>::iterator out_iterator(out); \
 typename Array<T1,D>::const_iterator a_iterator(a); \
 typename Array<T2,D>::const_iterator b_iterator(b); \
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
