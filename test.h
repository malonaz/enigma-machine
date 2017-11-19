// -*- C++ -*-
#ifndef TEST_H
#define TEST_H

#include "errors.h"

/**
 * This function runs a battery of tests:
 * 1) tests the plugboard class
 */
void test();


/**
 * This internal function compares two errors:
 * - if errors' codes are equal, increments test_passed.
 * - outputs test results
 */
void processError(Error error, Error exp_error);
#endif
