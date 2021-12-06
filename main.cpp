#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// TODO the runner family of functions should be modified to return error codes, or some processable error info.
//      the book uses a global variable (member of the main class) which I won't do for various reasons.
//      
void runFile(char *);
void runPrompt();
void run(istream &);
void error(int, string);
void report(int, string, string);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cout << "Usage: jlox [script]" << endl;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }

  return 0;
}

void runFile(char *filepath) {
  ifstream f (filepath, ios::in);
  run(f);
  f.close();
  // TODO if run returned an error, exit with error code 65.
}

void runPrompt() {
  while (true) {
    cout << "> ";
    string line;
    getline(cin, line);

    if (line.empty()) {
      break;
    }

    auto lstream = stringstream(line);
    run(lstream);
    // TODO if run returned an error, ignore it. You'd reset the 'global variable' here.
  }
}

// TODO this function should be modified to return error (codes?), or some processable error info.
//      the book uses a global variable (member of the main class) which I won't do for various reasons.
void run(istream &src) {
  // scanner = Scanner(src);
  // vector toks = scanner.getTokens();
  // for token in tokens:
  //     cout << token << endl;
}

void error(int line, string message) {
  report(line, string(""), message);
}

void report(int line, string where, string message) {
  cout << "[ line " << line << "] Error" << where << ": " << message << endl;
}
