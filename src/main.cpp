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
  rotor1.print_attributes();
  cascade.test();
  rotor1.print_offset();
  rotor2.print_offset();
  rotor3.print_offset();
  return 0;
}
