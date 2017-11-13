// -*- C++ -*-
#include "errors.h"
#include <cstring>

Error::Error(char* filename,int filetype)
  : code(NO_ERROR){
  this->filetype = filetype;
  strcpy(this->filename, filename);  
}



Error Error:: setCode(int error_code, const char* info){
  code = error_code;
  strcpy(this->info, info);
  return *this;
}



const char* Error::getFiletype(){
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
    stream << "Insufficient number of parameters";
    break;

  case INVALID_INPUT_CHARACTER:
    stream << "(input characters must be upper case letters A-Z)!";
    break;

  case INVALID_INDEX:
    stream << "Invalid index in " << error.getFiletype() << error.getFilename();
    break;

  case NON_NUMERIC_CHARACTER:
    stream << "Non-numeric character in " << error.getFiletype() << error.getFilename();
    break;

  case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
    stream << "Impossible plugboard configuration in " << error.getFiletype() << error.getFilename();
    break;

  case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
    stream << "Incorrect number of parameters in " << error.getFiletype() << error.getFilename();
    break;

  case INVALID_ROTOR_MAPPING:
    stream << "Invalid rotor mapping in " << error.getFiletype() << error.getFilename();
    break;

  case NO_ROTOR_STARTING_POSITION:
    stream << "No rotor starting position in " << error.getFiletype() << error.getFilename();
    break;

  case INVALID_REFLECTOR_MAPPING:
    stream << "Invalid reflector mapping in " << error.getFiletype() << error.getFilename();
    break;

  case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
    stream << "Incorrect "<< error.getInfo();
    stream << " number of parameters in ";
    stream << error.getFiletype() << error.getFilename();
    break;

  case ERROR_OPENING_CONFIGURATION_FILE:
    stream << "Error opening configuration " << error.getFiletype() << error.getFilename();
    break;

  case NO_ERROR: stream << "No error";
    break;

  default:
    stream << "Wrong error code. Fix your code !";
    break;
  }
  return stream;
}
