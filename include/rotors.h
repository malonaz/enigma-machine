// -*- C++ -*-
#ifndef ROTORS_H
#define ROTORS_H
#include <vector>
#include "sm.h"


class Rotor: public SM{
private:
  std::vector<int> mapping, notches;
public:
  // Constructors
  Rotor(char* mapping_config);

  // Methods
  void set_state(int new_state);
  void rotate(){state = (state+1)%26;}
  bool notch_engaged();
  virtual int step(int inp);

  //Debugging Methods
  void print_attributes();
  void print_state();
};


class Cascade: public SM{
public:
  SM sm1;
  SM sm2;
  
public:
  // Constructor
  Cascade(SM &sm1, SM &sm2);

  // Methods
  virtual int step(int inp);
};


#endif
