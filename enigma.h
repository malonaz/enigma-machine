// -*- C++ -*-
#ifndef ENIGMA_H
#define ENIGMA_H

#include "stateMachine.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotors.h"
#include "errors.h"

#include <ostream>


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
  Rotor** rotor_ptrs;
  int num_rotors;

public:
  /**
   * Constructor which given argument number and 
   * an argument array, with at least 2 arguments, 
   * constructs an enigma machine.
   */
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
   * internal helper method which:
   * - rotates the first rotor to be traversed by the machine. 
   * - for each rotor in order of their traversal
   *   from the plugboard to reflector:
   *    > if a notch is engaged, rotates the next rotor
   *      if there is one
   */
  void processRotorRotations();



  /**
   * Static method which given an array of arguments, 
   * checks whether they can be passed to
   * the Enigma constructor, by checking each argument
   * against its respective class's checkArg function.
   * returns the first error encountered.
   */
  static Error checkArgs(int num_configs, char** configs);


  /**
   * Method which tries to open a given rotor config
   * filepath and:
   * - returns appropriate error if 
   *   > encounters an error opening the file
   *   > one of the integers in the file is not in
   *     the range [0, 25]
   *   > there is a non-numeric character in the file
   *   > the number of integers in the file is not equal to
         the given number of rotors
   * - else returns a NO_ERROR error.
   */
  static Error checkRotorPos(char* config, int num_rotors);


  /**
   * Method which opens the given filepath
   * and:
   * -  sets the ith leftmost rotor's offset 
   *    to the ith integer it reads from the file
   */
  void setRotorPos(char* config);
  

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
  Error run(std::istream &input_stream = std::cin,
	    std::ostream &output_stream = std::cout,
	    std::ostream &error_stream = std::cerr,
	    bool debug = false);

};

#endif
