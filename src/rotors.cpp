// -*- C++ -*-
#include "../include/rotors.h"
#include <fstream>
#include <iostream>
#include "../include/errors.h"
#include "../include/sm.h"

Instruction Disk::step(Instruction inp){
  return Instruction(inp.value,ROTATE_NOW);
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


void Rotor:: set_offset(int offset){
  this->offset = offset;
}

void Rotor:: rotate(){
  offset = (offset+1)%26;
}

Instruction Rotor:: step(Instruction inp){
  inverse = !inverse;
  int offset_inp, msg = NO_MSG, output;
  if (inp.message == ROTATE_NOW)
    rotate();
  if (notch_engaged() && !inverse)
    msg = ROTATE_NOW;
  
  offset_inp =(inp.value + offset)%26;
  
  if (!inverse){
    //    std:: cout <<" not inverse ";
    output = mapping[offset_inp];
    output = output - offset;
    if (output<0)
      output+= 26;
    
    std:: cout << (char)(inp.value +97) << "-off->" << (char)(offset_inp + 97) << "-->" <<(char)( output+97) << "\n";
    return (Instruction(output,msg));
  }
  
  //output = inverse_mapping[offset_inp];
  output = inverse_mapping[offset_inp];
  output = output - offset;
  if (output<0)
    output+=26;
    
  std:: cout << (char)(inp.value +97) << "-off->" << (char)(offset_inp+97) << "-inv->" <<(char)(output+97) << "\n";
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

Cascade:: Cascade(std::vector<SM*> sm_ptrs){
  this->sm_ptrs = sm_ptrs;
}


Instruction Cascade:: step(Instruction inp){
  Instruction current_output = inp;
  
  SM* current_sm_ptr;
  for (unsigned i = 0; i<sm_ptrs.size(); i++){
    current_sm_ptr = sm_ptrs[i];
    current_output = current_sm_ptr->step(current_output);
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


Instruction Reflector::step(Instruction inp){
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
