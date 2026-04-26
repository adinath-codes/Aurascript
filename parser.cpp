#include "ast.h"
#include "lexer.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using std::string;
using t_TreeVect = std::vector<std::shared_ptr<LowkeyBranch>>;

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
  case TokenTypes::FR:
    return "FR";
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
  Parser(const std::string &srcCode) : sourceCode(srcCode), lex(sourceCode) {
    setNextToksToParse();
    setNextToksToParse();
  }
  void setNextToksToParse() {
    currTok = nextTok;
    nextTok = lex.nextToken();
  }
  std::shared_ptr<LowkeyBranch> parseLowkeyBranch() {
    // lowkey -> identifier (aVar) -> becomes/'=' -> exp -> fr::: lowekey aVar
    // becomes 56+89 fr
    auto lkb = std::make_shared<LowkeyBranch>();
    lkb->token = tokenTypeToString(TokenTypes::LOWKEY);
    setNextToksToParse();
    if (currTok.type != TokenTypes::IDENTIFIER) {
      std::cout
          << "[BUSTED]:Yo! <lowkey> should be followed by an <identifier>";
      return nullptr;
    }
    lkb->ident = currTok.literal;
    setNextToksToParse();
    if (currTok.type != TokenTypes::BECOMES) {
      std::cout
          << "[BUSTED]:Yo! <identifier> should be followed by an <becomes>";
      return nullptr;
    }
    setNextToksToParse();
    if (currTok.type != TokenTypes::NUMBER) {
      std::cout << "[BUSTED]:Yo! <identifier> only can become NUMBER for now ";
      return nullptr;
    }
    lkb->exp = currTok.literal;
    setNextToksToParse();

    if (currTok.type != TokenTypes::FR) {
      std::cout << "[BUSTED]:Yo! <becomes> should be followed by an <fr>";
      return nullptr;
    }

    setNextToksToParse();
    return lkb;
  }

  t_TreeVect parseProgram() {
    while (currTok.type != TokenTypes::GG) {
      switch (currTok.type) {
      case TokenTypes::LOWKEY: {
        std::shared_ptr<LowkeyBranch> lkBranchPtr = parseLowkeyBranch();
        if (lkBranchPtr != nullptr) {
          branchedTree.push_back(lkBranchPtr);
        }
        break;
      }
      default:
        setNextToksToParse();
        break;
      }
    }
    return branchedTree;
  }
};
