// -*- C++ -*-
#include <fstream>
#include <iostream>
#include <set>
#include <cctype>
#include "rotors.h"
#include "errors.h"
#include "sm.h"

Instruction EntryDisk::step(Instruction instr, bool debug){
  Instruction instr_output(instr.value,ROTATE_NOW);

  if (debug)
    std::cout << convert_int(instr.value) << "-d->" << convert_int(instr.value) << "\n";

  return instr_output;
}

Rotor::Rotor(char* mapping_config)
  :offset(0),inverse(false){
  std::ifstream rotor_input(mapping_config);
  int map_to;
  mapping.resize(26);
  inverse_mapping.resize(26);

  for (int i = 0; i<26; i++){
    rotor_input >> map_to;
    mapping[i] = map_to;
    inverse_mapping[map_to] = i;
  }
  while(rotor_input >> map_to){
    notches.push_back(map_to);
  }
  rotor_input.close();
}

ErrorReport Rotor::check_arg(char* arg){
  std::ifstream input(arg);
  if(!input.is_open())
    return ErrorReport(ERROR_OPENING_CONFIGURATION_FILE,arg);
  
  std::set<int> digits;
  int digit;
  int count = 0;
  
  while(input>>digit){
    
    if (invalid_index(digit)){
      return ErrorReport(INVALID_INDEX,arg);
    }
    if (count < 26){
      if (is_in_set(digits,digit)){
	return ErrorReport(INVALID_ROTOR_MAPPING,arg);
      }
      digits.insert(digit);
      count++;
    }
  }
  if (!input.eof()){ // what if it's last char..
    return ErrorReport(NON_NUMERIC_CHARACTER,arg); // or 'a'
  }

  if (digits.size() != 26){
    return  ErrorReport(INVALID_ROTOR_MAPPING,arg);
  }
    
  return ErrorReport(NO_ERROR,arg);
}



void Rotor:: set_offset(int offset){
  this->offset = offset;
}

void Rotor:: rotate(){
  offset = (offset+1)%26;
}

Instruction Rotor:: step(Instruction instr, bool debug){
  int offset_value, output_value, output_msg = NO_MSG;
  if (instr.message == ROTATE_NOW){
    if (debug)
      std::cout << "rotating-->";
    rotate();
  }
  
  if (notch_engaged() && !inverse)
    output_msg = ROTATE_NOW;
  
  offset_value =(instr.value + offset)%26;

  if (!inverse)
    output_value = mapping[offset_value];
  else
    output_value = inverse_mapping[offset_value];
  
  output_value -= offset;
  if (output_value<0)
    output_value += 26;

  if (debug)
    std::cout << (char)(instr.value+65) << "-off->" << (char)(offset_value + 65) << "-rot->" << (char)(output_value + 65) << "\n";

  inverse = !inverse;		  

  return (Instruction(output_value,output_msg));
}


bool Rotor:: notch_engaged(){
  for (unsigned i = 0; i < notches.size(); i++){
    if (offset == notches[i])
      return true;
  }
  return false;
}







Cascade:: Cascade(StateMachine** sm_ptrs,int num_ptrs){
  for (int i =0; i<num_ptrs; i++){
    this->sm_ptrs.push_back(sm_ptrs[i]);
  }
}

Instruction Cascade:: step(Instruction inp, bool debug){
  Instruction current_output = inp;
  
  StateMachine* current_sm_ptr;
  for (unsigned i = 0; i<sm_ptrs.size(); i++){
    current_sm_ptr = sm_ptrs[i];
    current_output = current_sm_ptr->step(current_output,debug);
  }
  return current_output;
}

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


Plugboard::Plugboard(char* mapping_config){
  std::ifstream plugboard_input(mapping_config);
  mapping.resize(26);
  for (int i = 0; i<26;i++)
    mapping[i] = i;
  int x,y;
  while(plugboard_input >> x >>y){
    mapping[x] = y;
    mapping[y] = x;
  }
  plugboard_input.close();
}

Instruction Plugboard:: step(Instruction inp, bool debug){
  if (debug)
    std::cout << convert_int(inp.value) << "-p->";
  
  return Instruction(mapping[inp.value],NO_MSG);
}

ErrorReport Plugboard::check_arg(char* arg){
  std::ifstream input(arg);
  if(!input.is_open())
    return ErrorReport(ERROR_OPENING_CONFIGURATION_FILE,arg);

  std::set<int> digits;
  int x,y;
  while(input>>x){
    if (!(input>>y)){
      if (input.eof())
	return ErrorReport(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS, arg);
      else
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
  
  if (!input.eof()){ 
    return ErrorReport(NON_NUMERIC_CHARACTER, arg);
  }
 
  return ErrorReport(NO_ERROR);
}


Instruction Reflector::step(Instruction inp, bool debug){
  if (debug)
    std:: cout << (char)(inp.value +97) << "-ref->" <<(char)( mapping[inp.value]+97) << "\n";
  return Instruction(mapping[inp.value], NO_MSG);
}







/////////////////DEBUGGING METHODS///////////////////////////////
void Rotor:: print_attributes(){
  
  std:: cout << "Mapping: ";
  for (unsigned i = 0; i < mapping.size(); i++){
    std::cout << (char)(mapping[i]+97) << ' ';
  }
  std:: cout << "\nInverse Mapping: ";
  for (unsigned i = 0; i < inverse_mapping.size(); i++){ 
    std::cout << (char)(inverse_mapping[i]+97) << ' ';
  }
  
  std:: cout << "\nNotches: ";
  
  for (unsigned i = 0; i< notches.size(); i++){
    std::cout<< notches[i] << ' ';
  }
  std:: cout << '\n';  
}



void Rotor:: print_offset(){
  std:: cout << "Offset: " << offset << '\n';
}
