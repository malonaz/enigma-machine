// -*- C++ -*-
#include "errors.h"
#include <cstring>

Error::Error(char* filename,int filetype)
  : code(NO_ERROR), code_set(false){
  this->filetype = filetype;
  strcpy(this->filename, filename);  
}



Error Error:: setCode(int error_code, const char* info){
  if (!code_set){
  code = error_code;
  strcpy(this->info, info);
  code_set = true;
  }
  return *this;
}



const char* Error::getFiletypeString(){
  switch(filetype){
  case PLUGBOARD:
    return "plugboard file ";
  case REFLECTOR:
    return "reflector file ";
  case ROTOR:
    return "rotor file ";
  case ROTOR_POS:
    return "rotor positions file ";
  default:
    return "";
  }
}

std::ostream& operator << (std::ostream& stream, Error &error){
  switch(error.getCode()){

  case INSUFFICIENT_NUMBER_OF_PARAMETERS:
    stream << "usage: enigma plugboard-file reflector-file (<rotor-file>* ";
    stream<< "rotor-positions)?";
    break;

  case INVALID_INPUT_CHARACTER:
    stream << "(input characters must be upper case letters A-Z)!";
    break;

  case INVALID_INDEX:
    stream << "Invalid index in " << error.getFiletypeString() << error.getFilename();
    break;

  case NON_NUMERIC_CHARACTER:
    stream << "Non-numeric character in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
    stream << "Impossible plugboard configuration in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
    stream << "Incorrect number of parameters in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case INVALID_ROTOR_MAPPING:
    stream << "Invalid rotor mapping in " << error.getFiletypeString() << error.getFilename();
    break;

  case NO_ROTOR_STARTING_POSITION:
    stream << "No rotor starting position in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case INVALID_REFLECTOR_MAPPING:
    stream << "Invalid reflector mapping in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
    stream << error.getInfo();
    stream << " number of parameters in ";
    stream << error.getFiletypeString() << error.getFilename();
    break;

  case ERROR_OPENING_CONFIGURATION_FILE:
    stream << "Error opening configuration " << error.getFiletypeString() << error.getFilename();
    break;

  case NO_ERROR: stream << "No error";
    break;

  default:
    stream << "Wrong error code. Fix your code !";
    break;
  }
  stream << std::endl;
  return stream;
}
