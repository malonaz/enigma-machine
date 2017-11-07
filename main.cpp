#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "rotors.h"
#include "enigma.h"
#include "errors.h"


using namespace std;

int main(int argc, char **argv){
  ifstream input;
  string str;
  for (int i = 1; i< argc; i++){
    std::cout << *(argv + i) << ": ";
    input.open(*(argv+i));
    getline(input, str);
    cout << str << '\n';
    input.close();
    cout << '\n';
  }
  cout << "input: ";
  getline(cin,str);
  cout << str << '\n';
  
  return 0;
  // cout << "DEBUG STARTS HERE" << endl;
  //for (int i =0; i<argc; i++)
  //  cout << *(argv+i) << endl;
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

  if (argc-1 >  MIN_ENIGMA_ARGS){
    flag =enigma.change_rotor_pos(*(argv+argc-1)); 
    if(flag){
      print_error(flag);
      return flag;
    }
  }
  
  if (!enigma.testLab())
    return INVALID_INPUT_CHARACTER;
  
  return 0;
}

