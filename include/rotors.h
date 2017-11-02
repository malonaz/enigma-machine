// -*- C++ -*-
#ifndef ROTORS_H
#define ROTORS_H
#include <vector>
#include "sm.h"

// States definitions
#define NOTCH_ENGAGED 002

// Msg definitions
#define ROTATE_NOW 003

class Disk: public SM{
public:
  virtual bool notch_engaged(){return true;}
  virtual Instruction step(Instruction inp, bool debug = false);
};

class Rotor: public SM{
private:
  int offset;
  std::vector<int> mapping, inverse_mapping, notches;
  bool inverse;
public:
  // Constructors
  Rotor(char* mapping_config);
  
  // Methods
  void set_offset(int offset);
  void rotate();
  bool notch_engaged();
  virtual Instruction step(Instruction inp, bool debug = false);

  //Debugging Methods
  void print_attributes();
  void print_offset();
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
  virtual Instruction step(Instruction inp, bool debug = false);
};


class Reflector: public SM{
private:
  std::vector<int> mapping;
  
public:
  // Constructors
  Reflector(char* mapping_config);  
  // Methods
  virtual Instruction step(Instruction inp, bool debug = false);
};



#endif
