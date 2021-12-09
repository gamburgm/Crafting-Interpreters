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

    static const map<string, TokenType> keywords;

  public:
    Scanner(istream &s) : src(s) {}
    // TODO should I use a reference here or something?
    vector<shared_ptr<Token>> scanTokens();
};
