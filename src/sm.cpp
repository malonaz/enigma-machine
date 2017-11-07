#include <iostream>
#include <string>
#include <cctype>
#include "../include/sm.h"


int convert_char(char c){
  return c-65;
}

char convert_int(int c){
  return c+65;
}


void SM::run(bool debug){
  std::string str;
  std::cout << "\nEnter a string:\n";
  std::getline(std::cin,str);
  int val;
  char c;
  for (unsigned i= 0; i<str.size();i++){
    if (str[i] == ' '){
      std::cout << ' ';
    }else{
      val = convert_char(std::tolower(str[i]));
      c = convert_int(step(Instruction(val,NO_MSG),debug).value);
      std:: cout << c;
    }
  }
  std::cout << std::endl;
}

void SM::test(bool debug){
  std::cout << "Enter a char, then press enter\n";
  char input;
  int output;
  Instruction instr(0,NO_MSG);
  while(std::cin >> input){
    instr.value = convert_char(input);
    output = step(instr,debug).value;
    if (debug)
      std::cout << input << " maps to ";
    std::cout << convert_int(output);
    std::cout << '\n';
  }
}



Instruction SM:: step(Instruction inp, bool debug){
  Instruction instruction(inp);
  return instruction;
}
