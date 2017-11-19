#include "helpers.h"
#include "errors.h"


int toInt(char c){
  return c-65;
}


char toChar(int n){
  return n+65;
}

int mod26(int n){
  while(n<0)
    n += 26;

  while(n>25)
    n -= 26;

  return n;
}



bool invalidIndex(int digit){
  if (digit <0 || digit > 25)
    return true;
  return false;
}

bool inSet(std::set<int> digits, int digit){
  if (digits.find(digit) != digits.end())
    return true;
  return false;
}

bool getNextPair(int &num1, int &num2, Error &error,
		 std::ifstream &config_stream){
  if (error.getCode() || !(config_stream >> num1))
    return false;
		   
  if (!(config_stream >> num2)){
    if (config_stream.eof()){
      if (error.getFiletype() == PLUGBOARD)
	error.setCode(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
      else
	error.setCode(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS, "(odd)");
    }
    return false;
  }
  return true;
}

