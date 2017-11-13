// -*- C++ -*-
#include "enigma.h"
#include "helpers.h"
#include "errors.h"
#include <iostream>


EnigmaMachine::EnigmaMachine(int argc, char** argv)
  :  num_rotors(0) {
  
  plugboard_ptr = new Plugboard(*argv++);
  reflector_ptr = new Reflector(*argv++);

  if(argc > MIN_ENIGMA_ARGS){
    num_rotors = argc - MIN_ENIGMA_ARGS -1;
    rotors_ptrs = new Rotor*[num_rotors];
   
    for (int i = 0; i < num_rotors; i++)
      rotors_ptrs[i] = new Rotor(*argv++);
  }
}


EnigmaMachine::~EnigmaMachine(){
  delete plugboard_ptr;
  delete reflector_ptr;
  
  for (int i = 0; i < num_rotors; i++)
    delete rotors_ptrs[i];
  delete[] rotors_ptrs;
}

int EnigmaMachine::step(int input, bool debug){
  int current_output = input;

  current_output = plugboard_ptr->step(current_output, debug);

  for (int i = num_rotors -1; i >= 0; i--){
    processRotorRotations(i);
    current_output = rotors_ptrs[i]->step(current_output, debug);
  }
  current_output = reflector_ptr->step(current_output, debug);

  for (int i = 0; i < num_rotors; i++)
    current_output = rotors_ptrs[i]->step(current_output, debug);

  current_output = plugboard_ptr->step(current_output, debug);

  return current_output;					
}


void EnigmaMachine:: processRotorRotations(int rotor_index){
  if (rotor_index == num_rotors-1) // last rotor
    rotors_ptrs[rotor_index]->rotate();

  if (rotors_ptrs[rotor_index]->notchEngaged()
      && rotor_index != 0) // not the first rotor
    rotors_ptrs[rotor_index-1]->rotate();
}
  

Error EnigmaMachine:: checkArgs(int num_configs, char** configs){
  if (num_configs < MIN_ENIGMA_ARGS)
    return Error(INSUFFICIENT_NUMBER_OF_PARAMETERS);

  Error plugboard_error = Plugboard::invalidArg(*configs++);
  if (plugboard_error.getCode())
    return plugboard_error;
  
  Error reflector_error = Reflector::invalidArg(*configs++);
  if (reflector_error.getCode())
    return reflector_error;
  

  for (int i = MIN_ENIGMA_ARGS; i < num_configs -1; i++){
    Error rotor_error = Rotor::invalidArg(*configs++);
    if (rotor_error.getCode())
      return rotor_error;
  }

  return Error(NO_ERROR);
}


Error EnigmaMachine::run(bool debug){
  char c;
  int input;
  while(std::cin >> c){
    input = toInt(c);
    if (invalid_index(input))
      return Error(INVALID_INPUT_CHARACTER);
    std::cout << toChar(step(input, debug));
  }
  return Error(NO_ERROR);
}
