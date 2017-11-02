// -*- C++ -*-
#ifndef ROTORS_H
#define ROTORS_H
#include <vector>
#include "sm.h"


class Rotor: public SM{
private:
  std::vector<int> mapping, inverse_mapping, notches;
  bool inverse;
public:
  // Constructors
  Rotor(char* mapping_config);
  
  // Copy Constructor
  
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
protected:
  std::vector<SM*> sm_ptrs;
  
public:
  // Constructor
  Cascade(SM** sm_ptrs,int num_ptrs);
  Cascade(std::vector<SM*> sm_ptrs);

  // Methods
  //virtual void set_state(int new_state);
  virtual int step(int inp);
};




class Reflector: public SM{
private:
  std::vector<int> mapping;
  
public:
  // Constructors
  Reflector(char* mapping_config);  
  // Methods
  virtual int step(int inp);
};



#endif
