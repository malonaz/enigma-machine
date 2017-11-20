#include "rotor_test.h"
#include "rotor.h"
#include "errors.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
#include <set>

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
  testRotorCheckArg(ROT1); // 2) reflector I
  testRotorCheckArg(ROT2);   // 3) reflector II
  testRotorCheckArg(ROT5);   // 4) reflector V

  // INVALID_REFLECTOR_MAPPING (1)
  exp_error_code = INVALID_REFLECTOR_MAPPING;
  testRotorCheckArg("rotors/rot7.rot"); // 5) maps to itself
  testRotorCheckArg("rotors/rot8.rot"); // 6) maps to contact already mapped
  testRotorCheckArg("rotors/rot9.rot"); // 7) maps contact already mapped

  // INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS (2)
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testRotorCheckArg("rotors/rot10.rot"); // 8) 0 pair
  testRotorCheckArg("rotors/rot11.rot"); // 9) 14 pairs
  testRotorCheckArg("rotors/rot12.rot"); // 10) 1 integer
  testRotorCheckArg("rotors/rot13.rot"); // 11) 12 pairs
  
  // INVALID_INDEX (2)
  exp_error_code = INVALID_INDEX;
  testRotorCheckArg("rotors/rot14.rot"); // 12) negative integer
  testRotorCheckArg("rotors/rot15.rot"); // 13) starts with a >25 integer
  testRotorCheckArg("rotors/rot16.rot"); // 14) ends with a>25 integer

  // NON_NUMERIC_CHARACTER (3)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testRotorCheckArg("rotors/rot17.rot"); // 15) begins with non-num char
  testRotorCheckArg("rotors/rot18.rot"); // 16) ends with non-num char
  testRotorCheckArg("rotors/rot19.rot"); // 17) word in middle
  testRotorCheckArg("rotors/rot20.rot"); // 18) int+char in middle
  testRotorCheckArg("rotors/rot21.rot"); // 19) int+char at the end

  // HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS //////
  
  //// INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testRotorCheckArg("rotors/rot22.rot"); // 20) 5 ints where 5th > 25
  
  //// INVALID_INDEX
  exp_error_code = INVALID_INDEX;
  testRotorCheckArg("rotors/rot23.rot"); // 21) pair (x,y) where x>25 & y already mapped
  testRotorCheckArg("rotors/rot24.rot"); // 22) pair (x,y) where x already mapped & y>25
  testRotorCheckArg("rotors/rot25.rot"); // 23) pair (x,y)  where x<0
  testRotorCheckArg("rotors/rot26.rot"); // 24) pair (x,y) where x>25 and y is non-numeric
  
  //// NON_NUMERIC_CHARACTER
  exp_error_code = NON_NUMERIC_CHARACTER;
  testRotorCheckArg("rotors/rot27.rot"); // 25) odd number + non-numeric char
  testRotorCheckArg("rotors/rot28.rot"); // 26) even number followed non-numeric char
  testRotorCheckArg("rotors/rot29.rot"); // 27) pair (x,y) where x non-numeric and y>25
  testRotorCheckArg("rotors/rot30.rot"); // 28) even number with ' - ' in middle
  testRotorCheckArg("rotors/rot31.rot"); // 29) contains a float
  
  
  // Check Rotor class is working properly
  subtest_count = 0;
  std::cout << "\n  Testing Rotor::step() \n"; 
  testRotorStep(ROT1); // 1) reflector I
  testRotorStep(ROT5); // 2) reflector II
  
  
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
    if (inSet(outputs,output) || invalidIndex(output))
      std::cout << "test failed!\n";
  }
  test_passed++;
  std::cout << "test passed!\n";
}
