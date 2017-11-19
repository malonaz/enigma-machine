#include "test.h"
#include "plugboard_test.h"
#include "reflector_test.h"
#include <iostream>

/* global test variables */
int exp_error_code;
int test_count =0;
int test_passed = 0;
int subtest_count;

void test(){
  std::cout << "\n\nStarting tests... \n\n";
    
  testPlugboard();

  testReflector();
  
  std::cout << "passed " << test_passed << "/" << test_count << "\n\n";

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

