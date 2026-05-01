#pragma once
#include "ast.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct LowkeyBranch;
using t_TreeVect = std::vector<std::shared_ptr<ObjectOutline>>;

std::string tokenTypeToString(TokenTypes type) {
  switch (type) {
  case TokenTypes::LOWKEY:
    return "LOWKEY";
  case TokenTypes::IDENTIFIER:
    return "IDENTIFIER";
  case TokenTypes::BECOMES:
    return "BECOMES";
  case TokenTypes::NUMBER:
    return "NUMBER";
  case TokenTypes::STRING:
    return "STRING";
  case TokenTypes::CAP:
    return "CAP";
  case TokenTypes::NOCAP:
    return "NOCAP";
  case TokenTypes::FR:
    return "FR";
  case TokenTypes::GHOST:
    return "GHOST";
  case TokenTypes::BADVIBES:
    return "BADVIBES";
  case TokenTypes::GG:
    return "GG";
  default:
    return "OTHER_TOKEN";
  }
}

class Parser {

private:
  std::string sourceCode =
      "lowkey aVariable becomes 100 fr lowkey bVariable becomes 200 fr";
  Lexer lex;
  t_TreeVect branchedTree;
  // std::shared_ptr<LowkeyBranch> lkBranch;

public:
  Token currTok, nextTok;
  Env env;
  Parser(const std::string &srcCode) : sourceCode(srcCode), lex(sourceCode) {
    setNextToksToParse();
    setNextToksToParse();
  }

  void setNextToksToParse() {
    currTok = nextTok;
    nextTok = lex.nextToken();
  }
  const std::shared_ptr<NullObject> GLOBAL_NULL_OBJ =
      std::make_shared<NullObject>();
  const std::shared_ptr<BoolObject> GLOBAL_TRUE_OBJ =
      std::make_shared<BoolObject>(true);
  const std::shared_ptr<BoolObject> GLOBAL_FALSE_OBJ =
      std::make_shared<BoolObject>(false);
  t_Obj_ptr ObjectEvaluator() {
    // IDENTIFIER EVAL
    if (currTok.type == TokenTypes::IDENTIFIER) {
      return std::make_shared<IdentObject>(currTok.literal);
    }
    // BOOL EVAL
    if (currTok.type == TokenTypes::NOCAP) {
      return GLOBAL_TRUE_OBJ;
    }
    if (currTok.type == TokenTypes::CAP) {
      return GLOBAL_FALSE_OBJ;
    }
    // STRING EVAL
    else if (currTok.literal.length() > 1 && currTok.literal.front() == '"' &&
             currTok.literal.back() == '"') {
      const std::string pureString =
          currTok.literal.substr(1, currTok.literal.length() - 2);
      return std::make_shared<StringObject>(pureString);
    } else {
      try {
        // NUMBER EVAL
        long long num = std::stoll(currTok.literal);
        return std::make_shared<IntObject>(num);
      } catch (std::string err) {
        // NULL EVAL
        std::cout << "[WARNING]:" << err;
        return GLOBAL_NULL_OBJ;
      }
    }
  }

  int getPriority(TokenTypes type) {
    switch (type) {
    case TokenTypes::BECOMES:
      return 5;

    case TokenTypes::SAME_SAME:
    case TokenTypes::GREATER_THAN:
    case TokenTypes::LESSER_THAN:
    case TokenTypes::GREATER_THAN_SAME:
    case TokenTypes::LESSER_THAN_SAME:
    case TokenTypes::NOT_SAME_SAME:
      return 7;
    case TokenTypes::HASAURA:
    case TokenTypes::LOSEAURA:
      return 10;
    case TokenTypes::STACKED:
    case TokenTypes::RATIOED:
      return 20;

    default:
      return 0;
    }
  }

