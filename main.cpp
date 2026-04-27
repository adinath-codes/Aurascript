#include "lib/env.h"
#include "lib/parser.h"
#include <iostream>
#include <string>

int main() {
  std::cout << "--- BOOTING ENGINE ---" << std::endl;
  Env env;
  std::string srcCode = "lowkey aVariable becomes 100 fr";
  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();
  for (const auto &branch : parsedCode) {
    std::cout << "[BRANCH]:" << std::endl
              << "TOKEN: " << branch->token << "\n"
              << "IDENTIFIER: " << branch->ident << "\n"
              << "EXPRESSION: " << branch->exp << "\n";
    auto numObj = std::make_shared<IntObject>(std::stoll(branch->exp));
    env.set(branch->ident, numObj);
    std::cout << "[ENV]:" << branch->ident << ":"
              << env.get(branch->ident)->viewValue() << std::endl;
  }

  std::cout << "--- ENGINE SHUTDOWN ---" << std::endl;
  return 0;
}
