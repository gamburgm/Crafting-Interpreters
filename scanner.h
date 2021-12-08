#include <iostream>
#include <memory>
#include <vector>
#include "token.h"

using namespace std;

class Scanner {
  private:
    const istream &src;
    vector<shared_ptr<Token>> toks{};
    int line{1};

    // TODO this should be re-organized
    bool isAtEnd() const;
    void scanToken();
    void addToken(TokenType, string);
    void addToken(TokenType, string, literal_t);
    bool match(char);
    void lex_string();
    void lex_number(char);
    void lex_identifier(char);

    char advance();
    char peek();
    char peekNext();

    static const map<string, TokenType> keywords = {
      {string("and"),    TokenType::AND},
      {string("class"),  TokenType::CLASS},
      {string("else"),   TokenType::ELSE},
      {string("false"),  TokenType::FALSE_BOOL},
      {string("for"),    TokenType::FOR},
      {string("fun"),    TokenType::FUN},
      {string("if"),     TokenType::IF},
      {string("nil"),    TokenType::NIL},
      {string("or"),     TokenType::OR},
      {string("print"),  TokenType::PRINT},
      {string("return"), TokenType::RETURN},
      {string("super"),  TokenType::SUPER},
      {string("this"),   TokenType::THIS},
      {string("true"),   TokenType::TRUE_BOOL},
      {string("var"),    TokenType::VAR},
      {string("while"),  TokenType::WHILE},
    };

  public:
    Scanner(istream &s) : src(s) {}
    // TODO should I use a reference here or something?
    vector<shared_ptr<Token>> scanTokens();
};
