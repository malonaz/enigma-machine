#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "rotors.h"
#include "enigma.h"
#include "errors.h"


using namespace std;

int main(int argc, char **argv){

  ErrorReport error_report = EnigmaMachine::check_args(argc-1,argv + 1);

  if (error_report.get_code()){
    cerr << error_report;
    return error_report.get_code();
  }

  EnigmaMachine enigma(argc-1, argv + 1);
  
  if (argc-1 >  MIN_ENIGMA_ARGS){
    ErrorReport rotor_setting_report =enigma.change_rotor_pos(*(argv+argc-1)); 
    if(rotor_setting_report.get_code()){
      cerr << rotor_setting_report;
      return rotor_setting_report.get_code();
    }
  }
  
  if (!enigma.testLab()){
    ErrorReport invalid_character_report(INVALID_INPUT_CHARACTER);
    return invalid_character_report.get_code();
  }
  
  return NO_ERROR;
}

