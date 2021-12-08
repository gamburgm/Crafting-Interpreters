#include <string>
#include <sstream>
#include "token.h"

using namespace std;

static const char *TOKEN_TYPE_STRS[] = {
  "LeftParen",
  "RightParen",
  "LeftBrace",
  "RightBrace",
  "Comma",
  "Dot",
  "Minus",
  "Plus",
  "Semicolon",
  "Slash",
  "Star",
  "Bang",
  "BangEqual",
  "Equal",
  "EqualEqual",
  "Greater",
  "GreaterEqual",
  "Less",
  "LessEqual",
  "Identifier",
  "String",
  "Number",
  "And",
  "Class",
  "Else",
  "False",
  "Fun",
  "For",
  "If",
  "Nil",
  "Or",
  "Print",
  "Return",
  "Super",
  "This",
  "True",
  "Var",
  "While",
  "End-of-file"
};

string getTokenType(TokenType t) {
  return string(TOKEN_TYPE_STRS[t]);
}

string Token::getLiteralString() {
  // to avoid nullptr falling into this case, a literal number only in NUMBER case
  if (holds_alternative<int>(literal) && type == TokenType::NUMBER) {
    return to_string(get<int>(literal));
  } else if (holds_alternative<string>(literal)) {
    return get<string>(literal);
  } else {
    return string("null");
  }
}

string Token::toString() {
  stringstream ss;
  ss << getTokenType(type) << " " << lexeme << " " << getLiteralString();

  return ss.str();
}
