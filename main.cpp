#include "lib/env.h"
#include "lib/parser.h"
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::stringstream myBuffer;
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
      // printf("%s\n", evaledExp->viewValue().c_str());
      myBuffer << evaledExp->viewValue() << "\n";
    }
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::BLOCK_STATEMENT) {
    auto block = std::dynamic_pointer_cast<BlockBranch>(node);
    for (const auto &Statement : block->statements) {
      Evaluator(Statement, env);
    }
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::SUS_STATEMENT) {
    auto susNode = std::dynamic_pointer_cast<SusBranch>(node);
    t_Obj_ptr condResult = Evaluator(susNode->condition, env);
    if (condResult == GLOBAL_TRUE_OBJ) {
      Evaluator(susNode->ifBody, env);
    } else {
      Evaluator(susNode->elseBody, env);
    }
    return GLOBAL_NULL_OBJ;
  }

  if (node->type() == OBJECT_TYPES::GRINDING_STATEMENT) {
    auto grindNode = std::dynamic_pointer_cast<GrindingBranch>(node);
    while (true) {

      t_Obj_ptr condResult = Evaluator(grindNode->condition, env);

      if (condResult == nullptr) {
        std::cout << "[RUNTIME BUSTED]: Loop condition evaluated to a ghost "
                     "pointer.\n";
        break;
      }

      if (condResult != GLOBAL_TRUE_OBJ) {
        break;
      }
      Evaluator(grindNode->body, env);
    }

    return GLOBAL_NULL_OBJ;
  }
  return GLOBAL_NULL_OBJ;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "HELP:\n"
              << "use aura <filename>.aura to run the file" << std::endl;
    return 0;
  }
  std::string filename = argv[1];
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "[FATALITY]: could not find/open the file named" << filename
              << std::endl;
    return 0;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string srcCode = buffer.str();

  Env env;
  Parser par(srcCode);
  t_TreeVect parsedCode = par.parseProgram();
  // STARTING TIME AFTER PARSING (since most langauges like python do
  // pre-warmed) inorder to give accurate RUNTIME between python and auraScript
  auto startTime = std::chrono::high_resolution_clock::now();
  for (const auto &branch : parsedCode) {
    Evaluator(branch, env);
  }
  auto endTime = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> TotalRunTime = endTime - startTime;
  // auto msRunTime =
  //     std::chrono::duration_cast<std::chrono::milliseconds>(TotalRunTime)
  //         .count();
  std::cout << myBuffer.str();
  std::cout << "\n[AURA ENGINE]: Process finished in " << std::fixed
            << std::setprecision(4) << TotalRunTime.count() << "ms.\n";
  return 0;
}