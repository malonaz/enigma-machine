#include <iostream>
#include <fstream>
#include<vector>
#include "rotors.h"
#include "enigma.h"


using namespace std;

int main(int argc, char **argv){
  cout << "\n\nWelcome \n\n";
  cout << "we have loaded "<<argc << " arguments!" <<endl;

  std::cout <<"Error code: " << EnigmaMachine:: check_args(argc-1,argv + 1) << std::endl;
  EnigmaMachine enigma(argc-1, argv + 1);

  if(enigma.change_rotor_pos(*(argv+argc-1)))
    std::cout<< "rotor pos: "<< enigma.change_rotor_pos(*(argv+argc-1)) << "\n";
  
  if (!enigma.testLab())
    return INVALID_INPUT_CHARACTER;
  
  return 0;
}

