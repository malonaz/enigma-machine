// -*- C++ -*-
#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "stateMachine.h"
#include "helpers.h"
#include "errors.h"
#include <vector>


/**
 * Reflector. This class simulates the reflector of 
 * an Enigma Machine. 
 * - the mapping of the reflector is represented by 
 *   vector of 26 integers in the range [0,25].
 */
class Reflector: public StateMachine{
private:
  std::vector<int> mapping;
  
public:

  /**
   * Constructor which opens a configuration file at the given path and:
   * - uses the 13 pairs of integers to fill the mapping field such
   *   that for each pair (x,y), x maps to y and vice versa.
   */
  Reflector(char* config);  


  /**
   * Method which takes an input and:
   * - maps the input using mapping
   * - returns the mapped value
   * OPT - set debug to true to see how the step was taken
   */
  virtual int step(int input, bool debug = false);



  /**
   * Static method which opens a given filepath, 
   * and checks whether it could be passed to
   * the Reflector constructor. 
   * returns the first error encountered.
   */
  static Error invalidArg(char* config);

  
};

#endif
