#include "rotor_test.h"
#include "../src/rotor.h"
#include "../src/errors.h"
#include "../src/helpers.h"
#include <iostream>
#include <cstring>

// declarations needed
extern int test_count, test_passed, subtest_count, exp_error_code;

/* Standard Rotors */
#define ROT1  "rotors/I.rot" // reflector I
#define ROT2 "rotors/II.rot" // reflector II
#define ROT3 "rotors/III.rot" // pluboard III
#define ROT4 "rotors/IV.rot" // reflector IV
#define ROT5 "rotors/V.rot" // reflector V


void testRotor(){
  std::cout << " Testing Rotor\n";
  subtest_count = 0;

  // checkArg tests
  std::cout << "  Testing Rotor::checkArg() \n";

  // ERROR_OPENING_CONFIGURATION_FILE 
  exp_error_code = ERROR_OPENING_CONFIGURATION_FILE;
  testRotorCheckArg("doesnotexist");   // 1) invalid filepath
  // NO_ERROR 
  exp_error_code = NO_ERROR;
  testRotorCheckArg("rotors/rot6.rot"); // 2) 0 notches
  testRotorCheckArg("rotors/rot7.rot");   // 3) one input mapping to itself, 0 notches
  testRotorCheckArg("rotors/rot8.rot");   // 4) 3 notches
  testRotorCheckArg("rotors/rot9.rot");   // 5) repeated notches.

  // INVALID_REFLECTOR_MAPPING (1)
  exp_error_code = INVALID_ROTOR_MAPPING;
  testRotorCheckArg("rotors/rot10.rot"); // 6) maps 0 input
  testRotorCheckArg("rotors/rot11.rot"); // 7) maps 1 input
  testRotorCheckArg("rotors/rot12.rot"); // 8) maps 25 inputs
  testRotorCheckArg("rotors/rot13.rot"); // 9) maps more than one input to the same output
  
  // INVALID_INDEX (2)
  exp_error_code = INVALID_INDEX;
  testRotorCheckArg("rotors/rot14.rot"); // 10) negative integer
  testRotorCheckArg("rotors/rot15.rot"); // 11) starts with a >25 integer
  testRotorCheckArg("rotors/rot16.rot"); // 12) ends with a>25 integer

  // NON_NUMERIC_CHARACTER (3)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testRotorCheckArg("rotors/rot17.rot"); // 13) begins with non-num char
  testRotorCheckArg("rotors/rot18.rot"); // 14) non-numeric char as first notch
  testRotorCheckArg("rotors/rot19.rot"); // 15) ends with non-numeric char
  testRotorCheckArg("rotors/rot20.rot"); // 16) word in the middle
  testRotorCheckArg("rotors/rot21.rot"); // 17) int+char in the middle
  testRotorCheckArg("rotors/rot22.rot"); // 18) 26th entry is int+char

  // HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS //////
  //// INVALID_INDEX
  exp_error_code = INVALID_INDEX;
  testRotorCheckArg("rotors/rot23.rot"); // 19) (1 2 3 4 5 50)
  
  //// NON_NUMERIC_CHARACTER
  exp_error_code = NON_NUMERIC_CHARACTER;
  testRotorCheckArg("rotors/rot24.rot"); // 20) (1 2 3 4 5 @)
  testRotorCheckArg("rotors/rot25.rot"); // 21) (1 2 3 - 4 5)
  
  
  // Test Rotor step
  subtest_count = 0;
  std::cout << "\n  Testing Rotor::step() \n"; 
  testRotorStep(ROT1); // 1) rotor I
  testRotorStep(ROT5); // 2) rotor V
  
  // Test Rotor rotation
  subtest_count = 0;
  std::cout << "\n  Testing Rotor::rotate() \n";
  testRotorRotate(ROT1); // 1) rotor I
  testRotorRotate(ROT5); // 2) rotor V



  // Test Rotor notchEngaged
  subtest_count = 0;
  std::cout << "\n  Testing Rotor::notchEngaged() \n";
  testRotorNotchEngaged(); // contains 1) test 0 notch. 2) test 3 notches


  
  std::cout << " Finished testing Rotor\n\n";
}


void testRotorCheckArg(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  
  Error error = Rotor::checkArg(filepath);
  Error exp_error(filepath, ROTOR);
  exp_error.setCode(exp_error_code);

  std::cout << "   test " << subtest_count << "... ";

  if (exp_error.getCode() == error.getCode()){
    test_passed++;
    std::cout << "test passed!";
  }else{
    std::cout << "test failed!\n";
    std::cout << "    got: " << error;
    std::cout << "\n    exp: " << exp_error;
  }
  std::cout << "\n";
}


void testRotorStep(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;
  strcpy(filepath,arg);
  Rotor rotor(filepath);

  std::cout <<"   test " << subtest_count<< "...";
  std::set<int> outputs;
  int output;
  for (int i =0; i < ALPHABET_SIZE; i++){
    output = rotor.step(i);
    if (inSet(outputs,output) || invalidIndex(output)){
      std::cout << "test failed!\n";
      return;
    }
  }
  test_passed++;
  std::cout << "test passed!\n";
}

void testRotorRotate(const char*arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;
  strcpy(filepath, arg);
  Rotor rotor(filepath);
  std::cout << "   test "  << subtest_count << "...";
  for (int i = 0; i < 100; i++){
    if (rotor.getOffset() != i%26){
      std::cout << "test failed!\n";
      return;
    }
    rotor.rotate();
  }
  test_passed++;
  std::cout << "test passed!\n";
}

void testRotorNotchEngaged(){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;
  strcpy(filepath, "rotors/rot6.rot");
  Rotor rotor(filepath);
  std::cout << "   test "  << subtest_count << "...";
  for (int i = 0; i < 26; i++){
    if (rotor.notchEngaged()){
      std::cout << "test failed!\n";
      return;
    }
    rotor.rotate();
  }
  test_passed++;
  std::cout << "test passed!\n";


  test_count++;
  subtest_count++;
  strcpy(filepath, "rotors/rot8.rot");
  Rotor rotor2(filepath);
  std::cout << "   test "  << subtest_count << "...";
  for (int i = 0; i < 26; i++){
    if (i < 3 && !rotor2.notchEngaged()){
      std::cout << "test failed!\n";
      return;
      
    }else{
      if (rotor.notchEngaged()){
	std::cout << "test failed!\n";
	return;
      }
    }
    rotor2.rotate();
  }
  test_passed++;
  std::cout << "test passed!\n";
}
