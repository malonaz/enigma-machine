// -*- C++ -*-
#ifndef ENIGMA_H
#define ENGIGMA_H

#include <iostream>
#include "rotors.h"


// min argc = 1 pb + 1 ref = 2
#define MIN_ENIGMA_ARGS 2


class EnigmaMachine: public Cascade{
private:
  Plugboard *plugboard;
  Disk *entry_disk;
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
  int change_rotor_pos(char* config);
  bool testLab(bool debug = false);
  
  // Static Methods
  static int check_args(int argc, char** argv);

  
};


#endif
