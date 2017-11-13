// -*- C++ -*-
#ifndef HELPERS_H
#define HELPERS_H

#include <set>

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
bool invalid_index(int digit);


/**
 * helper function, which given a set of integer
 * and an integer:
 * returns true if the integer is in the set.
 * returns false otherwise
 */
bool is_in_set(std::set<int> digits, int digit);



#endif
