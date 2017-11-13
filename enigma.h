// -*- C++ -*-
#ifndef ENIGMA_H
#define ENIGMA_H

#include "stateMachine.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotors.h"
#include "errors.h"

#define MIN_ENIGMA_ARGS 2


/**
 * EnigmaMachine. This class represents an enigma machine.
 * It contains at least two components: one plugboard and one
 * reflector. 
 */
class EnigmaMachine: public StateMachine{
private:
  Plugboard* plugboard_ptr;
  Reflector* reflector_ptr;
  Rotor** rotors_ptrs;
  int num_rotors;

public:
  EnigmaMachine(int argc, char** argv);

  /**
   * Destructor which overrides base class destructor.
   * It disallocates stateMachine components of enigma.
   */
  ~EnigmaMachine();



  /**
   * Method which takes an input and:
   * - feeds it to the enigma machine to make it 
   *   step once then returns the output.
   */
  virtual int step(int input, bool debug = false);

  
  /**
   * internal helper method which given the index of 
   * a rotor ptr in rotor_ptrs:
   * - rotates the rotor if it is the first rotor
   *   to be traversed by the machine. 
   * - rotates the next rotor to be traversed by the
   *   machine if the given rotor's notch is engaged
   */
  void processRotorRotations(int rotor_index);

  /**
   * Method which, in a loop, takes input from the standard input
   * stream and:
   * - if an input is not an uppercase letter in the range [A-Z],
   *   it returns an Error with code INVALID_INDEX.
   * - else, gets the EnigmaMachine to take a step,
   *   printing the value of each step's output to the standard output stream.
   * - when standard input stream is closed, returns an Error with code NO_ERROR
   * OPT - set param debug to true if you wish to see how each step was taken.
   */
  Error run(bool debug = false);

  
  /**
   * Static method which given an array of arguments, 
   * checks whether they can be passed to
   * the Enigma constructor. 
   * returns the first error encountered.
   */
  static Error checkArgs(int num_configs, char** configs);
    
};


#endif
