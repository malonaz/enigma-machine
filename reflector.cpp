// -*- C++ -*-
#include "reflector.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <set>

Reflector::Reflector(char* config){
  
  std::ifstream config_stream(config);
  
  mapping.resize(26);
  
  int x,y;
  
  for (int i = 0; i<13; i++){
    config_stream >> x >> y;
    mapping[x] = y;
    mapping[y] = x;
  }
  
  config_stream.close();    
}



int Reflector::step(int input, bool debug){
  if (debug)
    std::cout << toChar(input) << "-ref->";
  
  return mapping[input];
}


Error Reflector::checkArg(char* config){
  Error error(config, REFLECTOR);
  std::ifstream config_stream(config);

  if (!config_stream.is_open())
    return error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  int num1, num2;
  
  while (config_stream >> num1){
    
    if (!(config_stream >> num2)){
      if (config_stream.eof())
	return error.setCode(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
      return error.setCode(NON_NUMERIC_CHARACTER);
    }

    if (inSet(nums,num1) || inSet(nums, num2) || num1 == num2)
      return error.setCode(INVALID_REFLECTOR_MAPPING);

    if (nums.size() = 26)
      return error.setCode(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    
    if (invalidIndex(num1) || invalidIndex(num2))
      return error.setCode(INVALID_INDEX);
    
    
    nums.insert(num1);
    nums.insert(num2);    
  }
  
  if(!config_stream.eof())
    return error.setCode(NON_NUMERIC_CHARACTER);
  
  if (nums.size() != 26)
    return error.setCode(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  
  return error;
}

