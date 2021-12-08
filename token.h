#include <string>
#include <variant>

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

using literal_t = variant<int, string, nullptr_t>;

class Token {
  private:
    const TokenType type;
    const string lexeme;
    const literal_t literal;
    const int line;

    string getLiteralString();

  public:
    Token(TokenType t, string lex, literal_t lit, int lin) : type(t), lexeme(lex), literal(lit), line(lin) {}
    string toString();
};

#endif
