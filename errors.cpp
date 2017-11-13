// -*- C++ -*-


#include "errors.h"
#include <cstring>

Error::Error(char* filename,int object_type)
  : code(NO_ERROR){
  this->object_type = object_type;
  strcpy(this->filename, filename);  
}



Error Error:: setCode(int error_code){
  code = error_code;
  return *this;
}



const char* Error::getObject(){
  switch(object_type){
  case PLUGBOARD:
    return "plugboard file ";
  case REFLECTOR:
    return "reflector file ";
  case ROTOR:
    return "rotor file ";
  case ROTORPOSITIONS:
    return "rotor positions file ";
  default:
    return "";
  }
}

std::ostream& operator << (std::ostream& stream, Error &error){
  switch(error.getCode()){
  case 1: stream << "Insufficient number of parameters";
    break;
  case 2: stream << "Invalid input character";
    break;
  case 3: stream << "Invalid index in " << error.getObject() << error.getFilename();
    break;
  case 4: stream << "Non-numeric character in file " << error.getObject() << error.getFilename();
    break;
  case 5: stream << "Impossible plugboard configuration in file " << error.getObject() << error.getFilename();
    break;
  case 6: stream << "Incorrect number of parameters in file " << error.getObject() << error.getFilename();
    break;
  case 7: stream << "Invalid rotor mapping in file " << error.getObject() << error.getFilename();
    break;
  case 8: stream << "No rotor starting position in file " << error.getObject() << error.getFilename();
    break;
  case 9: stream << "Invalid reflector mapping in file " << error.getObject() << error.getFilename();
    break;
  case 10: stream << "Incorrect number of reflector parameters in file " << error.getObject() << error.getFilename();
    break;
  case 11: stream << "Error opening configuration file " << error.getObject() << error.getFilename();
    break;
  case 0: std:: cerr << "No error";
    break;
  default: stream << "Wrong error code. Fix your code !";
    break;
  }
  return stream;
}
