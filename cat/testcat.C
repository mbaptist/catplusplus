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
//test_field.C

#include "cat.h"
//using namespace slate;

void test_cat_tvector();
void test_cat_array();
void test_cat_array_cat_tvector();
void test_cross();


int main()
{
   // test_cat_tvector();
   // test_cat_array();
   test_cat_array_cat_tvector();
   //test_cross();
  return 0;
}


void test_cat_tvector()
{
  cout << "Testing cat_tvector ..." << endl;
  cat_tvector<double,1> a(1);
  cat_tvector<double,3> d(1,2,3);
  cat_tvector<complex<double>,3> b(1,2,3),c(b);
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << dot_product(b,d) << endl;
  cout << norm_sq(d) << endl;
  cout << endl;
}

void test_cat_array()
{
  cout << "Testing cat_array ..." << endl;
  cat_array<double,3> a(2,2,2);
  a=5;
  cout << a << endl;
  
  cout << endl;
  cat_array<double,3> & b(a);
  cout << b << endl;
  cout << endl;

  b=1;
  cout << a << endl;
  cout << endl;
  cout << b << endl;
  cout << endl;
  

  cat_array<double,3> c(a);
  b=2;
  cout << a << endl;
  cout << endl;
  cout << b << endl;
  cout << endl;
  cout << c << endl;
  cout << endl;

 
  //cout << a.num_references() << endl;

  c+=a;

  cout << c << endl;
  cout << endl;


}

void test_cat_array_cat_tvector()
{

  cout << "Testing cat_array<cat_tvector> ..." << endl;

  cat_array<cat_tvector<double,3>,3> tt(2,2,2);

  tt=cat_tvector<double,3>(5,6,7);

  cout << tt << endl;
  cout << endl;
  
  
  cat_array<cat_tvector<complex<double>,3>,3> ttt(tt.shape());

  ttt=cat_tvector<complex<double>,3>(complex<double>(5,1));

  cout << norm_sq(ttt) << endl;

    
#if 1

  cout << "create from extract" << endl;

  cat_array<double,3> stt(tt[1]);
  
  cout << stt << endl;
  
  stt=1;

  cout << tt << endl;

  tt[1]=2;
  
  cout << stt << endl;

  cout << endl;
   
#endif

//testing copy constructor
 
 
 
 //cat_array<cat_tvector<double,3>,3> ooo(cat_tvector<int,3>(2,2,2),cat_tvector<double,3>(1,2,3));
 
 


//testing copy constructor
#if 0 
    cat_array<cat_tvector<double,3>,3> ooo(cat_tvector<int,3>(2,2,2),cat_tvector<double,3>(1,2,3));
    cout << ooo << endl;
    cat_array<cat_tvector<double,3>,3> ccc(ooo);
    cout << ccc << endl;
    ccc=cat_tvector<double,3>(4,5,6);
    cout << ccc << endl;
    cout << ooo << endl;
#endif    

//testing operators


  ttt=ttt+tt;

  cout << ttt << endl;
  
  
  
  cout << "cross r c tv " << cross_product(cat_tvector<double,3>(1,2,3),cat_tvector<complex<double>,3>(1,-2,3)) << endl;
  
  
  cat_array<cat_tvector<double,3>,3> vr(3,3,3);
  vr=cat_tvector<double,3>(1,2,3);
  cat_array<cat_tvector<complex<double>,3>,3> vc(3,3,3);
  vc=cat_tvector<complex<double>,3>(complex<double>(1,1),complex<double>(-2,-2),complex<double>(3,3));
  
  cout << "cross r c a " << cross_product(vr,vc) << endl;
  
  
  //testing reshape;
  #if 0
  ttt.reshape(cat_tvector<int,3>(1,1,1));
  
  ttt=1;
  
  cout << ttt << endl;
  
  ttt.reshape(cat_tvector<int,3>(3,3,2));
  
  ttt=2;
  
  cout << ttt << endl;
  #endif
  
}





void test_cross()
{
	int n1=64;
	int n2=n1;
	int n3=n2;

	cat_array<cat_tvector<double,3>,3> a(n1,n2,n3),b(n1,n2,n3),cross(n1,n2,n3),cross_e(n1,n2,n3);
	for (int i=0;i<n1;++i)
		for (int j=0;j<n2;++j)
			for (int k=0;k<n3;++k)
				{	
					a(i,j,k)=cat_tvector<int,3>(i+j,i+k,j+k);
					b(i,j,k)=cat_tvector<int,3>(i-j,k-j,k-i);
					cross_e(i,j,k)=cat_tvector<int,3>((i+k)*(k-i)-(j+k)*(k-j),
										(j+k)*(i-j)-(i+j)*(k-i),
										(i+j)*(k-j)-(i+k)*(i-j));
				}

	cross=cross_product(a,b);

	for (int i=0;i<n1;++i)
                for (int j=0;j<n2;++j)
                        for (int k=0;k<n3;++k)
                                if (norm_sq(cross(i,j,k)-cross_e(i,j,k))!=0)
					{
						cout << i << " " << j << " " << k << endl;
						cout << cross(i,j,k) << " " << cross_e(i,j,k) << endl; 
						cout << "Failed." << endl;
						exit(0);
					}

	cout << "Success!" << endl;


}
