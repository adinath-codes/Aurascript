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
      std::cout << "[BUSTED]: divisor value can't be 0\n";
      return GLOBAL_NULL_OBJ;
    }
    return std::make_shared<IntObject>(leftVal / rightVal);
  case TokenTypes::SAME_SAME:
    if (leftVal == rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  case TokenTypes::GREATER_THAN:
    if (leftVal > rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  case TokenTypes::LESSER_THAN:
    if (leftVal < rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  case TokenTypes::GREATER_THAN_SAME:
    if (leftVal >= rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  case TokenTypes::LESSER_THAN_SAME:
    if (leftVal <= rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  case TokenTypes::NOT_SAME_SAME:
    if (leftVal != rightVal)
      return GLOBAL_TRUE_OBJ;
    else
      return GLOBAL_FALSE_OBJ;
  default:
    break;
  }
  return GLOBAL_NULL_OBJ;
}

t_Obj_ptr Evaluator(t_Obj_ptr node, Env &env) {
  if (!node) {
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::INTEGER_OBJ ||
      node->type() == OBJECT_TYPES::BOOL_OBJ ||
      node->type() == OBJECT_TYPES::STRING_OBJ) {
    return node;
  }

  if (node->type() == OBJECT_TYPES::IDENT_OBJ) {
    auto identNode = std::dynamic_pointer_cast<IdentObject>(node);
    t_Obj_ptr savedVal = env.get(identNode->value);
    if (savedVal == nullptr) {
      std::cout << "[BUSTED]: variable " << node->viewValue()
                << " not found!!\n";
      return GLOBAL_NULL_OBJ;
    }
    return savedVal;
  }

  if (node->type() == OBJECT_TYPES::LOWKEY_STATEMENT) {
    auto lkBranch = std::dynamic_pointer_cast<LowkeyBranch>(node);
    t_Obj_ptr val = Evaluator(lkBranch->exp, env);
    if (val != nullptr) {
      env.set(lkBranch->ident, val);
    }
    return val;
  }

  if (node->type() == OBJECT_TYPES::YAP_STATEMENT) {
    auto yapStatem = std::dynamic_pointer_cast<YapBranch>(node);
    t_Obj_ptr evaledExp = Evaluator(yapStatem->exp, env);
    if (evaledExp != nullptr && evaledExp->type() != OBJECT_TYPES::NULL_OBJ) {
      std::cout << evaledExp->viewValue() << std::endl;
    }
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::INFIX_OBJ) {
    auto infix = std::dynamic_pointer_cast<InfixNode>(node);
    t_Obj_ptr left = Evaluator(infix->Left, env);
    t_Obj_ptr right = Evaluator(infix->Right, env);

    if (left->type() == OBJECT_TYPES::INTEGER_OBJ &&
        right->type() == OBJECT_TYPES::INTEGER_OBJ) {
      return evalMathExp(left, infix->operatorType, right);
    } else {
      std::cout << "[RUNTIME ERROR]: Math operations require two numbers.\n";
      return GLOBAL_NULL_OBJ;
    }
  }

  return GLOBAL_NULL_OBJ;
}

int main() {
  std::cout << "--- BOOTING ENGINE ---\n";
  Env env;

  std::string srcCode = "yap 10 + 5 > 10 fr yap 100 != 100 fr";

  std::cout << "[SOURCE CODE]:\n" << srcCode << "\n\n";

  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();

  std::cout << "--- PARSED CODE ---\n\n";
  for (const auto &branch : parsedCode) {
    std::cout << "---------------------------------\n";

    // 1. THE X-RAY SCANNER (Check what type of node this is)
    if (branch->type() == OBJECT_TYPES::LOWKEY_STATEMENT) {
      auto lkBranch = std::dynamic_pointer_cast<LowkeyBranch>(branch);
      std::cout << "[NODE TYPE]: LOWKEY_BRANCH\n"
                << "[IDENTIFIER]: " << lkBranch->ident << "\n"
                << "[INNER MATH]: " << lkBranch->exp->viewValue() << "\n";
    } else if (branch->type() == OBJECT_TYPES::YAP_STATEMENT) {
      auto yapBranch = std::dynamic_pointer_cast<YapBranch>(branch);
      std::cout << "[NODE TYPE]: YAP_STATEMENT\n"
                << "[INNER EXP]: " << yapBranch->exp->viewValue() << "\n";
    }

    // 2. RUN THE ENGINE
    std::cout << "\n[EVALUATOR OUTPUT]:\n";
    Evaluator(branch, env); // If it's a yap statement, it prints here!

    // 3. CHECK THE RAM (Only if we just saved a variable)
    if (branch->type() == OBJECT_TYPES::LOWKEY_STATEMENT) {
      auto lkBranch = std::dynamic_pointer_cast<LowkeyBranch>(branch);
      t_Obj_ptr savedVal = env.get(lkBranch->ident);
      if (savedVal != nullptr) {
        std::cout << "\n[RAM STATE]: " << lkBranch->ident << " = "
                  << savedVal->viewValue() << "\n";
      }
    }

    std::cout << "---------------------------------\n\n";
  }

  std::cout << "--- ENGINE SHUTDOWN ---\n";
  return 0;
}