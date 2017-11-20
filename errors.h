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
 

/* file types */
#define PLUGBOARD 1
#define REFLECTOR 2
#define ROTOR 3
#define ROTOR_POS 4
#define NO_OBJECT 0


#define MAX_ARRAY_LENGTH 80
#define ALPHABET_SIZE 26


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
  char filename[MAX_ARRAY_LENGTH];
  int filetype;
  char info[MAX_ARRAY_LENGTH];
  bool code_set;
public:

  /**
   * Constructor. Used for errors that occur
   * while reading a file.
   * - initializes the filename
   *   and the filetype.
   * - initializes code to NO_ERROR
   * - initializes code_set to false
   */
  Error(char* filename, int filetype);

  /** 
   * Constructor. Used for errors that are 
   * not directly affiliated with a config file.
   * - initializes the code to error_code
   * - initializes the object type to NO_OBJECT
   * - initializes code_set to true
   */
  Error(int error_code)
    :code(error_code), filetype(NO_OBJECT), code_set(true){}
  
  /**
   * Method which given an error_code,
   * - if code has not been set:
   *   > sets the Error's code to error_code,
   *   >copies param info into this->info
   * - returns this object.
   */
  Error setCode(int error_code , const char* info = "\0");
  
  /**
   * Method which returns the error's code
   */
  int getCode(){return code;}

  /**
   * Method which returns the error' filename
   * as a constant char array.
   */
  char* getFilename(){return filename;}

  

  /**
   * Method which returns the error's filetype 
   * as a char array.
   */
  const char* getFiletypeString();


  /**
   * Method which returns the error's filetype
   * as a string;
   */
  int getFiletype(){return filetype;}
  
  /**
   * Method which returns the error's info as 
   * a constant array
   */
  const char* getInfo(){return info;}

  friend std:: ostream& operator <<(std::ostream& stream, Error &error);

  
};


std::ostream& operator << (std::ostream& stream, Error &error);



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



#endif


