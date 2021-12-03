#include <cstdio>
#include <iostream>

using namespace std;

void runFile(char *);
void runPrompt();

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cout << "Usage: jlox [script]" << endl;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}

void runFile(char *filename) {
}

void runPrompt() {
}
