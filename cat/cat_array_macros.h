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


//Forward decalration of class cat_array
template <class T,int D>
class cat_array;

#include "cat_numeric.h"
#include "cat_multi.h"
#include "cat_promote.h"


#define CAT_DECLARE_FUNCTION(func) \
template <class T,int D> \
cat_array<T,D> func(const cat_array<T,D> & a) \
{ \
 cat_array<T,D> out(a); \
 cat_array_iterator<T,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<type,D> func(const cat_array<T,D> & a) \
{ \
 cat_array<type,D> out(a); \
 cat_array_iterator<type,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<typename cat_numeric_traits<T>::T_numeric,D> func(const cat_array<T,D> & a) \
{ \
 cat_array<typename cat_numeric_traits<T>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_numeric_traits<T>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<typename cat_real_numeric_traits<T>::T_numeric,D> func(const cat_array<T,D> & a) \
{ \
 cat_array<typename cat_real_numeric_traits<T>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_real_numeric_traits<T>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<T,D> func(const cat_array<T,D> & a,const cat_array<T1,D> & b) \
{ \
 cat_array<T,D> out(a); \
 cat_array_iterator<T,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
 cat_array_const_iterator<T1,D> b_iterator(b); \
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
cat_array<typename cat_promote_traits<T,T1>::T_promote,D> func(const cat_array<T,D> & a,const T1 & b) \
{ \
 cat_array<typename cat_promote_traits<T,T1>::T_promote,D> out(a); \
 cat_array_iterator<typename cat_promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<typename cat_promote_traits<T,T1>::T_promote,D> func(const T1 & a,const cat_array<T,D> & b) \
{ \
 cat_array<typename cat_promote_traits<T,T1>::T_promote,D> out(b); \
 cat_array_iterator<typename cat_promote_traits<T,T1>::T_promote,D> out_iterator(out); \
 cat_array_const_iterator<T,D> b_iterator(b); \
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
cat_array<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> func(const cat_array<T,D> & a,const T1 & b) \
{ \
 cat_array<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const cat_array<T,D> & b) \
{ \
 cat_array<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
 cat_array_iterator<typename cat_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> b_iterator(b); \
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
cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> func(const cat_array<T,D> & a,const T1 & b) \
{ \
 cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> a_iterator(a); \
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
cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> func(const T1 & a,const cat_array<T,D> & b) \
{ \
 cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out(b.shape()); \
 cat_array_iterator<typename cat_real_numeric_traits<typename cat_promote_traits<T,T1>::T_promote>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T,D> b_iterator(b); \
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
cat_array<type,D> func(const cat_array<T1,D> & a,const cat_array<T,D> & b) \
{ \
 cat_array<type,D> out(a); \
 cat_array_iterator<type,D> out_iterator(out); \
 cat_array_const_iterator<T1,D> a_iterator(a); \
 cat_array_const_iterator<T,D> b_iterator(b); \
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
cat_array<typename cat_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D> func(const cat_array<T1,D> & a,const cat_array<T2,D> & b) \
{ \
 cat_array<typename cat_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T1,D> a_iterator(a); \
 cat_array_const_iterator<T2,D> b_iterator(b); \
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
cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> func(const cat_array<T1,D> & a,const cat_array<T2,D> & b) \
{ \
 cat_array<typename cat_real_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> out(a.shape()); \
 cat_array_iterator<typename cat_real_numeric_traits<typename cat_promote_traits<T1,T2>::T_promote>::T_numeric,D>::T_numeric,D> out_iterator(out); \
 cat_array_const_iterator<T1,D> a_iterator(a); \
 cat_array_const_iterator<T2,D> b_iterator(b); \
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
cat_array<typename cat_promote_traits<T1,T2>::T_promote,D> func(const cat_array<T1,D> & a,const cat_array<T2,D> & b) \
{ \
 cat_array<typename cat_promote_traits<T1,T2>::T_promote,D> out(a.shape()); \
 cat_array_iterator<typename cat_promote_traits<T1,T2>::T_promote,D> out_iterator(out); \
 cat_array_const_iterator<T1,D> a_iterator(a); \
 cat_array_const_iterator<T2,D> b_iterator(b); \
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

















#endif
