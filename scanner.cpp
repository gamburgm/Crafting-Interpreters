#include <sstream>
#include "scanner.h"
#include "util.h"

using namespace std;

const map<string, TokenType> Scanner::keywords = {
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

bool Scanner::isAtEnd() const {
  return src.peek() == EOF;
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  return expected == advance();
}

void Scanner::addToken(TokenType t, string lex) {
  addToken(t, lex, nullptr);
}

void Scanner::addToken(TokenType t, string lex, literal_t lit) {
  shared_ptr<Token> tok = make_shared<Token>(t, lex, lit, line);
  toks.push_back(tok);
}

char Scanner::advance() {
  return src.get();
}

char Scanner::peek() {
  return src.peek();
}

char Scanner::peekNext() {
  src.seekg(1, src.cur);
  char c = src.peek();
  src.seekg(-1, src.cur);
  return c;
}

void Scanner::lex_string() {
  stringstream ss;
  ss << '"';

  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    ss << advance();
  }

  if (isAtEnd()) {
    hadError = true;
    error(line, "Unterminated string.");
    return;
  }

  ss << advance(); // the closing "

  string val(ss.str());
  addToken(TokenType::STRING, val, val.substr(1, val.length() - 2));
}

void Scanner::lex_number(char first_digit) {
  stringstream ss;
  ss << first_digit;

  while (isDigit(peek())) {
    ss << advance();
  }

  if (peek() == '.' && isdigit(peekNext())) {
    ss << advance();
  }

  while (isDigit(peek())) {
    ss << advance();
  }

  string val(ss.str());
  addToken(TokenType::NUMBER, val, stod(val));
}

void Scanner::lex_identifier(char first_c) {
  stringstream ss;
  ss << first_c;

  while (isAlphaNumeric(peek())) {
    ss << advance();
  }

  TokenType type;
  string val(ss.str());

  auto type_iter = keywords.find(val);
  if (type_iter == keywords.end()) {
    type = TokenType::IDENTIFIER;
  } else {
    type = type_iter->second;
  }

  addToken(type, val);
}

void Scanner::scanToken() {
  char c = advance();

  string s(1, c);

  switch (c) {
    case '(': addToken(TokenType::LEFT_PAREN, s);  break;
    case ')': addToken(TokenType::RIGHT_PAREN, s); break;
    case '{': addToken(TokenType::LEFT_BRACE, s);  break;
    case '}': addToken(TokenType::RIGHT_BRACE, s); break;
    case ',': addToken(TokenType::COMMA, s);       break;
    case '.': addToken(TokenType::DOT, s);         break;
    case '-': addToken(TokenType::MINUS, s);       break;
    case '+': addToken(TokenType::PLUS, s);        break;
    case ';': addToken(TokenType::SEMICOLON, s);   break;
    case '*': addToken(TokenType::STAR, s);        break;
    case '!':
      if (match('=')) {
        s.push_back('=');
        addToken(TokenType::BANG_EQUAL, s);
      } else {
        addToken(TokenType::BANG, s);
      }
      break;
    case '=':
      if (match('=')) {
        s.push_back('=');
        addToken(TokenType::EQUAL_EQUAL, s);
      } else {
        addToken(TokenType::EQUAL, s);
      }
      break;
    case '<':
      if (match('=')) {
        s.push_back('=');
        addToken(TokenType::LESS_EQUAL, s);
      } else {
        addToken(TokenType::LESS, s);
      }
      break;
    case '>':
      if (match('=')) {
        s.push_back('=');
        addToken(TokenType::GREATER_EQUAL, s);
      } else {
        addToken(TokenType::GREATER, s);
      }
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(TokenType::SLASH, s);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"': lex_string(); break;
    default:
      if (isDigit(c)) {
        lex_number(c);
      } else if (isAlpha(c)) {
        lex_identifier(c);
      } else {
        hadError = true;
        error(line, "Unexpected character.");
      }
  }

}

const TokenVec &Scanner::scanTokens() {
  while (!isAtEnd()) {
    // we are at the beginning of the next lexeme
    scanToken();
  }

  shared_ptr<Token> tok = make_shared<Token>(TokenType::END_OF_FILE, "", nullptr, line);
  toks.push_back(tok);

  return toks;
}

bool Scanner::hadScannerError() {
  return hadError;
}
