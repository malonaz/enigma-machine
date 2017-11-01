// -*- C++ -*-
#ifndef SM_H
#define SM_H

class SM{
protected:
  int state;

public:
  // Constructor
  SM():state(-1){}
  // Methods
  virtual int step(int inp){return state;}
  virtual void set_state(int new_state){state = new_state;}
};

#endif 
