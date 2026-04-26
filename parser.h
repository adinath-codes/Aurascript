#include "lexer.h"
#include <string>
using std::string;
class parser {
private:
  std::string sourceCode =
      "lowkey aVariable becomes 100 fr lowkey bVariable becomes 200 fr";
  Lexer lex;

public:
  Token currTok, nextTok;
  parser(std::string srcCode) : sourceCode(srcCode), lex(sourceCode) {
    nextTok = lex.nextToken();
  }
  void parseProgram() {
    while (nextTok.type != TokenTypes::GG) {
      currTok = nextTok;
      nextTok = lex.nextToken();
    }
  }
};
