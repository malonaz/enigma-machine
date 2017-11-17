// -*- C++ -*-
#ifndef TEST_H
#define TEST_H

#include "plugboard.h"
#include "reflector.h"
#include "rotors.h"
#include "enigma.h"
#include <assert.h>


/* filepaths info */
#define MAX_FILEPATH_ARRAY  50
extern int test_count;
extern int subtest_count;
extern int passed_test;



void test();

/**
 * Method which will test the Plugboard class,
 * methods.
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
 *     o (3): 13th pair maps already mapped contact to invalid index -> (1) ??
 *     o (4): 10th pair connects a contact already connected, followed by non_numeric -> (1)
 *   > (2) then
       o (1) not possible!
 *     o (3): 5 integers where 5th is >25 -> (2)
 *     o (4): 5 integers followed by a non numeric char -> (2)
 *   > (3) then
 *     o (1): 13 pairs, where 12th pair contains int >25 & 13th pair maps to itself -> (3)
 *     o (2): 15 ints, where 3rd integer >25 -> (3)
 *     o (4): invalid index before non_numeric char -> (3)
 *   > (4) then 
 *     o (1): 4 pairs of entry. 1st pair has letters, 2nd pair maps to itself -> (4)
 *     o (2): 5 entries, 3rd int contains non num chars -> (4)
 *     o (3): 10 entries, 3rd contains non num chars, 4th contains invalid index -> (4)
 */
void testPlugboard();


/**
 * Method which, given a plugboard filepath and an 
 * expected error, will check whether the error 
 * given by Plugboard::checkArg function is equal
 * to expected. 
 * - increments subtest_count, test_count.
 * - if test is passed -> increments test_passed.
 */
void testPlugboardCheckArg(const char* arg);

void processError(Error error, Error exp_error);

#endif
