#include "test.h"
#include "errors.h"
#include <iostream>
#include <cstring>


/* plugboard filepath info for testing purposes */
#define PB1  "plugboards/I.pb" // plugboard I
#define PB2 "plugboards/II.pb" // plugboard II
#define PB3 "plugboards/III.pb" // pluboard III
#define PB4 "plugboards/IV.pb" // plugboard IV
#define PB5 "plugboards/V.pb" // plugboard V

#define INVALID_PB "plugboards/doesnotexist.pb" // does not exist
#define NULL_PB "plugboards/null.pb" // empty plugboard
#define PB6 "plugboards/1pair.pb" // 1 pair
#define PB7 "plugboards/pb7.pb" // 6 pairs, 5th pair maps to itself
#define PB8 "plugboards/pb8.pb" // 6 pairs, 5th pair maps to contact already mapped
#define PB9 "plugboards/pb9.pb" // 6 pairs, 5th pair maps already mapped contact  to other




int test_count = 0;
int subtest_count = 0;
int test_passed = 0;
int exp_error;
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
  std::cout << "  testing Pl-ugboard::checkArg() \n";

  // ERROR_OPENING_CONFIGURATION_FILE 
  exp_error = ERROR_OPENING_CONFIGURATION_FILE;
  testPlugboardCheckArg(INVALID_PB);   // 1) invalid filepath

  // NO_ERROR 
  exp_error = NO_ERROR;
  testPlugboardCheckArg(NULL_PB); // 2) empty pb
  testPlugboardCheckArg(NULL_PB);   // 3) one pair pb
  testPlugboardCheckArg(PB1);   // 4) 13 pairs pb

  // IMPOSSIBLE_PLUGBOARD_CONFIGURATION
  exp_error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  testPlugboardCheckArg(PB7); // 5) maps to itself
  testPlugboardCheckArg(PB8); // 6) maps to contact already mapped
  testPlugboardCheckArg(PB9); // 7) maps contact already mapped
  



  std::cout << " Finished testing Plugboard\n\n";
}


void testPlugboardCheckArg(const char* arg){
  test_count++;
  subtest_count++;

  strcpy(filepath,arg);
  
  Error error = Plugboard::checkArg(filepath);
  processError(error, exp_error);
  
}



void processError(Error error, int exp_error){

  std::cout << "   test " << subtest_count << "... ";

  if (exp_error == error.getCode()){
    test_passed++;
    std::cout << "test passed!";
  }else{
    std::cout << "test failed!\n";
    std::cout << "    got: " << error.getCode();
    std::cout << "\n    exp: " << exp_error;
  }
  std::cout << "\n";



}
