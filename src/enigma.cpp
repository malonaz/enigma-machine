#include "../include/enigma.h"



EnigmaMachine::EnigmaMachine(int argc, char** argv)
  :Cascade(){
  std::vector<SM*> sm_ptrs;
  Cascade(sm_ptrs);
}
