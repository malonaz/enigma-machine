// -*- C++ -*-
#include "rotor.h"
#include <iostream>
#include <fstream>
#include <set>
#include <cstring>

Rotor::Rotor(char* config)
  : mapping(ALPHABET_SIZE,0), inverse_mapping(ALPHABET_SIZE,0),
    notches(ALPHABET_SIZE,0), offset(0), inverse(false){
  
  std::ifstream config_stream(config);
  int map_to, notch;

  for (int i = 0; i < ALPHABET_SIZE; i++){
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

/**
 * internal helper function which returns a string object containing
 * error information for INVALID_ROTOR_MAPPING errors
 */
std::string getInvalidRotorMappingInfo(int previous_input,
				       int output, size_t current_input){
  std::string str("Invalid mapping of input ");
  str += current_input +  " to output " + output;
  str += " (output " + output;
  str += " is already mapped to from input " + previous_input;
  std:: cout <<str;
  return str;
}

Error Rotor:: checkArg(char* config){
  Error error(config, ROTOR);
  std::ifstream config_stream(config);

  if(!config_stream.is_open())
    error.setCode(ERROR_OPENING_CONFIGURATION_FILE);

  std::set<int> nums;
  std::vector<int> mappings(ALPHABET_SIZE, -1);
  int num;

  while (getNextInt(num, error, config_stream)){
    if (invalidIndex(num))
      error.setCode(INVALID_INDEX);

    if (nums.size() < ALPHABET_SIZE){
      if (inSet(nums, num)){
	std::cerr << "Invalid mapping of input " << nums.size();
	std::cerr << " to output " << num << " (output " << num;
	std::cerr << " is already mapped to from input " << mappings[num];
	std:: cerr << ") in ";
	error.setCode(INVALID_ROTOR_MAPPING);
      }
      mappings[num] = nums.size();
      nums.insert(num);
    }
  }
  
  if (!config_stream.eof()){
    if (nums.size() == ALPHABET_SIZE)
      error.setCode(NON_NUMERIC_CHARACTER, "for notches ");
    else
      error.setCode(NON_NUMERIC_CHARACTER, "for mapping ");
  }

  if (nums.size() != ALPHABET_SIZE)
    error.setCode(INVALID_ROTOR_MAPPING, "not all inputs mapped in ");

  config_stream.close();
  return error;
}



