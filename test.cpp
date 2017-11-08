#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "rotors.h"
#include "enigma.h"
#include "errors.h"


using namespace std;



void print_file(const char* root, const char * file){
  string filename = root;
  filename.append(file);
  ifstream input(filename.c_str());
  string str;
  getline(input,str);
  cout << str << endl;
  //cout << "Model error stream: " << str;
}



void run_test(int argc,char** argv, const char* test_num){
  cout << "\n\nRunning test " << test_num << endl;

  string root = "tests/test";
  root += test_num;
  root.append("/");
  int current_error_code;

  current_error_code = EnigmaMachine::check_args(argc,argv);

  if (current_error_code){
    print_file(root.c_str(),"error_stream");
    print_error(current_error_code);
    cout << "your error code: " << current_error_code;
    return;
  }

  EnigmaMachine enigma(argc, argv);

  if ( argc >  MIN_ENIGMA_ARGS){
    current_error_code =enigma.change_rotor_pos(*(argv + argc -1)); 
    if(current_error_code){
      print_file(root.c_str(),"error_stream");
      print_error(current_error_code);
      return;
    }
  }

  string inputs = root + "input";
  const char *str = inputs.c_str();
  
  if (!enigma.transduce(str)){
    print_file(root.c_str(),"error_stream");
    cout << "your error code: " << INVALID_INPUT_CHARACTER << endl;
    return;
  }
  cout << endl;
  print_file(root.c_str(),"output");
  
}

int main(){
  cout << "TESTING..." << endl;
  //test 0
  int argc = 6;
  char *argv0[] = {"tests/test0/plugboard.pb", "tests/test0/reflector.rf", "tests/test0/I.rot", "tests/test0/II.rot", "tests/test0/III.rot", "tests/test0/rotors.pos"};
  run_test(argc,argv0,"0");

  // test1
  argc =2;
  char *argv1[] = {"tests/test1/plugboard.pb", "tests/test1/reflector.rf"};
  run_test(argc,argv1,"1");

  argc = 2;
  char *argv2[] = {"tests/test2/plugboard.pb", "tests/test2/reflector.rf"};
  run_test(argc,argv2,"2");


  argc = 2;
  char *argv3[] = {"tests/test3/plugboard.pb", "tests/test3/reflector.rf"};
  run_test(argc,argv3, "3");


  argc = 5;
  char *argv4[] = {"tests/test4/plugboard.pb", "tests/test4/reflector.rf", "tests/test4/rotor.rot", "tests/test4/rotor2.rot", "tests/test4/rotor.pos"};
  run_test(argc,argv4,"4");
  return 0;
}
