#include "parser.h"
#include <iostream>
#include <string>

int main() {
  std::cout << "--- BOOTING ENGINE ---" << std::endl;

  std::string srcCode = "lowkey aVariable becomes 100 fr";
  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();
  for (const auto &branches : parsedCode) {
    std::cout << "[BRANCHES]:" << std::endl
              << "TOKEN: " << branches->token << "\n"
              << "IDENTIFIER: " << branches->ident << "\n"
              << "EXPRESSION: " << branches->exp << "\n";
  }

  std::cout << "--- ENGINE SHUTDOWN ---" << std::endl;
  return 0;
}
