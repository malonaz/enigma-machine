// -*- C++ -*-

#include "reflector.h"
#include "errors.h"
#include "sm.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <set>


Reflector::Reflector(char* mapping_config){
  std::ifstream reflector_input(mapping_config);
  mapping.resize(26);
  int x,y;
  for (int i = 0; i<13; i++){
    reflector_input >> x >> y;
    mapping[x] = y;
    mapping[y] = x;
  }
  reflector_input.close();    
}

ErrorReport Reflector:: check_arg(char * arg){

  std::ifstream input(arg);

  if(!input.is_open())
      return ErrorReport(ERROR_OPENING_CONFIGURATION_FILE,arg);  
  
  std::set<int> digits;
  int x,y;
  
  while(input>>x){
    if (digits.size() >= 26)
      return ErrorReport(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS,arg);
    
    if (!(input>>y)){
      if (input.eof())
	return ErrorReport(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS, arg);
      return ErrorReport(NON_NUMERIC_CHARACTER, arg);
    }
    
    if (invalid_index(x) || invalid_index(y) ){
      return ErrorReport(INVALID_INDEX, arg);
    }
    if (is_in_set(digits,x) ||is_in_set(digits,y) || x == y){
      return ErrorReport(IMPOSSIBLE_PLUGBOARD_CONFIGURATION, arg);
    }
    digits.insert(x);
    digits.insert(y);
  }
  if (!input.eof())
    return ErrorReport(NON_NUMERIC_CHARACTER, arg);
    
  return ErrorReport(NO_ERROR);
}


Instruction Reflector::step(Instruction inp, bool debug){
  if (debug)
    std:: cout << (char)(inp.value +97) << "-ref->" <<(char)( mapping[inp.value]+97) << "\n";
  return Instruction(mapping[inp.value], NO_MSG);
}
