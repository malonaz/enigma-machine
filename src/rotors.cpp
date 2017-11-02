// -*- C++ -*-
#include "../include/rotors.h"
#include <fstream>
#include <iostream>
#include "../include/errors.h"
#include "../include/sm.h"


Rotor::Rotor(char* mapping_config){
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


void Rotor:: set_state(int new_state){
  state = new_state;
}

int Rotor:: step(int inp){
  int offset_inp;
  inverse = !inverse;
  
  if (!inverse){
    rotate();
    offset_inp  = (inp + state)%26;
    std:: cout << (char)(inp +97) << "-->" <<(char)( mapping[offset_inp]+97) << "\n";

    return (mapping[offset_inp]);
  }
  offset_inp = (inp + state)%26;
  std:: cout << (char)(inp +97) << "-inv->" <<(char)(inverse_mapping[offset_inp]+97) << "\n";
  return (inverse_mapping[offset_inp]);
}

bool Rotor:: notch_engaged(){
  for (unsigned i = 0; i < notches.size(); i++){
    if (state == notches[i])
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

int Cascade:: step(int inp){
  int input = inp;
  for (unsigned i = 0; i<sm_ptrs.size(); i++){
    input = sm_ptrs[i]->step(input);
  }
  return input;
}

Reflector::Reflector(char* mapping_config){
  std::ifstream reflector_input(mapping_config);
  mapping.resize(26);
  int x,y;
  for (int i = 0; i<13; i++){
    reflector_input >> x >> y;
    mapping[x] = y;
  }
  reflector_input.close();    
}


int Reflector::step(int inp){
  std:: cout << (char)(inp +97) << "-ref->" <<(char)( mapping[inp]+97) << "\n";
  return mapping[inp];
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



void Rotor:: print_state(){
  std:: cout << "State: " << state << '\n';
}
