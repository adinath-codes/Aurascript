#include "lexer.h"
#include <memory>

class Statements {
private:
  /* data */
public:
  virtual Token tokenLiteral() {
    Token tok;
    return tok;
  }
  Statements(/* args */);
  ~Statements();
};
// ASSIGNMENT STATEMENT
class LowkeyStatement : public Statements {
private:
  /* data */
public:
  Token name;
  std::shared_ptr<Ident> ident;
  std::shared_ptr<Expr> value;

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
