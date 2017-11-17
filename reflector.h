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
   * check whether it can safely be passed to the Reflector constructor
   * and returns an Error with filename config
   * filetype REFLECTOR and error code:
   * - INVALID_REFLECTOR_MAPPING: if the file attempts to map
   *   an input to itself or pair each idnex with more than one other
   * - INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS: if the file does not 
   *   contain exactly 13 pairs of numbers
   * - INVALID_INDEX: if the file contains a number outside the range [0, 25]
   * - NON_NUMERIC_CHARACTER: if the file contains any characters other than 
   *   numeric characters.
   * - NO_ERROR: if none of the above occur
   * ! error codes are activated as the configuration file is read.
   */
  static Error checkArg(char* config);

  
};

#endif
