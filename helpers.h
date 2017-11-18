// -*- C++ -*-
#ifndef HELPERS_H
#define HELPERS_H

#include "errors.h"
#include <set>
#include <fstream>
/**
 * helper function which, given an ascii character in the range [A-Z],
 * returns the corresponding integer in the range [0-25].
 */
int toInt(char c);


/**
 * helper function which, given an integer in the range [0,25],
 * returns the corresponding ascii character in the range [A-Z]. 
 */
char toChar(int n);


/**
 * helper function which performs modulo26
 * arithmetic on a given integer then returns it
 */
int mod26(int n);


/**
 * helper function, which given an digit
 * returns true if digit is not in range [0,25]
 * returns false otherwise
 */
bool invalidIndex(int digit);


/**
 * helper function, which given a set of integer
 * and an integer:
 * returns true if the integer is in the set.
 * returns false otherwise
 */
bool inSet(std::set<int> digits, int digit);


/**
 * helper function which attempts to extract two integers from 
 * config_stream and:
 * - if error's code is not NO_ERROR, returns false
 * - if extracts two integers successfully, returns true
 * - if it fails to extract the first integers, returns false
 * - if it fails to extract the 2nd integer:
 *     > if is is the end of file, sets error's code to 
 *     INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
 *     > returns false
 */ 
bool getNextPair(int &num1, int &num2, Error &error,
		 std::ifstream &config_stream);


/**
 * helper function which sets error's code to 
 * NON_NUMERIC_CHARACTER if config contains 
 * a non-numeric character
 */
void checkForNumericChar(char* config, Error &error);


#endif
