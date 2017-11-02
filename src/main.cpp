#include <iostream>
#include <fstream>
#include "../include/rotors.h"
#include<vector>

using namespace std;

int main(int argc, char **argv){
  Disk entryDisk;
  Rotor rotor1(argv[1]);
  Rotor rotor2(argv[2]);
  Rotor rotor3(argv[3]);
  Reflector reflector(argv[4]);
  SM* sm_ptrs[] = {&entryDisk,&rotor1,&rotor2,&rotor3,&reflector,&rotor3,&rotor2,&rotor1};
  
  Cascade cascade(sm_ptrs,8);
  cascade.test();
  //cascade.step(Instruction(0,NO_MSG));
  
  return 0;
}
