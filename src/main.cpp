#include <iostream>
#include <fstream>
#include "../include/rotors.h"
#include "../include/enigma.h"
#include<vector>

using namespace std;

int main(int argc, char **argv){
  cout << "\n\nWelcome \n\n";
  cout << "we have loaded "<<argc << " arguments!" <<endl;
  
  EnigmaMachine enigma(argc, argv);
  
  enigma.test();

  return 0;
}

