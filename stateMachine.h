// -*- C++ -*-
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "errors.h"

/**
 * StateMachine. This class represents state machines.
 */
class StateMachine{  
public:
  
  /** 
   * Destructor. Virtual so user can delete
   * StateMachine-derived objects through a base ptr.
   */
  virtual ~StateMachine() {}

  
  /**
   * Virtual method which, given an input, makes the machine step,  
   * then returns an output.
   * OPT - set param debug to true if you wish to see how the step was taken.
   */
  virtual int step(int input,bool debug = false);

};

#endif
  
