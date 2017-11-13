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
    return error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  int num1, num2;
  while (config_stream >> num1){
    if (!(config_stream >> num2)){
      if (config_stream.eof())
	return error.setCode(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
      return error.setCode(NON_NUMERIC_CHARACTER);
    }

    if(invalid_index(num1) || invalid_index(num2))
      return error.setCode(INVALID_INDEX);

    if (is_in_set(nums,num1) || is_in_set(nums,num2) || num1 == num2)
      return error.setCode(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);

    nums.insert(num1);
    nums.insert(num2);

  }
  
  if (!config_stream.eof())
    return error.setCode(NON_NUMERIC_CHARACTER);  
  
  return error;
}

