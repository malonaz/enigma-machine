// -*- C++ -*-
#ifndef SM_H
#define SM_H

#include "errors.h"

// SM states definition
#define IDLE 000

// Messages definitions
#define NO_MSG 001

int convert_char(char c);

char convert_int(int c);


struct Instruction{
public:
   int value;
   int message;

  // Constructors
    Instruction(int val,int msg):value(val), message(msg){}
};


class SM{
protected:
  int state;
public:
  // Constructor
  SM():state(IDLE){}

  // Destructor
  virtual ~SM(){};
  
  // Methods
  void test(bool debug = false);
  void run(bool debug = false);
  virtual Instruction step(Instruction inp,bool debug = false);
  
  
};

#endif 
