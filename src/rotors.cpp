// -*- C++ -*-
#include "../include/rotors.h"
#include <fstream>
#include <iostream>
#include "../include/errors.h"
#include "../include/sm.h"


Rotor::Rotor(char* mapping_config){
  std::ifstream rotor_input(mapping_config);
  int map_to;
  
  for (int i = 0; i<26; i++){
    rotor_input >> map_to;
    mapping.push_back(map_to);
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
  rotate();
  int offset_inp  = (inp + state)%26;
  return (mapping[offset_inp]);
}

bool Rotor:: notch_engaged(){
  for (unsigned i = 0; i < notches.size(); i++){
    if (state == notches[i])
      return true;
  }
  return false;
}



Cascade::Cascade(SM &sm1, SM &sm2){
  this->sm1 = sm1;
  this->sm2 = sm2;
}



int Cascade:: step(int inp){
  int sm1_output = sm1.step(inp);
  return sm2.step(sm1_output);
}







/////////////////DEBUGGING METHODS///////////////////////////////
void Rotor:: print_attributes(){
  std:: cout << "Mapping: ";
  for (unsigned i = 0; i < mapping.size(); i++){
    std::cout << mapping[i] << ' ';
  }
  std:: cout << '\n'<< "Notches: ";
  
  for (unsigned i = 0; i< notches.size(); i++){
    std::cout<< notches[i] << ' ';
  }
  std:: cout << '\n';  
}



void Rotor:: print_state(){
  std:: cout << "State: " << state << '\n';
}
