#include <iostream>
#include "util.h"

using namespace std;

// TODO should I use string here anyway? I lose the satisfaction of string literals.

void error(int line, const char *message) {
  report(line, "", message);
}

void report(int line, const char *where, const char *message) {
  cout << "[ line " << line << "] Error" << where << ": " << message << endl;
}

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         c == '_';
}

bool isAlphaNumeric(char c) {
  return isDigit(c) || isAlpha(c);
}
