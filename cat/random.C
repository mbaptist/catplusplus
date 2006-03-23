 
#include "random.h"

#include <ctime>
#include <iostream>
using namespace std;

namespace cat
{

  random_generator::random_generator()
  {
    reinit();
  }

  random_generator::random_generator(int seed)
  {
    reinit(seed);
  }

  random_generator::~random_generator()
  {
  }

  void random_generator::reinit()
  {
    srand(time(0));
    heat();
  }

  void random_generator::reinit(const int & seed)
  {
    srand(seed);
    heat();
  }

  void random_generator::heat()
  {
    const int nit_heat(100000);
    for(int i=0;i<nit_heat;++i)
      rand();
  } 

  double random_generator::operator()()
  {
    return double(double(rand())/RAND_MAX);
  }

  double random_generator::operator()(const double & a,const double & b)
  {
    return double(a+(b-a)*double(rand())/RAND_MAX);
  }


}
