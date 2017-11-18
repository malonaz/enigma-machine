#include "test.h"
#include "errors.h"
#include <iostream>
#include <cstring>


/* plugboard filepath info for testing purposes */
// STANDARD PLUGBOARDS
#define PB1  "plugboards/I.pb" // plugboard I
#define PB2 "plugboards/II.pb" // plugboard II
#define PB3 "plugboards/III.pb" // pluboard III
#define PB4 "plugboards/IV.pb" // plugboard IV
#define PB5 "plugboards/V.pb" // plugboard V

// NO_ERROR
#define INVALID_PB "plugboards/doesnotexist.pb" // does not exist
#define NULL_PB "plugboards/null.pb" // empty plugboard
#define PB6 "plugboards/1pair.pb" // 1 pair
// IMPOSSIBLE_PLUGBOARD_CONFIGURATION
#define PB7 "plugboards/pb7.pb" // 6 pairs, 5th pair maps to itself
#define PB8 "plugboards/pb8.pb" // 6 pairs, 5th pair maps to contact already mapped
#define PB9 "plugboards/pb9.pb" // 6 pairs, 5th pair maps already mapped contact  to other
// INCORRECT_NUMBER_PLUGBOARD_PARAMETERS
#define PB10 "plugboards/pb10.pb" // 1 integer
#define PB11 "plugboards/pb11.pb" // 25 integers
// INVALID_INDEX
#define PB12 "plugboards/pb12.pb" // contains neg int
#define PB13 "plugboards/pb13.pb" // starts with an int that's >25
#define PB14 "plugboards/pb14.pb" // ends with an int that's >25
// NON_NUMERIC_CHARACTERS
#define PB15 "plugboards/pb15.pb" // starts with char
#define PB16 "plugboards/pb16.pb" // 13 pairs + a char
#define PB17 "plugboards/pb17.pb" // word in middle
#define PB18 "plugboards/pb18.pb" // int+char in middle
#define PB19 "plugboards/pb19.pb" // ends with int+char
// HIERARCHY (1)
#define PB20 "plugboards/pb20.pb" // 29 ints
#define PB21 "plugboards/pb21.pb" // 26 integers where 26th has invalid index
#define PB22 "plugboards/pb22.pb" // maps already mapped contact then later has a char
#define PB23 "plugboards/pb23.pb" // maps to contact already mapped, followed by char
// HIERARCHY (2)
#define PB24 "plugboards/pb24.pb" // 5 integers, 5th is >25
#define PB25 "plugboards/pb25.pb" // 5 integers, followed by "@"


int test_count = 0;
int subtest_count = 0;
int test_passed = 0;
int exp_error_code;
char filepath[MAX_FILEPATH_ARRAY];

void test(){
  std::cout << "\n\nStarting tests... \n\n";
    
  testPlugboard();

  std::cout << "passed " << test_passed << "/" << test_count << "\n\n";

}


void testPlugboard(){
  std::cout << " Testing Plugboard\n";
  subtest_count = 0;

  // checkArg tests
  std::cout << "  testing Plugboard::checkArg() \n";

  // ERROR_OPENING_CONFIGURATION_FILE 
  exp_error_code = ERROR_OPENING_CONFIGURATION_FILE;
  testPlugboardCheckArg(INVALID_PB);   // 1) invalid filepath

  // NO_ERROR 
  exp_error_code = NO_ERROR;
  testPlugboardCheckArg(NULL_PB); // 2) empty pb
  testPlugboardCheckArg(NULL_PB);   // 3) one pair pb
  testPlugboardCheckArg(PB1);   // 4) 13 pairs pb

  // IMPOSSIBLE_PLUGBOARD_CONFIGURATION (1)
  exp_error_code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  testPlugboardCheckArg(PB7); // 5) maps to itself
  testPlugboardCheckArg(PB8); // 6) maps to contact already mapped
  testPlugboardCheckArg(PB9); // 7) maps contact already mapped

  // INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS (2)
  exp_error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  testPlugboardCheckArg(PB10); // 8) 1 integer
  testPlugboardCheckArg(PB11); // 9) 25 integers
  
  // INVALID_INDEX (2)
  exp_error_code = INVALID_INDEX;
  testPlugboardCheckArg(PB12); // 10) contains negative integer
  testPlugboardCheckArg(PB13); // 11) starts with an int >25
  testPlugboardCheckArg(PB14); // 12) ends with an int >25

  // NON_NUMERIC_CHARACTER (3)
  exp_error_code = NON_NUMERIC_CHARACTER;
  testPlugboardCheckArg(PB15); // 13) starts with a character
  testPlugboardCheckArg(PB16); // 14) 13 pairs + 1 char
  testPlugboardCheckArg(PB17); // 15) word in middle
  testPlugboardCheckArg(PB18); // 16) int+char in middle
  testPlugboardCheckArg(PB19); // 17) int+char at the end

  // HIERARCHY
  exp_error_code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  testPlugboardCheckArg(PB20); // 18) 29 integers
  testPlugboardCheckArg(PB21); // 19) 26 integers where 26th has invalid index ????
  testPlugboardCheckArg(PB22); // 20) maps already mapped contact then later has a char "-"
  testPlugboardCheckArg(PB23); // 21) maps to contact already mapped, followed by a "/"
  
  exp_error_code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  testPlugboardCheckArg(PB24); // 22) 5 integers, 5th is >25
  testPlugboardCheckArg(PB25); // 23) 5 integers, followed by "@"    
  std::cout << " Finished testing Plugboard\n\n";
}


void testPlugboardCheckArg(const char* arg){
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  
  Error error = Plugboard::checkArg(filepath);
  Error exp_error = error;
  exp_error.setCode(exp_error_code);
  processError(error, exp_error);
  
}



void processError(Error error, Error exp_error){
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
