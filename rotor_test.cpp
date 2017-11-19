#include "rotor_test.h"
#include "rotors.h"
#include "errors.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
#include <set>

// declarations needed
extern int test_count, test_passed, subtest_count, exp_error_code;

/* Standard Rotors */
#define ROT1  "rotors/I.rf" // reflector I
#define ROT2 "rotors/II.rf" // reflector II
#define ROT3 "rotors/III.rf" // pluboard III
#define ROT4 "rotors/IV.rf" // reflector IV
#define ROT5 "rotors/V.rf" // reflector V


void testReflector(){
  std::cout << " Testing Reflector\n";
  subtest_count = 0;

  // checkArg tests
  std::cout << "  Testing Reflector::checkArg() \n";

  // ERROR_OPENING_CONFIGURATION_FILE 
  exp_error_code = ERROR_OPENING_CONFIGURATION_FILE;
  testReflectorCheckArg("doesnotexist");   // 1) invalid filepath
  // NO_ERROR 
  exp_error_code = NO_ERROR;
  testReflectorCheckArg(RF1); // 2) reflector I
  testReflectorCheckArg(RF2);   // 3) reflector II
  testReflectorCheckArg(RF5);   // 4) reflector V

  // INVALID_REFLECTOR_MAPPING (1)
  exp_error_code = INVALID_REFLECTOR_MAPPING;
  testReflectorCheckArg("rotors/rf7.rf"); // 5) maps to itself
  testReflectorCheckArg("rotors/rf8.rf"); // 6) maps to contact already mapped
  testReflectorCheckArg("rotors/rf9.rf"); // 7) maps contact already mapped

  // INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS (2)
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testReflectorCheckArg("rotors/rf10.rf"); // 8) 0 pair
  testReflectorCheckArg("rotors/rf11.rf"); // 9) 14 pairs
  testReflectorCheckArg("rotors/rf12.rf"); // 10) 1 integer
  testReflectorCheckArg("rotors/rf13.rf"); // 11) 12 pairs
  
  // INVALID_INDEX (2)
  exp_error_code = INVALID_INDEX;
  testReflectorCheckArg("rotors/rf14.rf"); // 12) negative integer
  testReflectorCheckArg("rotors/rf15.rf"); // 13) starts with a >25 integer
  testReflectorCheckArg("rotors/rf16.rf"); // 14) ends with a>25 integer

  // NON_NUMERIC_CHARACTER (3)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testReflectorCheckArg("rotors/rf17.rf"); // 15) begins with non-num char
  testReflectorCheckArg("rotors/rf18.rf"); // 16) ends with non-num char
  testReflectorCheckArg("rotors/rf19.rf"); // 17) word in middle
  testReflectorCheckArg("rotors/rf20.rf"); // 18) int+char in middle
  testReflectorCheckArg("rotors/rf21.rf"); // 19) int+char at the end

  // HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS //////
  
  //// INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testReflectorCheckArg("rotors/rf22.rf"); // 20) 5 ints where 5th > 25
  
  //// INVALID_INDEX
  exp_error_code = INVALID_INDEX;
  testReflectorCheckArg("rotors/rf23.rf"); // 21) pair (x,y) where x>25 & y already mapped
  testReflectorCheckArg("rotors/rf24.rf"); // 22) pair (x,y) where x already mapped & y>25
  testReflectorCheckArg("rotors/rf25.rf"); // 23) pair (x,y)  where x<0
  testReflectorCheckArg("rotors/rf26.rf"); // 24) pair (x,y) where x>25 and y is non-numeric
  
  //// NON_NUMERIC_CHARACTER
  exp_error_code = NON_NUMERIC_CHARACTER;
  testReflectorCheckArg("rotors/rf27.rf"); // 25) odd number + non-numeric char
  testReflectorCheckArg("rotors/rf28.rf"); // 26) even number followed non-numeric char
  testReflectorCheckArg("rotors/rf29.rf"); // 27) pair (x,y) where x non-numeric and y>25
  testReflectorCheckArg("rotors/rf30.rf"); // 28) even number with ' - ' in middle
  testReflectorCheckArg("rotors/rf31.rf"); // 29) contains a float
  
  
  // Check Reflector class is working properly
  subtest_count = 0;
  std::cout << "\n  Testing Reflector::step() \n"; 
  testRotorstep(RF1); // 1) reflector I
  testRotorstep(RF5); // 2) reflector II
  
  
  std::cout << " Finished testing Reflector\n\n";
}


void testReflectorCheckArg(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  
  Error error = Reflector::checkArg(filepath);
  Error exp_error = error;
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


void testRotorstep(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;
  strcpy(filepath,arg);
  Reflector reflector(filepath);

  std::cout <<"   test " << subtest_count<< "...";
  std::set<int> outputs;
  int output;
  for (int i =0; i < ALPHABET_SIZE; i++){
    output = reflector.step(i);
    if (inSet(outputs,output) || invalidIndex(output))
      std::cout << "test failed!\n";
  }
  test_passed++;
  std::cout << "test passed!\n";
}
