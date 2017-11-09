// -*- C++ -*-
#ifndef ERRORS_H
#define ERRORS_H
//

#include <set>
#include <cstring>

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


/**
 * ErrorReport. This class is used to represent error reports.
 * - it contains an error code
 * - it contains the file which caused the error
 */
class ErrorReport{
private:
  int error_code;
  char filename[50];

public:
  /**
   * Constructor. Initializes error code and filename members.
   */
  ErrorReport(int code, char *file)
    :error_code(code){
    strcpy(filename,file);
  }
  ErrorReport(char *file)
    :error_code(NO_ERROR){
    strcpy(filename,file);
  }
  ErrorReport(int code)
    :error_code(code){}
     

/**
   * Copy Constructor. Initializes error code and filename members.
   */
  ErrorReport(const ErrorReport &error_report)
    :error_code(error_report.error_code){
    strcpy(filename,error_report.filename);
  }
    
  
  // METHODS
  
  /**
   * method which returns error code
   */
  const int get_code(){return error_code;}


  /**
   * method which returns the file name 
   */
  char* get_filename(){return filename;}
  /**
   * method which sets this report's error code to code
   */
  void set_error_code(int code){error_code = code;}

  
  friend std::ostream& operator << (std::ostream& stream, ErrorReport& error_report);
  
};

std::ostream& operator << (std::ostream& stream, ErrorReport& error_report);



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

void print_error(int error_code);


#endif
