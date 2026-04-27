#pragma once
#include "lexer.h"
#include <memory>
#include <vector>

class Statements {
private:
  /* data */
public:
  virtual ~Statements() = default;
  virtual Token tokenLiteral() {
    Token tok;
    return tok;
  }
};
// ASSIGNMENT STATEMENT
class LowkeyBranch : public Statements {
private:
  /* data */
public:
  //   Token token;
  std::string token;
  //   std::shared_ptr<Ident> ident;
  std::string ident;
  //   std::shared_ptr<Expr> value;
  std::string exp;

  Token tokenLiteral() override {
    Token tok;
    return tok;
  }
};

// CONDITIONAL STATEMENT

// LOOPING STATEMENT

// JUMP STATEMENT
class Program {

public:
  std::vector<std::shared_ptr<LowkeyBranch>> branches;
};
