#include <iostream>
#include <string>
#include <cctype>
#include "sm.h"


/* internal helper function which, given an ascii character in the range [A-Z],
   returns the corresponding integer in the range [0-25].*/
int convert_char(char c){
  return c-65;
}

/* internal helper function which, given an integer in the range [0,25],
   returns the corresponding ascii character in the range [A-Z]. */
char convert_int(int c){
  return c+65;
}


void StateMachine::run(bool debug){
  std::string str;
  std::cout << "\nEnter a string:\n";
  std::getline(std::cin,str);
  int val;
  char c;
  for (unsigned i= 0; i<str.size();i++){
    if (str[i] == ' '){
      std::cout << ' ';
    }else{
      val = convert_char(str[i]);//std::tolower(str[i]));
      c = convert_int(step(Instruction(val,NO_MSG),debug).value);
      std:: cout << c;
    }
  }
  std::cout << std::endl;
}

Instruction StateMachine:: step(Instruction instr, bool debug){
  Instruction instruction(instr);
  return instruction;
}
