// -*- C++ -*-
#ifndef ENIGMA_H
#define ENGIGMA_H

#include <iostream>
#include "../include/rotors.h"


// min argc = 1 pb + 1 ref + 1 rot_pos = 3
#define MIN_ARGS 3


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
  
  // Static Methods
  static int check_args(int argc, char** argv);

  
};


#endif
