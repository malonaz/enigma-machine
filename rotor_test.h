// -*- C++ -*-
#ifndef ROTOR_TEST_H
#define ROTOR_TEST_H

/**
 * Function which will test the Rotor class methods.
 * Testing strategy:
 *
 * for checkArg:
 * - ERROR_OPENING_CONFIGURATION_FILE
 * - NO_ERROR
 *   > correct mapping, 0 notches
 *   > correct mapping with one input mapping to itself, 0 notches
 *   > correct mapping, and 3 notches
 *   > specs allow for repeated notches value so we must accept it
 * - INVALID_ROTOR_MAPPING (1)
 *   > maps 0 input
 *   > maps 1 input
 *   > maps 25 inputs
 *   > connect a contact already connected
 *   > connect a contact to a contact already connected
 * - INVALID_INDEX (2)
 *   > negative integer
 *   > starts with a >25 integer
 *   > ends with a >25 integer
 * - NON_NUMERIC_CHARACTER (3)- 
 *   > file begins with a character 
 *   > non-numeric char as first notch
 *   > ends with non-numeric char
 *   > word in the middle
 *   > int+char in the middle
 *   > ends with int+char as 26th entry 
 * - HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS:
 *   > INVALID_ROTOR_MAPPING
 *     o no ambiguous situations with:
 *       > INVALID_INDEX because if I have less than 26 integers
 *         and the last one is an invalid index, the INVALID_INDEX
 *         error will interrupt my reading operation and thus takes
 *         priority.
 *   > INVALID_INDEX
 *     o pair (x,y) where x>25 & y already mapped 
 *     o pair (x,y) where x already mapped & y>25 
 *     o pair (x,y) where x or y is negative. I consider "-14" to be numerical
 *       although the character '-' on its own is non-numeric
 *   > NON_NUMERIC_CHARACTER
 *     o pair (x,y) where x>25 and y is non-numeric. we are reading in pairs so
 *       although invalid index occurs before non-numeric character, 
 *     o (1 2 3 4 5 @): file contains an odd number and specs indicate to return that
 *       error first, but I believe NON_NUMERIC_CHARACTER is encounted first here, 
 *       rather than simultaneously with the odd number error. 
 *     o pair (x,y) where x is non-numeric and y>25
 *     o 5 pairs followed by a non-numeric character
 *     o file contains a '-', a space, then a number
 *
 * For Step: 
 *  Note: As described in my reflector.h documentation, step expects input 
 *        in range [0,25]. I do not expect or test input outside this range because
 *        this class is only used by the EnigmaMachine class which will never it
 *        incorrect input.
 *  - entire input domain must return a value in range [0,25] & no 2 inputs 
 *    map to the same output
 *    > reflector
 *    > reflector V
 */
void testRotor();

/**
 * Function which, given a plugboard filepath will 
 * check whether the error given by Plugboard::checkArg 
 * method has code equal to exp_error_code
 * - increments subtest_count, test_count.
 * - if test is passed -> increments test_passed.
 * - outputs test results
 */
void testRotorCheckArg(const char* arg);

/**
 * Function which, given a reflector filepath with
 * correct configuration, constructs a Reflector and 
 * makes it step through rangre [0,25]
 * - increments test_count, subtest_count
 * - if all inputs map to a value in range [0,25] and 
 *   no two inputs map to the same output, increments
 *   test_passed.
 * - outputs test results
 */
void testRotorStep(const char* arg);

#endif
