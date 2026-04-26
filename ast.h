#include "lexer.h"
#include <memory>
#include <vector>
class Program {
private:
  std::vector<std::shared_ptr<LowkeyBranch>> branches;

public:
};

class Statements {
private:
  /* data */
public:
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
class Expr {
private:
  /* data */
public:
  Expr(/* args */);
  ~Expr();
};

class Ident {
private:
  /* data */
public:
  Ident(/* args */);
  ~Ident();
};
