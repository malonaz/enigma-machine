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
 *     o (1 2 3 4 5 50): file contains <26 numbers and specs indicate to return that
 *       error first, but I believe that invalid_index_is encountered here first.        
 *   > NON_NUMERIC_CHARACTER
 *     o (1 2 3 4 5 @): file contains <26 numbers and specs indicate to return that
 *       error first, but I believe NON_NUMERIC_CHARACTER is encounted first here, 
 *       rather than simultaneously with the odd number error. 
 *     o file contains a '-', a space, then a number
 *
 * For Step: 
 *  Note: As described in my rotor.h documentation, step expects input 
 *        in range [0,25]. I do not expect or test input outside this range because
 *        this class is only used by the EnigmaMachine class which will never
 *        feed it incorrect input.
 *  - entire input domain must return a value in range [0,25] & no 2 inputs 
 *    map to the same output
 *    > Rotor I
 *    > Rotor V
 */
void testRotor();

/**
 * Function which, given a rotor filepath will 
 * check whether the error given by Rotor::checkArg 
 * method has code equal to exp_error_code
 * - increments subtest_count, test_count.
 * - if test is passed -> increments test_passed.
 * - outputs test results
 */
void testRotorCheckArg(const char* arg);

/**
 * Function which, given a rotor filepath with
 * correct configuration, constructs a Rotor and 
 * makes it step through rangre [0,25]
 * - increments test_count, subtest_count
 * - if all inputs map to a value in range [0,25] and 
 *   no two inputs map to the same output, increments
 *   test_passed.
 * - outputs test results
 */
void testRotorStep(const char* arg);



/**
 * Function which, given a rotor filepath with 
 * correct configuration, constructs a Rotor and 
 * makes it rotate 100 times to make sure the 
 * rotate method works correctly.
 * - outputs test results
 */
void testRotorRotate(const char* arg);


/**
 * Function which tests whether notchEngaged
 * method works correctly.
 * outputs test results
 */
void testRotorNotchEngaged();


#endif
