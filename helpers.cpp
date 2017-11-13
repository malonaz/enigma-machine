#include "helpers.h"

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
