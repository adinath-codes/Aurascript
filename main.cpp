#include "lib/env.h"
#include "lib/parser.h"
#include <iostream>
#include <string>
const std::shared_ptr<NullObject> GLOBAL_NULL_OBJ =
    std::make_shared<NullObject>();
const std::shared_ptr<BoolObject> GLOBAL_TRUE_OBJ =
    std::make_shared<BoolObject>(true);
const std::shared_ptr<BoolObject> GLOBAL_FALSE_OBJ =
    std::make_shared<BoolObject>(false);
t_Obj_ptr Evaluator(const std::string &exp) {
  // BOOL EVAL
  if (exp == "nocap") {
    return GLOBAL_TRUE_OBJ;
  } else if (exp == "cap") {
    return GLOBAL_FALSE_OBJ;
  }
  // STRING EVAL
  else if (exp.length() > 1 && exp.front() == '"' && exp.back() == '"') {
    const std::string pureString = exp.substr(1, exp.length() - 2);
    return std::make_shared<StringObject>(pureString);
  } else {
    try {
      // NUMBER EVAL
      long long num = std::stoll(exp);
      return std::make_shared<IntObject>(num);
    } catch (std::string err) {
      // NULL EVAL
      std::cout << "[WARNING]:" << err;
      return GLOBAL_NULL_OBJ;
    }
  }
}

int main() {
  std::cout << "--- BOOTING ENGINE ---" << std::endl;
  Env env;
  std::string srcCode = "lowkey aVariable = nocap fr";
  std::cout << "[SOURCE CODE]:" << srcCode << std::endl << std::endl;
  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();
  std::cout << "--- PARSED CODE ---" << std::endl << std::endl;
  for (const auto &branch : parsedCode) {
    std::cout << "[BRANCH]:" << std::endl
              << "TOKEN: " << branch->token << "\n"
              << "IDENTIFIER: " << branch->ident << "\n"
              << "EXPRESSION: " << branch->exp << "\n\n";
    env.set(branch->ident, Evaluator(branch->exp));
    std::cout << "[ENV]:\n"
              << branch->ident << "=" << env.get(branch->ident)->viewValue()
              << std::endl
              << std::endl;
  }

  std::cout << "--- ENGINE SHUTDOWN ---" << std::endl;
  return 0;
}
