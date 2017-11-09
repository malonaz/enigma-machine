
#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include <cstring>


//#include "rotors.h"
#include "enigma.h"
#include "errors.h"
//#include "reflector.h"

using namespace std;



void print_file(const char* root, const char * file){
  string filename = root;
  filename.append(file);
  ifstream input(filename.c_str());
  string str;
  getline(input,str);
  cout << str << endl;
}



void run_test(int argc,char** argv, const char* test_num){
  cout << "\n\nRunning test " << test_num << endl;

  string root = "tests/test";
  root += test_num;
  root.append("/");

  ErrorReport error_report = EnigmaMachine::check_args(argc,argv);
  
  if (error_report.get_code()){
    print_file(root.c_str(),"error_stream");
    cerr << error_report;
    return;
  }

  EnigmaMachine enigma(argc, argv);
  
  if ( argc >  MIN_ENIGMA_ARGS){
    ErrorReport error_report2 = enigma.change_rotor_pos(*(argv + argc -1)); 
    if(error_report2.get_code()){
      print_file(root.c_str(),"error_stream");
      cerr << error_report2;
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

void increment_argv(char** argv, const char x, const char y){
  for (int i =0; i< 6; i++){
    argv[i][10] = x;
    argv[i][11] = y;
  }
}

int main(){
  cout << "TESTING..." << endl;

  char plugboard[50], reflector[50], rotor[50], rotor2[50], rotor3[50], rotor_pos[50];
  strcpy(plugboard,"tests/test00/plugboard.pb");
  strcpy(reflector, "tests/test00/reflector.rf");
  strcpy(rotor, "tests/test00/rotor.rot");
  strcpy(rotor2,"tests/test00/rotor2.rot");
  strcpy(rotor3,"tests/test00/rotor3.rot");
  strcpy(rotor_pos, "tests/test00/rotor.pos");
  char* argv[10] = {plugboard,reflector,rotor,rotor2,rotor3,rotor_pos};
  
  //test 0
  int argc = 6;
  run_test(argc,argv,"00");

  // test1
  argc =2;
  increment_argv(argv,'0','1');
  run_test(argc,argv,"01");

  argc = 2;
  increment_argv(argv,'0','2');
  run_test(argc,argv,"02");

  argc = 2;
  increment_argv(argv,'0','3');
  run_test(argc,argv, "03");

  argv[4] = rotor_pos;
  
  argc = 5;
  increment_argv(argv,'0','4');
  run_test(argc,argv,"04");

  argc = 0;
  increment_argv(argv,'0','5');
  run_test(argc,argv,"05");

  
  argv[3] = rotor_pos;
  argc = 4;
  increment_argv(argv,'0','6');
  run_test(argc,argv,"06");

  argc = 4;
  increment_argv(argv,'0','7');
  run_test(argc,argv,"07");

  argc = 4;
  increment_argv(argv,'0','8');
  run_test(argc,argv,"08");

  argc = 4;
  increment_argv(argv,'0','9');
  run_test(argc,argv,"09");

  argc = 4;
  increment_argv(argv,'1','0');
  run_test(argc,argv,"10");

  
  cout<< "\n\n\n\n";

  return 0;
}
