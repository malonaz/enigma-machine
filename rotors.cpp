// -*- C++ -*-
#include <fstream>
#include <iostream>
#include <set>
#include <cctype>
#include "rotors.h"
#include "errors.h"
#include "sm.h"

Instruction Disk::step(Instruction inp, bool debug){
  int output = inp.value;
  Instruction instr(output,ROTATE_NOW);
  if (debug)
    std::cout << convert_int(output) << "-d->" << convert_int(output) << "\n";
  return instr;
}


Rotor::Rotor(char* mapping_config)
  :offset(0){
  std::ifstream rotor_input(mapping_config);
  inverse = true;
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

int Rotor::check_arg(char* arg){
  std::ifstream input(arg);
  //std::cout << "starting Rotor check\n";
  if(!input.is_open()){

    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  std::set<int> digits;
  int digit;
  int count = 0;
  while(input>>digit){
    if (digit<0 || digit >25){

      return INVALID_INDEX;
    }
    if (count < 26){
      if (digits.find(digit) != digits.end()){

	return INVALID_ROTOR_MAPPING;
      }
      digits.insert(digit);
      count++;
    }
  }
  if (!input.eof()){ // what if it's last char..

    return NON_NUMERIC_CHARACTER; // or 'a'
  }

  if (digits.size() != 26){

    return  INVALID_ROTOR_MAPPING;
  }
    
  return NO_ERROR;  
}



void Rotor:: set_offset(int offset){
  this->offset = offset;
}

void Rotor:: rotate(){
  offset = (offset+1)%26;
}

Instruction Rotor:: step(Instruction inp, bool debug){
  inverse = !inverse;
  int offset_inp, msg = NO_MSG, output;
  if (inp.message == ROTATE_NOW){
    if (debug)
      std::cout << "rotating-->";
    rotate();
    
  }
  if (notch_engaged() && !inverse)
    msg = ROTATE_NOW;
  
  offset_inp =(inp.value + offset)%26;
  
  if (!inverse){
    output = mapping[offset_inp];
    output = output - offset;
    if (output<0)
      output+= 26;
    if (debug)
      std:: cout << (char)(inp.value +97) << "-off->" << (char)(offset_inp + 97) << "-->" <<(char)( output+97) << "\n";
    return (Instruction(output,msg));
  }
  
  output = inverse_mapping[offset_inp];
  output = output - offset;
  if (output<0)
    output+=26;
  if (debug)
    std:: cout << (char)(inp.value +97) << "-off->" << (char)(offset_inp+97) << "-inv->" <<(char)(output+97) << "       " << msg <<"\n";
  return (Instruction(output,msg));
}


bool Rotor:: notch_engaged(){
  for (unsigned i = 0; i < notches.size(); i++){
    if (offset == notches[i])
      return true;
  }
  return false;
}

Cascade:: Cascade(SM** sm_ptrs,int num_ptrs){
  for (int i =0; i<num_ptrs; i++){
    this->sm_ptrs.push_back(sm_ptrs[i]);
  }
}

Instruction Cascade:: step(Instruction inp, bool debug){
  Instruction current_output = inp;
  
  SM* current_sm_ptr;
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

int Reflector:: check_arg(char * arg){
  std::ifstream input(arg);
  //std::cout << "starting Reflector check\n";
  if(!input.is_open()){

    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  std::set<int> digits;
  int digit;
  while(input>>digit){
    if (digit<0 || digit >25){

      return INVALID_INDEX;
    }
    if (digits.find(digit) != digits.end()){

      return INVALID_REFLECTOR_MAPPING;
    }
    digits.insert(digit);
  }
  if (!input.eof()){ // what if it's last char.. 

    return NON_NUMERIC_CHARACTER; // or 'a'
  }

  if (digits.size() != 26){

    return  INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
    
  return NO_ERROR;  
}


Plugboard::Plugboard(char* mapping_config){
  std::ifstream plugboard_input(mapping_config);
  mapping.resize(26);
  for (int i = 0; i<26;i++)
    mapping[i] = i;
  int x,y;
  while(!plugboard_input.eof()){
    plugboard_input >> x >> y;
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

int Plugboard::check_arg(char* arg){
  std::ifstream input(arg);

  std::cout << "starting Plugboard check";

  if(!input.is_open()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  std::set<int> digits;
  int digit;
  while(input>>digit){
    if (digit<0 || digit >25){

      return INVALID_INDEX;
    }
    if (digits.find(digit) != digits.end()){
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
    digits.insert(digit);
  }
  
  if (!input.eof()){ // what if it's last char.. 

    return NON_NUMERIC_CHARACTER;
  }
  if (digits.size()%2 != 0){

    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  return NO_ERROR;
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
