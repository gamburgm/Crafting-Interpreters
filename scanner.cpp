#include "scanner.h"
#include "util.h"

using namespace std;

bool Scanner::isAtEnd() const {
  return src.peek() != EOF;
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  return expected == advance();
}

void Scanner::addToken(TokenType t, string lex) {
  addToken(t, lex, nullptr);
}

void Scanner::addToken(TokenType t, string lex, literal_t lit) {
  toks.add(shared_ptr<Token>(new Token(t, lex, lit, line)));
}

char Scanner::advance() {
  return src.get();
}

char Scanner::peek() {
  return src.peek();
}

// FIXME odds this works?
char Scanner::peekNext() {
  src.seekg(1, src.cur);
  char c = src.peek();
  src.seekg(-1, src.cur);
  return c;
}

void Scanner::lex_string() {
  stringstream ss('"', ios::in | ios::out); // FIXME this is wrong for multiple reasons

  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    ss << advance();
  }

  if (isAtEnd()) {
    error(line, "Unterminated string.");
    return;
  }

  ss << advance(); // the closing "

  string val(ss.str());
  addToken(TokenType::STRING, val, val.substr(1, val.length() - 2));
}

void Scanner::lex_number(char first_digit) {
  stringstream ss(first_digit, ios::in | ios::out); // FIXME this is wrong for multiple reasons
  while isdigit(peek()) {
    ss << advance();
  }

  if (peek() == '.' && isdigit(peekNext(src))) {
    ss << advance();
  }

  while (isdigit(peek())) {
    ss << advance();
  }

  string val(ss.str());
  addToken(TokenType::NUMBER, val, stod(val));
}

void Scanner::lex_identifier(char first_c) {
  stringstream ss(first_c, ios::in | ios::out); // FIXME this is wrong for multiple reasons
  while (isalnum(peek())) {
    ss << advance();
  }

  TokenType type;
  string val(ss.str());

  auto type_iter = keywords.find(val);
  if (type == keywords.end()) {
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
        add_token(TokenType::BANG_EQUAL, s);
      } else {
        add_token(TokenType::BANG, s);
      }
      break;
    case '=':
      if (match('=')) {
        s.push_back('=');
        add_token(TokenType::EQUAL_EQUAL, s);
      } else {
        add_token(TokenType::EQUAL, s);
      }
      break;
    case '<':
      if (match('=')) {
        s.push_back('=');
        add_token(TokenType::LESS_EQUAL, s);
      } else {
        add_token(TokenType::LESS, s);
      }
      break;
    case '>':
      if (match('=')) {
        s.push_back('=');
        add_token(TokenType::GREATER_EQUAL, s);
      } else {
        add_token(TokenType::GREATER, s);
      }
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(TokenType::SLASH, s);
      }
      break;
    // TODO should these case statements be on the same line?
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"': scan_string(); break;
    default:
      if (isdigit(c)) {
        lex_number(c);
      } else if (isalpha(c)) {
        lex_identifier(c);
      } else {
        // FIXME need to decide how I want to signal an error has occurred
        error(line, "Unexpected character.");
      }
  }

}

vector<shared_ptr<Token>> Scanner::scanTokens() {
  while (!isAtEnd()) {
    // we are at the beginning of the next lexeme
    scanToken();
  }

  // FIXME where does `line` come from?
  // TODO should I use `make_shared` or use the constructor as I am now?
  toks.push_back(shared_ptr<Token>(new Token(TokenType::END_OF_FILE, "", nullptr, line)));
  return toks;
}


