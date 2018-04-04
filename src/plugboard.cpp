// -*- C++ -*-
#include "plugboard.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <set>

Plugboard::Plugboard(char* config){
  std::ifstream config_stream(config);
  
  mapping.resize(26);
  for (int i = 0; i<26;i++)
    mapping[i] = i;

  int x,y;
  
  while(config_stream >> x >> y){
    mapping[x] = y;
    mapping[y] = x;
  }

  config_stream.close();
}


int Plugboard:: step(int input, bool debug){
  if (debug)
    std::cout << toChar(input) << "-plug->";
  
  return mapping[input];
}



Error Plugboard::checkArg(char* config){
  Error error(config, PLUGBOARD);
  std::ifstream config_stream(config);

  if (!config_stream.is_open())
    error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  int num1, num2;

  while (getNextPair(num1, num2, error, config_stream)){
    if(invalidIndex(num1) || invalidIndex(num2)) 
      error.setCode(INVALID_INDEX);
    
    if (inSet(nums,num1) || inSet(nums,num2) || num1 == num2)
      error.setCode(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
                                                 
    nums.insert(num1);                           
    nums.insert(num2);
  }
  
  if (!error.getCode() && !config_stream.eof())
    error.setCode(NON_NUMERIC_CHARACTER);

  config_stream.close();
  return error;
}

