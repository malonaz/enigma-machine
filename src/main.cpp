#include <iostream>
#include <fstream>
#include "../include/rotors.h"

using namespace std;

int convert_char(char c){
  return c-97;
}

char convert_int(int c){
  return c+97;
}

void test_sm(SM &sm){
  char input;
  while(true){
    sm.set_state(25);
    cout << "Enter a letter: ";
    cin >> input;
    cout << input << " is mapped to " << convert_int(sm.step(convert_char(input))) << endl;
  }
}

int main(int argc, char **argv){
  Rotor rotor1(argv[1]);
  rotor1.set_state(25);
  Rotor rotor2(argv[1]);
  rotor2.set_state(25);
  Cascade cascade(rotor1,rotor2);
  test_sm(cascade);
  return 0;
}
