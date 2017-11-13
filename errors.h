// -*- C++ -*-
#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <set>

/* error codes  */
#define INSUFFICIENT_NUMBER_OF_PARAMETERS		1
#define INVALID_INPUT_CHARACTER				2
#define INVALID_INDEX					3
#define NON_NUMERIC_CHARACTER				4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION		5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS	6
#define INVALID_ROTOR_MAPPING				7
#define NO_ROTOR_STARTING_POSITION			8
#define INVALID_REFLECTOR_MAPPING			9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS	10
#define ERROR_OPENING_CONFIGURATION_FILE		11
#define NO_ERROR					0
 

/* object types */
#define PLUGBOARD 101
#define REFLECTOR 102
#define ROTOR 103
#define ROTORPOSITIONS 104
#define NO_OBJECT 100


#define MAX_FILENAME_LENGTH 100

/**
 * Error. This class is used to represent an error.
 * An error is characterized by:
 * - an error code
 * - if error occured while reading an object config file
 *    o  the name of the file that caused the error
 *    o  the type of object the file was meant to config
 */

class Error{
private:
  int code;
  char filename[MAX_FILENAME_LENGTH];
  int object_type;

public:

  /**
   * Constructor. Used for errors that occur
   * while checking an argument for an object
   * constructor.
   * - initializes the filename
   *   and the object_type.
   * - initializes code to NO_ERROR
   */
  Error(char* filename, int object_type);

  /** 
   * Constructor. Used for errors that are 
   * not directly affiliated with a config file.
   * - initializes the code to error_code
   * - initializes the object type to NO_OBJECT
   */
  Error(int error_code)
    :code(error_code), object_type(NO_OBJECT){}
  
  /**
   * Method which given an error_code,
   * sets the Error's code to error_code and
   * returns this object.
   */
  Error setCode(int error_code);


  /**
   * Method which returns the error's code
   */
  int getCode(){return code;}

  /**
   * Method which returns the errors' filename
   */
  char* getFilename(){return filename;}


  /**
   * Method which returns the error's object type 
   * as a char array.
   */
  const char* getObject();

  friend std:: ostream& operator <<(std::ostream& stream, Error &error);

  
};


std::ostream& operator << (std::ostream& stream, Error &error);



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