  t_Obj_ptr parseExp(int prevPower) {
    auto leftNode = ObjectEvaluator();
    if (!leftNode) {
      return nullptr;
    }
    setNextToksToParse();
    while (getPriority(currTok.type) > prevPower) {
      // FOREG: IF IT IS MULT THEN NEW INFIX NODE IS CREATED
      Token opTok = currTok;
      setNextToksToParse();
      auto infixNode = std::make_shared<InfixNode>();
      infixNode->Left = leftNode;
      infixNode->Operator = opTok.literal;
      infixNode->operatorType = opTok.type;
      // RECURSION:
      int nextPower = getPriority(opTok.type);
      if (currTok.type == TokenTypes::BECOMES) {
        nextPower -= 1;
      }
      infixNode->Right = parseExp(nextPower);
      leftNode = infixNode;
    }
    return leftNode;
  }
  // LOWKEY BRANCH
  std::shared_ptr<LowkeyBranch> parseLowkeyBranch() {
    // lowkey -> identifier (aVar) -> becomes/'=' -> exp -> fr::: lowekey
    // aVarbecomes 56+89 fr
    auto lkb = std::make_shared<LowkeyBranch>();
    lkb->token = tokenTypeToString(TokenTypes::LOWKEY);
    setNextToksToParse();
    if (currTok.type != TokenTypes::IDENTIFIER) {
      return nullptr;
    }
    lkb->ident = currTok.literal;
    setNextToksToParse();
    if (currTok.type != TokenTypes::BECOMES) {
      return nullptr;
    }
    setNextToksToParse();
    switch (currTok.type) {
    case (TokenTypes::NUMBER):
    case (TokenTypes::CAP):
    case (TokenTypes::NOCAP):
    case (TokenTypes::STRING):
    case (TokenTypes::IDENTIFIER):
      break;
    default:
      return nullptr;
    }
    lkb->exp = parseExp(0);
    if (currTok.type != TokenTypes::FR) { // TODO: add or ghost
      return nullptr;
    }
    setNextToksToParse();
    return lkb;
  }
  // YAP BRANCH
  std::shared_ptr<YapBranch> parseYapBranch() {
    auto yapNode = std::make_shared<YapBranch>();
    setNextToksToParse();
    yapNode->exp = parseExp(0);
    if (currTok.type != TokenTypes::FR) {
      std::cout
          << "[SYNTAX BUSTED]: Bruh, you forgot the 'fr' to end your yap.\n";
      return nullptr;
    }
    setNextToksToParse();

    return yapNode;
  }
  // BLOCK BRANCH
  std::shared_ptr<BlockBranch> parseBlockBranch() {
    auto block = std::make_shared<BlockBranch>();
    setNextToksToParse();

    while (currTok.type != TokenTypes::RBRACE &&
           currTok.type != TokenTypes::GG) {

      t_Obj_ptr stmt = parseStatement();

      if (stmt != nullptr) {
        block->statements.push_back(stmt);
      } else {
        setNextToksToParse();
      }
    }
    return block;
  }
  // SUS BRANCH
  std::shared_ptr<SusBranch> parseSusBranch() {
    auto susNode = std::make_shared<SusBranch>();
    setNextToksToParse();
    if (currTok.type != TokenTypes::LPAREN) {
      std::cout << "[SYNTAX BUSTED]: Bruh , you forgot the '(' after 'sus'"
                << std::endl;
      return nullptr;
    }
    setNextToksToParse();
    susNode->condition = parseExp(0);
    if (currTok.type != TokenTypes::RPAREN) {
      std::cout << "[SYNTAX BUSTED]: Expected '{' to start the sus block"
                << std::endl;
      return nullptr;
    }
    susNode->ifBody = parseBlockBranch();
    if (currTok.type == TokenTypes::RBRACE) {
      setNextToksToParse();
    }
    if (currTok.type == TokenTypes::FLOP) {
      setNextToksToParse();
      if (currTok.type != TokenTypes::LBRACE) {
        std::cout << "[SYNTAX BUSTED]: Expected '{' after 'flop'.\n";
        return nullptr;
      }
      susNode->elseBody = parseBlockBranch();
      if (currTok.type == TokenTypes::RBRACE) {
        setNextToksToParse();
      }
    }
    return susNode;
  }
  // GRINDING BRANCH
  std::shared_ptr<GrindingBranch> parseGrindingBranch() {
    auto grindNode = std::make_shared<GrindingBranch>();
    setNextToksToParse();
    if (currTok.type != TokenTypes::LPAREN) {
      std::cout << "[SYNTAX BUSTED]: '(' is missing in the conditional part of "
                   "the grinding loop"
                << std::endl;
      return nullptr;
    }
    setNextToksToParse();
    grindNode->condition = parseExp(0);
    if (currTok.type != TokenTypes::RPAREN) {
      std::cout << "[SYNTAX BUSTED]: ')' is missing in the conditional part of "
                   "the grinding loop"
                << std::endl;
      return nullptr;
    }
    setNextToksToParse();

    if (currTok.type != TokenTypes::LBRACE) {
      std::cout << "[SYNTAX BUSTED]: '{' is missing in the conditional part of "
                   "the grinding loop"
                << std::endl;
      return nullptr;
    }

    grindNode->body = parseBlockBranch();
    if (currTok.type != TokenTypes::RBRACE) {
      std::cout << "[SYNTAX BUSTED]: '}' is missing in the conditional part of "
                   "the grinding loop"
                << std::endl;
      return nullptr;
    }
    return grindNode;
  }
  t_Obj_ptr parseStatement() {
    switch (currTok.type) {
    case TokenTypes::LOWKEY:
      return parseLowkeyBranch();

    case TokenTypes::YAP:
      return parseYapBranch();

    case TokenTypes::SUS:
      return parseSusBranch();

    case TokenTypes::KEEPGRINDING:
      return parseGrindingBranch();

    default:
      return nullptr;
    }
  }

  t_TreeVect parseProgram() {
    while (currTok.type != TokenTypes::GG) {

      // Same exact logic! Just route it.
      t_Obj_ptr stmt = parseStatement();

      if (stmt != nullptr) {
        branchedTree.push_back(stmt);
      } else {
        setNextToksToParse();
      }
    }
    return branchedTree;
  }
};
