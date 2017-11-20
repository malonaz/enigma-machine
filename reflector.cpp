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
    error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  int num1, num2;

  while (getNextPair(num1,num2,error,config_stream)){
    if (invalidIndex(num1) || invalidIndex(num2))
      error.setCode(INVALID_INDEX);

    if (inSet(nums,num1) || inSet(nums,num2) || num1 == num2)
      error.setCode(INVALID_REFLECTOR_MAPPING);
    
    if (!error.getCode()){      
      nums.insert(num1);            
      nums.insert(num2);
    }
  }
  
  if(!error.getCode()){
    if (!config_stream.eof())
      error.setCode(NON_NUMERIC_CHARACTER);
    else if (nums.size() != 26)
      error.setCode(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS, "insufficient");
  }
  
  config_stream.close();
  return error;  
}

