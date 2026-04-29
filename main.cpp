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
t_Obj_ptr evalMathExp(t_Obj_ptr left, TokenTypes opType, t_Obj_ptr right) {
  auto leftInt = std::dynamic_pointer_cast<IntObject>(left);
  auto rightInt = std::dynamic_pointer_cast<IntObject>(right);
  long long leftVal = leftInt->value;
  long long rightVal = rightInt->value;
  switch (opType) {
  case TokenTypes::HASAURA:
    return std::make_shared<IntObject>(leftVal + rightVal);

  case TokenTypes::LOSEAURA:
    return std::make_shared<IntObject>(leftVal - rightVal);

  case TokenTypes::STACKED:
    return std::make_shared<IntObject>(leftVal * rightVal);

  case TokenTypes::RATIOED:
    if (rightVal == 0) {
      std::cout << "[BUSTED]:divisor value can't be 0" << std::endl;
      return GLOBAL_NULL_OBJ;
    }
    return std::make_shared<IntObject>(leftVal / rightVal);
  default:
    break;
  }
  return GLOBAL_NULL_OBJ;
}
t_Obj_ptr Evaluator(t_Obj_ptr node) {
  if (!node) {
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::INTEGER_OBJ ||
      node->type() == OBJECT_TYPES::BOOL_OBJ ||
      node->type() == OBJECT_TYPES::STRING_OBJ) {
    return node;
  }
  if (node->type() == OBJECT_TYPES::INFIX_OBJ) {
    auto infix = std::dynamic_pointer_cast<InfixNode>(node);
    t_Obj_ptr left = Evaluator(infix->Left);
    t_Obj_ptr right = Evaluator(infix->Right);
    if (left->type() == OBJECT_TYPES::INTEGER_OBJ &&
        right->type() == OBJECT_TYPES::INTEGER_OBJ) {
      return evalMathExp(left, infix->operatorType, right);
    } else {
      std::cout << "[RUNTIME ERROR]: Math operations require two numbers."
                << std::endl;
      return GLOBAL_NULL_OBJ;
    }
  }
  return GLOBAL_NULL_OBJ;
}
int main() {
  std::cout << "--- BOOTING ENGINE ---" << std::endl;
  Env env;
  std::string srcCode = "lowkey aVariable becomes 100+20*10  fr";
  std::cout << "[SOURCE CODE]:" << srcCode << std::endl << std::endl;
  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();
  std::cout << "--- PARSED CODE ---" << std::endl << std::endl;
  for (const auto &branch : parsedCode) {
    std::cout << "[BRANCH]:" << std::endl
              << "TOKEN: " << branch->token << "\n"
              << "IDENTIFIER: " << branch->ident << "\n"
              << "EXPRESSION: " << branch->exp->viewValue() << "\n\n";
    env.set(branch->ident, Evaluator(branch->exp));
    std::cout << "[ENV]:\n"
              << branch->ident << "=" << env.get(branch->ident)->viewValue()
              << std::endl
              << std::endl;
  }

  std::cout << "--- ENGINE SHUTDOWN ---" << std::endl;
  return 0;
}
