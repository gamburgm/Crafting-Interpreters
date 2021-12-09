#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "token.h"

using namespace std;

class Scanner {
  private:
    istream &src;
    vector<shared_ptr<Token>> toks{};
    int line{1};
    bool hadError{false};

    void scanToken();

    void addToken(TokenType, string);
    void addToken(TokenType, string, literal_t);

    void lex_string();
    void lex_number(char);
    void lex_identifier(char);

    char advance();
    bool match(char);
    char peek();
    char peekNext();
    bool isAtEnd() const;

    static const map<string, TokenType> keywords;

  public:
    Scanner(istream &s) : src(s) {}
    // TODO should I use a reference here or something?
    vector<shared_ptr<Token>> scanTokens();
    bool hadScannerError();
};
