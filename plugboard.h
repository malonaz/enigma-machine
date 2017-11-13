// -*- C++ -*-
#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "stateMachine.h"
#include "helpers.h"
#include "errors.h"
#include <vector>


/**
 * Plugboard. This class simulates the plugboard of 
 * an Enigma Machine. 
 * - the mapping of the plugboard is represented by 
 *   a vector of 26 integers in the range [0,25].
 */
class Plugboard: public StateMachine{
private:
  std::vector<int> mapping;
  int error_code;
  
public:

  /**
   * Constructor which opens a configuration file at the given path and:
   * - initiates field mapping to 26 integers in the range [0,25] such 
   *   that each letter maps to itself
   * - for the 0 or more given pairs of integers, mutates the mapping
   *   field such that the first integer maps to the second and vice versa.
   */
  Plugboard(char* config);
  
  /**
   * Method which takes an input and:
   * - maps the input using mapping
   * - returns the mapped value
   *  OPT - set param debug to true to see how the step was taken.
   */  
  virtual int step(int input, bool debug = false);


  /**
   * Static method which opens a given filepath, 
   * and checks whether it could be passed to
   * the Plugboard constructor. 
   * returns the first error encountered.
   */
  static Error checkArg(char* config);
};


#endif

  
