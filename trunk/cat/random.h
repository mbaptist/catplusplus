// -*- C++ -*-

#ifndef RANDOM_H
#define RANDOM_H


namespace cat
{

  class random_generator
  {
  public:
    //Constructors
    random_generator();//default (generates seed based on timer)
    random_generator(int seed);
    //Destructor
    ~random_generator();
    //Accessors
    double operator()();
    double operator()(const double & a,const double & b);	
    void reinit();
    void reinit(const int & seed);
  private:
    void heat();
    //Forbidden actions
    random_generator(const random_generator &);//forbid copy
  };

}

#endif
