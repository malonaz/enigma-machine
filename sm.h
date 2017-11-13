// -*- C++ -*-
#ifndef SM_H
#define SM_H
#include "errors.h"

// Messages definitions
#define NO_MSG 001


/**
 * internal helper function which, given an ascii character in the range [A-Z],
 * returns the corresponding integer in the range [0-25].
 */
int convert_char(char c);


/**
 * internal helper function which, given an integer in the range [0,25],
 * returns the corresponding ascii character in the range [A-Z]. 
 */
char convert_int(int c);


/**
 * Instruction. This struct is used as input and 
 * output for state machines. 
 */
struct Instruction{
public:
  int value; 
  int message; // used to pass messages between SMs.
  
  // Constructors
  Instruction(int val,int msg = NO_MSG):value(val), message(msg){}
};

/**
 * StateMachine. This abstract class represents state machines.
 * Look at methods below.
 */
class StateMachine{
protected:
  int state; // to be removed at some point
public:

  // DESTRUCTOR
  virtual ~StateMachine(){};
  
  // METHODS
  
  /**
   * Method which, in a loop, takes in input, and gets the machine to take a step,
   * printing the value of each step's instruction output to the standard output stream.
   * Set optional param debug to true if you wish to see how the step was taken.
   */
  void run(bool debug = false);

  /**
   * Virtual method which, given an Instruction, returns an Instruction
   * Set optional param debug to true if you wish to see how the step was taken.
   */
  virtual Instruction step(Instruction instr,bool debug = false); 
};

#endif 
