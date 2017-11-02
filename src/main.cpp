#include <iostream>
#include <fstream>
#include "../include/rotors.h"
#include<vector>

using namespace std;

int main(int argc, char **argv){
  Rotor rotor1(argv[1]);
  Rotor rotor2(argv[2]);
  Rotor rotor3(argv[3]);
  rotor1.set_state(25);
  rotor2.set_state(25);
  rotor3.set_state(25);
  Reflector reflector(argv[4]);

  SM* sm_ptrs[] = {&rotor1,&rotor2,&rotor3,&reflector,&rotor3,&rotor2,&rotor1};
  
  Cascade cascade(sm_ptrs,7);
  cascade.test();

  
  return 0;
}
