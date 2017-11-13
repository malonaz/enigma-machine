// -*- C++ -*-
#include "rotors.h"
#include <iostream>
#include <fstream>
#include <set>

Rotor::Rotor(char* config)
  : mapping(26,0), inverse_mapping(26,0),
    notches(26,0), offset(0), inverse(false){
  
  std::ifstream config_stream(config);
  int map_to, notch;

  for (int i = 0; i < 26; i++){
    config_stream >> map_to;
    mapping[i] = map_to;
    inverse_mapping[map_to] = i;
  }
  
  while(config_stream >> notch){
    notches[notch] = 1;
  }
  
  config_stream.close();
}

int Rotor:: step(int input, bool debug){
  int offset_input, output, offset_output;
  
  offset_input = mod26(input + offset);
  
  if (!inverse)
    offset_output = mapping[offset_input];
  
  else
    offset_output = inverse_mapping[offset_input];

  output = mod26(offset_output - offset);
    
  if (debug){
    std::cout << toChar(input) << "-off->" << toChar(offset_input);
    std::cout << "-rot->" << toChar(offset_output);
    std::cout << "-off->" << toChar(output) << "\n";
  }

  inverse = !inverse; //reversing direction		  

  return output;
}

Error Rotor:: checkArg(char* config){
  Error error(config, ROTOR);
  std::ifstream config_stream(config);

  if(!config_stream.is_open())
    return error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  int num;

  while (config_stream >> num){
    if (invalid_index(num))
      return error.setCode(INVALID_INDEX);

    if (nums.size() != 26){
      if (is_in_set(nums, num))
	return error.setCode(INVALID_ROTOR_MAPPING);
      nums.insert(num);
    }
  }
  if (!config_stream.eof())
    return error.setCode(NON_NUMERIC_CHARACTER);

  if (nums.size() != 26)
    return error.setCode(INVALID_ROTOR_MAPPING);
  
  return error;
}



