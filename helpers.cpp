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

int getNextPair(int &num1, int &num2, std::ifstream &config_stream){
  if (!(config_stream >> num1))
    return 0;
  if (!(config_stream >> num2))
    return 1;
  return 2;
}
