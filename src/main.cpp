#include <iostream>
#include <fstream>
#include "../include/rotors.h"
#include "../include/enigma.h"
#include<vector>

using namespace std;

int main(int argc, char **argv){
  cout << "\n\nWelcome \n\n";
  cout << "we have loaded "<<argc << " arguments!" <<endl;

  std::cout <<"Error code: " << Plugboard:: check_arg(argv[1]) << std::endl;
  //Plugboard::check_arg(argv[1]);
  EnigmaMachine enigma(argc-1, ++argv);


  
  //enigma.test();
  
  return 0;
}

