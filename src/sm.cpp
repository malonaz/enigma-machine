#include "../include/sm.h"

int convert_char(char c){
  return c-97;
}

char convert_int(int c){
  return c+97;
}

void SM::test(){
  char c;
  int value;
    while(true){
      std::cout << "Enter a letter: ";
      std::cin >> c;
      value = convert_char(c);
      std::cout << c << " is mapped to " << convert_int(step(Instruction(value,NO_MSG)).value) << std::endl;
    }
}

Instruction SM:: step(Instruction inp){
  Instruction instruction(inp);
  return instruction;
}
