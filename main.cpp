// TODO: AI FLAGGED
#include "lexer.h"
#include <iostream>
#include <string>

// Helper to print token types nicely
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

int main() {
  std::cout << "--- BOOTING ENGINE ---" << std::endl;

  std::string srcCode = "lowkey aVariable becomes 100 fr";
  Lexer lex(srcCode);

  Token tok = lex.nextToken();

  std::cout << "FIRST TOKEN TRIGGERED: " << tokenTypeToString(tok.type)
            << std::endl;

  while (tok.type != TokenTypes::GG) {
    std::cout << "OUTPUT: " << tokenTypeToString(tok.type) << " \t| LITERAL: ["
              << tok.literal << "]" << std::endl;

    tok = lex.nextToken();
  }

  std::cout << "--- ENGINE SHUTDOWN ---" << std::endl;
  return 0;
}
