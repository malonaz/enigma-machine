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
   * and checks whether it could be passed to
   * the Rotor constructor. 
   * returns the first error encountered.
   */
  static Error invalidArg(char* config);
  
};


#endif
