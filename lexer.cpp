#include "lib/lexer.h"
#include <iostream>
#include <unordered_map>

using std::string;
using std::unordered_map;
static unordered_map<string, TokenTypes> keywords = {
    {"lowkey", TokenTypes::LOWKEY},
    {"nocap", TokenTypes::NOCAP},
    {"cap", TokenTypes::CAP},
    {"sus", TokenTypes::SUS},
    {"flop", TokenTypes::FLOP},
    {"keepgrinding", TokenTypes::KEEPGRINDING},
    {"yap", TokenTypes::YAP},
    {"flex", TokenTypes::FLEX},
    {"fr", TokenTypes::FR},
    {"ghosting", TokenTypes::GHOSTING},
    {"becomes", TokenTypes::BECOMES},
    {"hasaura", TokenTypes::HASAURA},
    {"loseaura", TokenTypes::LOSEAURA},
    {"stacked", TokenTypes::STACKED},
    {"rationed", TokenTypes::RATIOED}};

Lexer::Lexer(string sourceCode) {
  input = sourceCode;
  position = 0; // curr Pointer
  readPos = 0;  // reading position (it checks over and tells whether to take it
  currChar = 0; // curr reading character
  readNextChar();
};

void Lexer::readNextChar() {
  if (readPos < input.length()) {
    currChar = input[readPos];
  } else {
    currChar = 0; // NO char , ie currChar -> '\0'
  }
  position = readPos;
  readPos++;
};

string Lexer::readWord() {
  int startPos = position;
  while (isValidLetter(currChar)) {
    readNextChar();
  }
  return input.substr(startPos, position - startPos);
}

string Lexer::readNumber() {
  int startPos = position;
  while (isValidDigit(currChar)) {
    readNextChar();
  }
  return input.substr(startPos, position - startPos);
}

void Lexer::skipWhiteSpace() {
  while (currChar == ' ' || currChar == '\t' || currChar == '\n' ||
         currChar == '\r') {
    readNextChar();
  }
}

TokenTypes Lexer::lookupWords(string identifier) {
  if (keywords.count(identifier)) {
    return keywords[identifier];
  }
  return TokenTypes::IDENTIFIER;
}

Token Lexer::nextToken() {
  Token tok;
  skipWhiteSpace();
  switch (currChar) {
  case '=':
    tok.type = TokenTypes::BECOMES;
    tok.literal = "=";
    break;

  case '+':
    tok.type = TokenTypes::HASAURA;
    tok.literal = "+";
    break;

  case '-':
    tok.type = TokenTypes::LOSEAURA;
    tok.literal = "-";
    break;

  case '*':
    tok.type = TokenTypes::STACKED;
    tok.literal = "*";
    break;

  case '/':
    tok.type = TokenTypes::RATIOED;
    tok.literal = "/";
    break;

  case '\0':
    tok.type = TokenTypes::GG;
    tok.literal = "\0";
    break;

  default:
    if (isValidLetter(currChar)) {
      tok.literal = readWord();
      tok.type = lookupWords(tok.literal);
      return tok;
    } else if (isValidDigit(currChar)) {
      tok.literal = readNumber();
      tok.type = TokenTypes::NUMBER;
      return tok;
    } else {
      tok.type = TokenTypes::BADVIBES;
      tok.literal = string(1, currChar);
      readNextChar();
    }
    break;
  }
  readNextChar();
  return tok;
}
