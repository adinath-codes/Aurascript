#pragma once
#include "lexer.h"
#include "object.h"
#include <memory>
#include <vector>

class Statements : public ObjectOutline {
private:
  /* data */
public:
  virtual ~Statements() = default;
  virtual Token tokenLiteral() {
    Token tok;
    return Token();
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
  std::shared_ptr<ObjectOutline> exp;

  Token tokenLiteral() override {
    Token tok;
    return tok;
  }
  OBJECT_TYPES type() override { return OBJECT_TYPES::LOWKEY_STATEMENT; }
  std::string viewValue() override { return ident + " = " + exp->viewValue(); }
};

// YAP STATEMENT
class YapBranch : public Statements {
public:
  std::shared_ptr<ObjectOutline> exp;

  Token tokenLiteral() override {
    Token tok;
    return tok;
  }
  OBJECT_TYPES type() override { return OBJECT_TYPES::YAP_STATEMENT; }
  std::string viewValue() override { return "yap " + exp->viewValue() + " fr"; }
};

// BLOCK STATEMENT (hold instructions)
class BlockBranch : public Statements {
public:
  std::vector<std::shared_ptr<ObjectOutline>> statements;
  OBJECT_TYPES type() override { return OBJECT_TYPES::BLOCK_STATEMENT; }
  std::string viewValue() { return "{...BLOCK OF CODE...}"; }
};

// CONDITIONAL STATEMENT
class SusBranch : public Statements {
public:
  std::shared_ptr<ObjectOutline> condition;
  std::shared_ptr<BlockBranch> ifBody;
  std::shared_ptr<BlockBranch> elseBody;

  OBJECT_TYPES type() override { return OBJECT_TYPES::SUS_STATEMENT; }
  std::string viewValue() override { return "sus (...) { ... }"; }
};

// LOOPING STATEMENT
class GrindingBranch : public Statements {
public:
  std::shared_ptr<ObjectOutline> condition;
  std::shared_ptr<BlockBranch> body;

  OBJECT_TYPES type() override { return OBJECT_TYPES::GRINDING_STATEMENT; }
  std::string viewValue() override { return "{...WHILE LOOP RUNNING...}"; }
};
// JUMP STATEMENT
class AST {

public:
  std::vector<std::shared_ptr<ObjectOutline>> branches;
};
