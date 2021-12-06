#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void runFile(char *);
void runPrompt();
void run(istream &);

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
  }
}

void run(istream &src) {
}
