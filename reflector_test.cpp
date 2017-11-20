#include "reflector_test.h"
#include "reflector.h"
#include "errors.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
#include <set>

// declarations needed
extern int test_count, test_passed, subtest_count, exp_error_code;

/* Standard Reflectors */
#define RF1  "reflectors/I.rf" // reflector I
#define RF2 "reflectors/II.rf" // reflector II
#define RF3 "reflectors/III.rf" // pluboard III
#define RF4 "reflectors/IV.rf" // reflector IV
#define RF5 "reflectors/V.rf" // reflector V


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
  testReflectorCheckArg("reflectors/rf7.rf"); // 5) maps to itself
  testReflectorCheckArg("reflectors/rf8.rf"); // 6) maps to contact already mapped
  testReflectorCheckArg("reflectors/rf9.rf"); // 7) maps contact already mapped

  // INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS (2)
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testReflectorCheckArg("reflectors/rf10.rf"); // 8) 0 pair
  testReflectorCheckArg("reflectors/rf12.rf"); // 9) 1 integer
  testReflectorCheckArg("reflectors/rf13.rf"); // 10) 12 pairs
  
  // INVALID_INDEX (2)
  exp_error_code = INVALID_INDEX;
  testReflectorCheckArg("reflectors/rf14.rf"); // 11) negative integer
  testReflectorCheckArg("reflectors/rf15.rf"); // 12) starts with a >25 integer
  testReflectorCheckArg("reflectors/rf16.rf"); // 13) ends with a>25 integer

  // NON_NUMERIC_CHARACTER (3)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testReflectorCheckArg("reflectors/rf17.rf"); // 14) begins with non-num char
  testReflectorCheckArg("reflectors/rf18.rf"); // 15) ends with non-num char
  testReflectorCheckArg("reflectors/rf19.rf"); // 16) word in middle
  testReflectorCheckArg("reflectors/rf20.rf"); // 17) int+char in middle
  testReflectorCheckArg("reflectors/rf21.rf"); // 18) int+char at the end

  // HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS //////
  
  //// INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  exp_error_code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  testReflectorCheckArg("reflectors/rf22.rf"); // 19) 5 ints where 5th > 25

  //// INVALID_INDEX
  exp_error_code = INVALID_INDEX;
  testReflectorCheckArg("reflectors/rf23.rf"); // 20) pair (x,y) where x>25 & y already mapped
  testReflectorCheckArg("reflectors/rf24.rf"); // 21) pair (x,y) where x already mapped & y>25
  testReflectorCheckArg("reflectors/rf25.rf"); // 22) pair (x,y)  where x<0
  testReflectorCheckArg("reflectors/rf26.rf"); // 23) pair (x,y) where x>25 and y is non-numeric
  
  //// NON_NUMERIC_CHARACTER
  exp_error_code = NON_NUMERIC_CHARACTER; 
  testReflectorCheckArg("reflectors/rf27.rf"); // 24) odd number + non-numeric char
  testReflectorCheckArg("reflectors/rf28.rf"); // 25) even number followed non-numeric char
  testReflectorCheckArg("reflectors/rf29.rf"); // 26) pair (x,y) where x non-numeric and y>25
  testReflectorCheckArg("reflectors/rf30.rf"); // 27) even number with ' - ' in middle
  testReflectorCheckArg("reflectors/rf31.rf"); // 28) contains a float
  
  
  // Check Reflector class is working properly
  subtest_count = 0;
  std::cout << "\n  Testing Reflector::step() \n"; 
  testReflectorStep(RF1); // 1) reflector I
  testReflectorStep(RF5); // 2) reflector II
  
  
  std::cout << " Finished testing Reflector\n\n";
}

void testReflectorCheckArg(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  
  Error error = Reflector::checkArg(filepath);
  
  Error exp_error(filepath, REFLECTOR);
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


void testReflectorStep(const char* arg){
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
