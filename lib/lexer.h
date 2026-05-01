#pragma once

#include "opt.h"
#include <string>
using std::string;

enum class TokenTypes {
  // OPERATORS: =,+,-,*,/,\0
  BECOMES,
  HASAURA,
  LOSEAURA,
  STACKED,
  RATIOED,
  GG,
  // COMPARATOR: ==,>,<,<=,>=,!=
  SAME_SAME,
  GREATER_THAN,
  LESSER_THAN,
  GREATER_THAN_SAME,
  LESSER_THAN_SAME,
  NOT_SAME_SAME,
  // KEYWORDS: let,true,false,if,else,while,print,return,\n
  LOWKEY,
  SUS,
  FLOP,
  KEEPGRINDING,
  YAP,
  FLEX,
  GHOST,
  // DATATYPES : number,bool,string (OPTIMSED WITH BIN)
  NUMBER,
  NOCAP,
  CAP,
  STRING,
  // OTHERS: ;,identifier,numbers,EOF, ILLEGAL(none of them)
  FR,
  IDENTIFIER,
  BADVIBES
};
struct Token {
  TokenTypes type;
  string literal;
};

class Lexer {
private:
  string input;
  int position;
  int readPos;
  char currChar;
  bool isValidLetter(char ch) {
    // return ((ch|32)-'a')<=('z'-'a')
    return IS_VALID_CHAR_LUT[(unsigned char)ch] &
           IS_ALPHA; // Used a LUT for high optimisation
  };
  bool isValidDigit(char ch) {
    return (unsigned char)(ch - '0') <= 9;
    // return ch >= '0' && ch <= '9';
    // return IS_VALID_CHAR_LUT[(unsigned char)ch] &
    //  IS_NUMBER; // Used a LUT for high optimisation
  };
  bool isWhiteSpace(char ch) {
    return IS_VALID_CHAR_LUT[(unsigned char)ch] & IS_WHITE_SPACE;
  }
  void skipWhiteSpace();
  string readWord();
  char peekChar();
  string readNumber();
  string readString();
  TokenTypes lookupWords(string identifier);

public:
  Token nextToken();
  void readNextChar();
  Lexer(string sourceCode);
};