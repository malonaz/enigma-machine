// -*- C++ -*-
#ifndef ENIGMA_H
#define ENGIGMA_H

#include <iostream>
#include "rotors.h"
#include "reflector.h"

// min argc = 1 pb + 1 ref = 2
#define MIN_ENIGMA_ARGS 2


class EnigmaMachine: public Cascade{
private:
  Plugboard *plugboard;
  EntryDisk *entry_disk;
  Reflector *reflector;
  Rotor **rotors;
  int num_rotors;

public:
  // Constructors
  
  EnigmaMachine(int argc, char** argv);
  EnigmaMachine();

  // Destructor
   ~EnigmaMachine();

  // Methods
  ErrorReport change_rotor_pos(char* config);
  bool testLab(bool debug = false);
  bool transduce(const char* filename);
  
  // Static Methods
  static ErrorReport check_args(int argc, char** argv);

  
};


#endif
