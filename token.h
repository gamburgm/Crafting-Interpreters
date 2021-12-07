#include <string>

using namespace std;

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
  // single-character tokens
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // one or two character tokens
  BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

  // literals
  IDENTIFIER, STRING, NUMBER,

  // keywords
  AND, CLASS, ELSE, FALSE_BOOL, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE_BOOL, VAR, WHILE,

  END_OF_FILE,
};

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

string getTokenType(TokenType);

class Token {
  private:
    const TokenType type;
    const string lexeme;
    const any literal;
    const int line;

  public:
    Token(TokenType t, string lex, any lit, int line) : type(t), lexeme(lex), literal(lit), line(line) {}
    string toString();
};

#endif
