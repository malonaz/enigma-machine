#include <iostream>
#include <fstream>
#include "../include/rotors.h"
#include "../include/enigma.h"
#include<vector>

using namespace std;

int main(int argc, char **argv){
  cout << "\n\nWelcome \n\n";
  cout << "we have loaded "<<argc << " arguments!" <<endl;

  std::cout <<"Error code: " << EnigmaMachine:: check_args(argc-1,argv + 1) << std::endl;
  EnigmaMachine enigma(argc-1, argv + 1);

  if(enigma.change_rotor_pos(*(argv+argc-1)))
    return enigma.change_rotor_pos(*(argv+argc-1));
  
  enigma.test();
  
  return 0;
}

