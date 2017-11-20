// -*- C++ -*-
#ifndef PLUGBOARD_TEST_H
#define PLUGBOARD_TEST_H

/**
 * Function which will test the Plugboard class methods.
 * Testing strategy:
 *
 * for checkArg:
 * - ERROR_OPENING_CONFIGURATION_FILE
 * - NO_ERROR
 *   > 0 pair
 *   > 1 pair
 *   > 13 pairs 
 * - IMPOSSIBLE_PLUGBOARD_CONFIGURATION (1)
 *   > connects a contact with itself
 *   > connect a contact already connected
 *   > connect a contact to a contact already connected
 * - INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS (2)
 *   > 1 integer
 *   > 25 integers
 * - INVALID_INDEX (3)
 *   > negative integer??
 *   > starts with a >25 integer
 *   > ends with a >25 integer
 * - NON_NUMERIC_CHARACTER (4)
 *   > file begins with a character 
 *   > ends with char
 *   > char in the middle
 *   > int+char in the middle
 *   > 13 pairs, ends with int+char 
 * - ERROR HIERARCHY:
 *   > (1) then 
 *     o (2): 29 integers -> (1)
 *     o (3): 13 pairs where 12th pair maps to itself, and 25th int > 25 -> (1) ??
 *     o (4): 10th pair connects a contact already connected, followed by non_numeric -> (1)
 *   > (2) then
       o (1) not possible!
 *     o (3): 5 integers where 5th is >25 -> (2)
 *     o (4): not possible!
 *   > (3) then
 *     o (1): 13 pairs, where 12th pair contains int >25 & 13th pair maps to itself -> (3)
 *     o (2): 15 ints, where 3rd integer >25 -> (3)
 *     o (4): invalid index before non_numeric char -> (3)
 *   > (4) then 
 *     o (1): 4 pairs of entry. 1st pair has letters, 2nd pair maps to itself -> (4)
 *     o (2): 5 entries, 3rd int contains non num chars -> (4)
 *     o (3): 10 entries, 3rd contains non num chars, 4th contains invalid index -> (4)

 * - HIERARCHY TRICKY MULTIPLE ERROR SITUATIONS:
 *   > IMPOSSIBLE_PLUGBOARD_CONFIGURATION
 *     o no ambiguous situation where this error takes priority because
 *       1) NON_NUMERIC_CHARACTER  & INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
 *       occur outside pair analysis
 *       2) INVALID_INDEX takes priority as a number with an invalid index
 *          is not considered a contact and therefore, given a pair (x,y)
 *          where x already mapped and y>25, I do not consider this an attempt to
 *          map x to more than one other contact
 *   > INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
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
 *  Note: As described in my Plugboard.h documentation, step expects input 
 *        in range [0,25]. I do not expect or test outside this range because
 *        this class is only used by the EnigmaMachine class which will never 
 *        feed it incorrect input.
 *  - entire input domain must return a value in range [0,25] & no 2 inputs 
 *    map to the same output
 *    > 1 pair plugboard
 *    > 13 pair plugboard
 * 
 */
void testPlugboard();

/**
 * Function which, given a plugboard filepath will 
 * check whether the error given by Plugboard::checkArg 
 * method has code equal to exp_error_code
 * - increments subtest_count, test_count.
 * - if test is passed -> increments test_passed.
 * - outputs test results
 */
void testPlugboardCheckArg(const char* arg);



/**
 * Function which, given a plugboard filepath with
 * correct configuration, constructs a Plugboard and 
 * makes it step through rangre [0,25]
 * - increments test_count, subtest_count
 * - if all inputs map to a value in range [0,25] and 
 *   no two inputs map to the same output, increments
 *   test_passed.
 * - outputs test results
 */
void testPlugboardStep(const char* arg);

#endif
