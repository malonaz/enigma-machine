// -*- C++ -*-
#ifndef ENIGMA_H
#define ENGIGMA_H

#include <iostream>
#include "../include/rotors.h"

class EnigmaMachine: public Cascade{
private:
  Plugboard* plugboard;
  Disk* entry_disk;
  Reflector* reflector;
  Cascade* rotor_cascade;

public:
  // Constructors
  EnigmaMachine(int argc, char** argv);
  
};


#endif
