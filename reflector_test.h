// -*- C++ -*-
#ifndef REFLECTOR_TEST_H
#define REFLECTOR_TEST_H

/**
 * Function which will test the Reflector class methods.
 * Testing strategy:
 *
 * for checkArg:
 * - ERROR_OPENING_CONFIGURATION_FILE
 * - NO_ERROR
 *   > 13 pairs 
 * - INVALID_REFLECTOR_MAPPING (1)
 *   > connects a contact with itself
 *   > connect a contact already connected
 *   > connect a contact to a contact already connected
 * - INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS (2)
 *   > 0 pair
 *   > 14 pairs
 *   > 1 integer
 *   > 27 integers
 * - INVALID_INDEX (3)
 *   > negative integer
 *   > starts with a >25 integer
 *   > ends with a >25 integer
 * - NON_NUMERIC_CHARACTER (4)
 *   > file begins with a character 
 *   > ends with char
 *   > word in the middle
 *   > int+char in the middle
 *   > ends with int+char 
 * - HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS:
 *   > INVALID_REFLECTOR_MAPPING
 *     o no ambiguous situation where this error takes priority because
 *       1) NON_NUMERIC_CHARACTER  & INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
 *       occur outside pair analysis
 *       2) INVALID_INDEX takes priority as a number with an invalid index
 *          is not considered an index to the alphabet. Therefore, given a pair (x,y)
 *          where x already mapped and y>25, I do not consider this an attempt to
 *          map x to more than one other index.
 *   > INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
 *     o 5 integers where the 5th >25
 *   > INVALID_INDEX
 *     o pair (x,y) where x>25 & y already mapped 
 *     o pair (x,y) where x already mapped & y>25 
 *     o pair (x,y) where x or y is negative. I consider "-14" to be numerical
 *       although the character '-' on its own is non-numeric     
 *     o pair (x,y) where x>25 and y is non-numeric. 
 *   > NON_NUMERIC_CHARACTER
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
void testReflector();

/**
 * Function which, given a plugboard filepath will 
 * check whether the error given by Plugboard::checkArg 
 * method has code equal to exp_error_code
 * - increments subtest_count, test_count.
 * - if test is passed -> increments test_passed.
 * - outputs test results
 */
void testReflectorCheckArg(const char* arg);

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
void testReflectorStep(const char* arg);

#endif
