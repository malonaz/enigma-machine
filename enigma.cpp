// -*- C++ -*-
#include "enigma.h"
#include "helpers.h"
#include "errors.h"
#include <iostream>
#include <fstream>

EnigmaMachine::EnigmaMachine(int argc, char** argv)
  :  num_rotors(0) {
  
  plugboard_ptr = new Plugboard(*argv++);
  reflector_ptr = new Reflector(*argv++);

  if(argc > MIN_ENIGMA_ARGS){
    num_rotors = argc - MIN_ENIGMA_ARGS -1;
    rotor_ptrs = new Rotor*[num_rotors];
   
    for (int i = 0; i < num_rotors; i++)
      rotor_ptrs[i] = new Rotor(*argv++);

    setRotorPos(*argv++);
  }
}


EnigmaMachine::~EnigmaMachine(){
  delete plugboard_ptr;
  delete reflector_ptr;
  delete [] rotor_ptrs;
}

int EnigmaMachine::step(int input, bool debug){
  int current_output = input;

  current_output = plugboard_ptr->step(current_output, debug);
  processRotorRotations();
   
  for (int i = num_rotors -1; i >= 0; i--)
    current_output = rotor_ptrs[i]->step(current_output, debug);
  
  current_output = reflector_ptr->step(current_output, debug);

  for (int i = 0; i < num_rotors; i++)
    current_output = rotor_ptrs[i]->step(current_output, debug);

  current_output = plugboard_ptr->step(current_output, debug);

  return current_output;					
}


void EnigmaMachine:: processRotorRotations(){
  if (num_rotors == 0)
    return;
  
  int first_rotor_index = num_rotors -1, last_rotor_index = 0;
  rotor_ptrs[first_rotor_index]->rotate();

  for (int i = first_rotor_index; i > last_rotor_index; i--)
    if (rotor_ptrs[i]->notchEngaged())
      rotor_ptrs[i-1]->rotate();
}
  

Error EnigmaMachine:: checkArgs(int num_configs, char** configs){
  if (num_configs < MIN_ENIGMA_ARGS)
    return Error(INSUFFICIENT_NUMBER_OF_PARAMETERS);

  Error plugboard_error = Plugboard::checkArg(*configs++);
  if (plugboard_error.getCode())
    return plugboard_error;
  
  Error reflector_error = Reflector::checkArg(*configs++);
  if (reflector_error.getCode())
    return reflector_error;

  int num_rotors = num_configs - MIN_ENIGMA_ARGS -1;
  if (num_rotors > 0){
    for (int i = 0; i < num_rotors; i++){
      Error rotor_error = Rotor::checkArg(*configs++);
      if (rotor_error.getCode())
	return rotor_error;
    }

    Error rotor_pos_error = EnigmaMachine::checkRotorPos(*configs++, num_rotors);
    if (rotor_pos_error.getCode())
      return rotor_pos_error;
  }
  
  return Error(NO_ERROR);
}

void EnigmaMachine::setRotorPos(char*config){
  std::ifstream config_stream(config);
  int num;
  for (int i = 0; i < num_rotors; i++){
    config_stream >> num;
    rotor_ptrs[i]->setOffset(num);
  }
  config_stream.close();
}

Error EnigmaMachine::checkRotorPos(char* config, int num_rotors){
  Error error(config, ROTOR_POS);
  std::ifstream config_stream(config);

  if(!config_stream.is_open())
    return error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  int num, count = 0;

  while (config_stream >> num){
    if (invalid_index(num))
      return error.setCode(INVALID_INDEX);
    count++;
  }

  if (!config_stream.eof())
    return error.setCode(NON_NUMERIC_CHARACTER);

  if (count != num_rotors)
    return error.setCode(NO_ROTOR_STARTING_POSITION);

  return error;    
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



