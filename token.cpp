#include <string>
#include "token.h"

using namespace std;

string getTokenType(TokenType t) {
  return string(TOKEN_TYPE_STRS[t]);
}

string Token::toString() {
  return getTokenType(type) + " " + lexeme + " "; // + literal, somehow
}
