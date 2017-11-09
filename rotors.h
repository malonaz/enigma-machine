// -*- C++ -*-
#ifndef ROTORS_H
#define ROTORS_H
#include <vector>
#include "sm.h"


// Instruction Messages definitions
#define ROTATE_NOW 003

/**
 * EntryDisk. This class simulates the Enigma machine
 * entry disk. 
 */
class EntryDisk: public StateMachine{
public:
  // METHODS
  
  /**
   * Method which, given an instruction with value x,
   * returns an instruction with value x and message ROTATE_NOW.
   * Set optional param debug to true if you wish to see how the step was taken.
   */
  virtual Instruction step(Instruction instr, bool debug = false);
};


/**
 * Rotor. This class simulates the Enigma rotors.
 * - The current rotation of the rotor is represented by 
 *   its offset field, always in the range [0,25]. 
 * - The mapping of the rotor is represented by two vectors of
 *   integers.
 * - its notches are represented by a vector of integers.
 * - lastly, the inverse variable keeps track of which way the 
 *   rotor is being traversed.
 */
class Rotor: public StateMachine{
private:
  int offset; 
  std::vector<int> mapping, inverse_mapping, notches;
  bool inverse;

public:
  // CONSTRUCTORS

  /**
   * Constructor which opens the file at the given path and:
   * - Initiates the offset to 0 and inverse to false
   * - Opens the file and uses the first 26 integers to initiate
   *   the mapping and inverse mapping fields.
   * - uses the 0 or more remaining integers to initiate the notches field.
   */
  Rotor(char* mapping_config);

  
  // METHODS

  /**
   * Method which sets this offset to the given offset.
   */
  void set_offset(int offset);

  /**
   * Method which simulates a rotor rotation by
   * incrementing offset by 1, modulo 26.
   */
  void rotate();

  /**
   * Method which returns true if rotor has a notch at the
   * current offset.
   * returns false otherwise.
   */
  bool notch_engaged();

  /**
   * Method which takes an Instruction and:
   * - if instruction message is ROTATE_NOW -> rotates this rotor.
   * - applies current offset to the instruction value.
   * - if inverse is false -> maps offset value with mapping
   * - if inverse if true -< maps offset value with inverse_mapping
   * - if inverse is true -> sets inverse to false & vice versa
   * - msg to be attached to instruction output is ROTATE_NOW if 
   *   reverse is false and there is a notch at the current_offset.
   *   otherwise, msg will be NO_MSG.
   * - returns an instruction with the mapped value and msg.
   */
  virtual Instruction step(Instruction instr, bool debug = false);

  /**
   * Static method which opens a given filepath, 
   * and checks whether it could be passed to
   * the rotor Constructor. If an error is encountered,
   * returns the appropriate error code. 
   * returns NO_ERROR otherwise.
   */
  static ErrorReport check_arg( char* arg);
  
  //Debugging Methods, to be removed !
  void print_attributes();
  void print_offset();
};

 /**
  * Cascade. This class represents a state machine made up of 
  * state machines connected in series together.
  * - The component state machines connected in series (cascaded)
  *   are represented by a vector of state machine pointers.
  */
class Cascade: public StateMachine{
protected:
  std::vector<StateMachine*> sm_ptrs;
  
public:
  // CONSTRUCTORS

  /**
   * Constructor which, given an array of StateMachine ptrs
   * adds them to the vector of state machine pointers.
   */
  Cascade(StateMachine** sm_ptrs,int num_ptrs);
  Cascade(){};

  // METHODS

  /**
   * Method which takes an instruction and:
   * - feeds it to the first StateMachine of
   *   the Cascade, to make it step once.
   * - takes the instruction output and feeds it 
   *   to the next StateMachine. Repeats this until
   *   the last StateMachine of the Cascade.
   * - returns the instruction output of the last StateMachine
   */
  virtual Instruction step(Instruction inp, bool debug = false);
};



/**
 * Plugboard. This class simulates the plugboard of 
 * an Enigma Machine. 
 * - the mapping of the plugboard is represented by 
 *   vector of 26 integers in the range [0,25].
 */
class Plugboard: public StateMachine{
private:
  std::vector<int> mapping;

public:
  // CONSTRUCTOR

  /**
   * Constructor which opens a file at a given path and:
   * - iniates field mapping to 26 integers in the range [0,25],
   *   such that each letter maps to itself
   * - for the 0 or more given pairs of integers, mutates the mapping
   *   field such that the first integer maps to the second and vice versa.
   */
  Plugboard(char* mapping_config);
  
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
   * the Plugboard constructor . If an error is encountered,
   * returns the appropriate error code. 
   * returns NO_ERROR otherwise.
   */
  static ErrorReport check_arg(char* arg);
};

#endif
