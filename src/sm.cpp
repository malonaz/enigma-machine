#include "../include/sm.h"

int convert_char(char c){
  return c-97;
}

char convert_int(int c){
  return c+97;
}


void SM::test(){
  char input;
    while(true){
      set_state(25);
      std::cout << "Enter a letter: ";
      std::cin >> input;
      std::cout << input << " is mapped to " << convert_int(step(convert_char(input))) << std::endl;
    }
}
