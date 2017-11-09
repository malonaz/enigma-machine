// -*- C++ -*-
#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "errors.h"
#include "sm.h"

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
  // CONSTRUCTOR

  /**
   * Constructor which opens the file at a givne path and:
   * - uses the 13 pairs of integers to instantiate 
   *   the mapping field.
   */
  Reflector(char* mapping_config);  


  // METHODS

  /**
   * Method which takes an instruction and:
   * - maps the instruction's value using mapping
   * - returns an instruction with the mapped value and NO_MSG
   */
  virtual Instruction step(Instruction inp, bool debug = false);

  
  /**
   * Static method which opens a file at a given path and: 
   * and checks whether it could be passed to
   * the Reflector constructor . If an error is encountered,
   * returns the appropriate error code. 
   * returns NO_ERROR otherwise.
   */
  static ErrorReport check_arg(char *arg);
};




#endif
