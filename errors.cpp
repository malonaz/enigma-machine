// -*- C++ -*-
#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include "errors.h"


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
  case 11: std::cerr << "Error opening configuraiton file";
    break;
  case 0: std:: cerr << "No error";
    break;
  default: std::cerr << "Wrong error code. Fix your code !";
    break;
  }
}




#endif
