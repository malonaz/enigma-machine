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
   * Method which takes an input in the range [0,25]
   * - maps the input using mapping
   * - returns the mapped value
   *  OPT - set param debug to true to see how the step was taken.
   */  
  virtual int step(int input, bool debug = false);


   /**
   * Static method which opens a given filepath,
   * check whether it can safely be passed to the Plugboard constructor
   * and returns an Error with filename config
   * filetype PLUGBOARD and error code:
   * - IMPOSSIBLE_PLUGBOARD_CONFIGURATION: if the file 
   *   attempts to connect a contact with itself, or with more than
   *   one other contact.
   * - INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS: if the file 
   *   contains an odd number of number.
   * - INVALID_INDEX: if the file contains a number outside the range [0, 25]
   * - NON_NUMERIC_CHARACTER: if the file contains any characters other than 
   *   numeric characters.
   * - NO_ERROR: if none of the above occur
   * ! error codes are activated as the configuration file is read.
   */
  static Error checkArg(char* config);

  
};


#endif

  
