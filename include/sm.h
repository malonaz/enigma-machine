// -*- C++ -*-
#ifndef SM_H
#define SM_H
#include <iostream>

int convert_char(char c);

char convert_int(int c);

class SM{
protected:
  int state;

public:
  // Constructor
  SM():state(-1){}

  // Methods
  void test();
  virtual int step(int inp){return state;}
  virtual void set_state(int new_state){}
  
};

#endif 
