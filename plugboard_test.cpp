#include "plugboard_test.h"
#include "plugboard.h"
#include "errors.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
#include <set>

// declarations needed
extern int test_count, test_passed, subtest_count, exp_error_code;

/* Standard Plugboards */
#define PB1  "plugboards/I.pb" // plugboard I
#define PB2 "plugboards/II.pb" // plugboard II
#define PB3 "plugboards/III.pb" // pluboard III
#define PB4 "plugboards/IV.pb" // plugboard IV
#define PB5 "plugboards/V.pb" // plugboard V


void testPlugboard(){
  std::cout << " Testing Plugboard\n";
  subtest_count = 0;

  // checkArg tests
  std::cout << "  Testing Plugboard::checkArg() \n";

  // ERROR_OPENING_CONFIGURATION_FILE 
  exp_error_code = ERROR_OPENING_CONFIGURATION_FILE;
  testPlugboardCheckArg("doesnotexist");   // 1) invalid filepath
  // NO_ERROR 
  exp_error_code = NO_ERROR;
  testPlugboardCheckArg("plugboards/null.pb"); // 2) empty pb
  testPlugboardCheckArg(PB1);   // 3) one pair pb
  testPlugboardCheckArg(PB5);   // 4) 13 pairs pb

  // IMPOSSIBLE_PLUGBOARD_CONFIGURATION (1)
  exp_error_code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  testPlugboardCheckArg("plugboards/pb7.pb"); // 5) maps to itself
  testPlugboardCheckArg("plugboards/pb8.pb"); // 6) maps to contact already mapped
  testPlugboardCheckArg("plugboards/pb9.pb"); // 7) maps contact already mapped

  // INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS (2)
  exp_error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  testPlugboardCheckArg("plugboards/pb10.pb"); // 8) 1 integer
  testPlugboardCheckArg("plugboards/pb11.pb"); // 9) 25 integers
  
  // INVALID_INDEX (3)
  exp_error_code = INVALID_INDEX;
  testPlugboardCheckArg("plugboards/pb12.pb"); // 10) contains negative integer
  testPlugboardCheckArg("plugboards/pb13.pb"); // 11) starts with an int >25
  testPlugboardCheckArg("plugboards/pb14.pb"); // 12) ends with an int >25

  // NON_NUMERIC_CHARACTER (4)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testPlugboardCheckArg("plugboards/pb15.pb"); // 13) starts with a character
  testPlugboardCheckArg("plugboards/pb16.pb"); // 14) 13 pairs + 1 char
  testPlugboardCheckArg("plugboards/pb17.pb"); // 15) word in middle
  testPlugboardCheckArg("plugboards/pb18.pb"); // 16) int+char in middle
  testPlugboardCheckArg("plugboards/pb19.pb"); // 17) int+char at the end

  // HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS //////
  
  //// INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  exp_error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  testPlugboardCheckArg("plugboards/pb20.pb"); // 18) 5 ints where 5th > 25
  
  //// INVALID_INDEX
  exp_error_code = INVALID_INDEX;
  testPlugboardCheckArg("plugboards/pb21.pb"); // 19) pair (x,y) where x>25 & y already mapped
  testPlugboardCheckArg("plugboards/pb22.pb"); // 20) pair (x,y) where x already mapped & y>25
  testPlugboardCheckArg("plugboards/pb23.pb"); // 21) pair (x,y)  where x<0
  testPlugboardCheckArg("plugboards/pb24.pb"); // 22) pair (x,y) where x>25 and y is non-numeric
  //// NON_NUMERIC_CHARACTER
  exp_error_code = NON_NUMERIC_CHARACTER;
  testPlugboardCheckArg("plugboards/pb25.pb"); // 23) odd number + non-numeric char
  testPlugboardCheckArg("plugboards/pb26.pb"); // 24) even number followed non-numeric char
  testPlugboardCheckArg("plugboards/pb27.pb"); // 25) pair (x,y) where x non-numeric and y>25
  testPlugboardCheckArg("plugboards/pb28.pb"); // 26) even number with ' - ' in middle
  testPlugboardCheckArg("plugboards/pb29.pb"); // 27) contains a float

  // Check Plugboard class is working properly
  subtest_count = 0;
  std::cout << "\n  Testing Plugboard::step() \n"; 
  testPlugboardStep(PB1); // 1) 1 pair
  testPlugboardStep(PB5); // 2) 13 pairs
  
  
  std::cout << " Finished testing Plugboard\n\n";
}


void testPlugboardCheckArg(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  Error error = Plugboard::checkArg(filepath);
  Error exp_error(filepath, PLUGBOARD);
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


void testPlugboardStep(const char* arg){
  char filepath[MAX_ARRAY_LENGTH];
  test_count++;
  subtest_count++;
  strcpy(filepath,arg);
  Plugboard plugboard(filepath);

  std::cout <<"   test " << subtest_count<< "...";
  std::set<int> outputs;
  int output;
  for (int i =0; i < ALPHABET_SIZE; i++){
    output = plugboard.step(i);
    if (inSet(outputs,output) || invalidIndex(output))
      std::cout << "test failed!\n";
  }
  test_passed++;
  std::cout << "test passed!\n";
}
