#include <iostream>
#include <fstream>
#include<vector>
#include "rotors.h"
#include "enigma.h"
#include "errors.h"

using namespace std;

int main(int argc, char **argv){
  // cout << "\n\nWelcome \n\n";
  // cout << "we have loaded "<<argc << " arguments!" <<endl;
  int flag;
  // std::cout <<"Error code: " << EnigmaMachine:: check_args(argc-1,argv + 1) << std::endl;
  flag = EnigmaMachine::check_args(argc-1,argv + 1);

  if (flag){
    print_error(flag);
    return flag;
  }
      
  EnigmaMachine enigma(argc-1, argv + 1);

  flag =enigma.change_rotor_pos(*(argv+argc-1)); 
  if(flag){
    print_error(flag);
    return flag;
  }

  
  if (!enigma.testLab())
    return INVALID_INPUT_CHARACTER;
  
  return 0;
}

