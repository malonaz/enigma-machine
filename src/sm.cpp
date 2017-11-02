#include <iostream>
#include <string>
#include <cctype>
#include "../include/sm.h"


int convert_char(char c){
  return c-97;
}

char convert_int(int c){
  return c+97;
}


void SM::test(){
  std::string str;
  std::cout << "Welcome\nEnter a string: ";
  std::getline(std::cin,str);
  int val;
  char c;
  for (unsigned i= 0; i<str.size();i++){
    if (str[i] == ' '){
      std::cout << ' ';
    }else{
      val = convert_char(std::tolower(str[i]));
      c = convert_int(step(Instruction(val,NO_MSG)).value);
      std:: cout << c;
    }
  }
  std::cout << std::endl;
}



Instruction SM:: step(Instruction inp, bool debug){
  Instruction instruction(inp);
  return instruction;
}
