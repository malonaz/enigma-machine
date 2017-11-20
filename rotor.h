// -*- C++ -*-
#ifndef ROTORS_H
#define ROTORS_H

#include "stateMachine.h"
#include "helpers.h"
#include "errors.h"
#include <vector>

/**
 * Rotor. This class simulates the Enigma rotors.
 * - The current rotation of the rotor is represented by 
 *   an offset field, always in the range [0,25]. 
 * - The mapping of the rotor is represented by two vectors of
 *   integers.
 * - its notches are represented by a vector of integers.
 * - lastly, the inverse field keeps track of which way the 
 *   rotor is being traversed.
 */
class Rotor: public StateMachine{
private:
  std::vector<int> mapping, inverse_mapping, notches;
  int offset; 
  bool inverse;

public:

  /**
   * Constructor which opens a configuration file at the given path and:
   * - Initiates mapping,inverse & notches to 26 all zeros.
   * - Initiates offset to 0 and inverse to false
   * - Opens the file and uses the first 26 integers to initiate
   *   the mapping and inverse mapping fields.
   * - for the 0 or more remaining integers, set notches to 1
   *   for these integers, to indicate a notch is present.
   */
  Rotor(char* config);

  /**
   * Method which sets offset to param offset.
   */
  void setOffset(int offset){this->offset = offset;}

  /**
   * Method which simulates a rotor rotation by
   * incrementing offset by 1, modulo 26, to reflect
   * circular nature of a rotor.
   */
  void rotate(){offset = mod26(offset+1);}

  /**
   * Method which returns true if rotor has a notch at the
   * current offset.
   * returns false otherwise.
   */
  bool notchEngaged(){return notches[offset];}
  
  /**
   * Method which takes an input and:
   * - applies offset to input.
   * - if inverse is false -> maps offset value with mapping
   * - if inverse if true -< maps offset value with inverse_mapping
   * - if inverse is true -> sets inverse to false & vice versa
   * - returns mapped value.
   * OPT - set debug to true to see how the step was taken
   */
  virtual int step(int input, bool debug = false);


  /**
   * Static method which opens a given filepath,
   * check whether it can safely be passed to the Rotor constructor
   * and returns an Error with filename config
   * filetype ROTOR and error code:
   * - INVALID_ROTOR_MAPPING: if the file attempts to map more than one
   *   input to the same output, or does not provide a mapping for some input
   * - INVALID_INDEX: if the file contains a number outside the range [0, 25]
   * - NON_NUMERIC_CHARACTER: if the file contains any characters other than 
   *   numeric characters.
   * - NO_ERROR: if none of the above occur
   * ! error codes are activated as the configuration file is read.
   */
  static Error checkArg(char* config);
  
};


#endif
