#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// FIXME should there be a newline here?  
#include "scanner.h"

using namespace std;

// TODO the runner family of functions should be modified to return error codes, or some processable error info.
//      the book uses a global variable (member of the main class) which I won't do for various reasons.
//      
void runFile(char *);
void runPrompt();
int run(istream &);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cout << "Usage: clox [script]" << endl;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }

  return 0;
}

void runFile(char *filepath) {
  ifstream f (filepath, ios::in);
  int err = run(f);
  f.close();

  if (err != 0) {
    exit(65);
  }
}

void runPrompt() {
  while (true) {
    cout << "> ";
    string line;
    getline(cin, line);

    if (line.empty()) {
      break;
    }

    auto ss = stringstream(line);
    run(ss);
  }
}

int run(istream &src) {
  // TODO how would I handle this pointer? how should I do this? make_shared?
  Scanner *s = new Scanner(src);
  auto toks = s->scanTokens();

  int res;
  if (s->hadScannerError()) {
    res = 1;
  } else {
    res = 0;
    for (auto const &t : toks) {
      cout << t->toString() << endl;
    }
  }

  delete s;
  return res;
}
