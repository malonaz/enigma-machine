

#include "enigma.h"
#include "errors.h"
#include <iostream>

int main(int argc, char **argv){
  int num_configs = argc -1;
  char** configs = ++argv;
 
  
  Error enigma_error = EnigmaMachine::checkArgs(num_configs,configs);
  
  if (enigma_error.getCode()){
    std::cerr << enigma_error;
    return enigma_error.getCode();
  }
  
  EnigmaMachine enigma(num_configs, configs);
	       		       
  Error runtime_error = enigma.run();
  if (runtime_error.getCode()){
    std::cerr << runtime_error;
    return runtime_error.getCode();
  }
  
  return NO_ERROR;
}

