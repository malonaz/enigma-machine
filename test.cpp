#include "test.h"
#include "plugboard_test.h"
#include "reflector_test.h"
#include "rotor_test.h"
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

  testRotor();
  
  std::cout << "passed " << test_passed << "/" << test_count << "\n\n";

}

