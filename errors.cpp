// -*- C++ -*-

#include <iostream>
#include "errors.h"


std::ostream& operator << (std::ostream& stream, ErrorReport& error_report){
  switch(error_report.get_code()){
  case 1: stream << "Insufficient number of parameters";
    break;
  case 2: stream << "Invalid input character";
    break;
  case 3: stream << "Invalid index";
    break;
  case 4: stream << "Non numeric character in file " << error_report.get_filename();
    break;
  case 5: stream << "Impossible plugboard configuration";
    break;
  case 6: stream << "Incorrect number of parameters in plugboard file " << error_report.get_filename();
    break;
  case 7: stream << "Invalid rotor mapping";
    break;
  case 8: stream << "No rotor starting position";
    break;
  case 9: stream << "Invalid reflector mapping";
    break;
  case 10: stream << "Incorrect number of reflector parameters";
    break;
  case 11: stream << "Error opening configuration file";
    break;
  case 0: std:: cerr << "No error";
    break;
  default: stream << "Wrong error code. Fix your code !";
    break;
  }
  return stream;
}


bool invalid_index(int digit){
  if (digit <0 || digit > 25)
    return true;
  return false;
}

bool is_in_set(std::set<int> digits, int digit){
  if (digits.find(digit) != digits.end())
    return true;
  return false;
}


void print_error(int error_code){
  switch(error_code){
  case 1: std::cerr << "Insufficient number of parameters";
    break;
  case 2: std::cerr << "Invalid input character";
    break;
  case 3: std::cerr << "Invalid index";
    break;
  case 4: std::cerr << "Non numeric character";
    break;
  case 5: std::cerr << "Impossible plugboard configuration";
    break;
  case 6: std::cerr << "Incorrect number of plugboard parameters";
    break;
  case 7: std::cerr << "Invalid rotor mapping";
    break;
  case 8: std::cerr << "No rotor starting position";
    break;
  case 9: std::cerr << "Invalid reflector mapping";
    break;
  case 10: std::cerr << "Incorrect number of reflector parameters";
    break;
  case 11: std::cerr << "Error opening configuration file";
    break;
  case 0: std:: cerr << "No error";
    break;
  default: std::cerr << "Wrong error code. Fix your code !";
    break;
  }
  std::cout << std::endl;
}



