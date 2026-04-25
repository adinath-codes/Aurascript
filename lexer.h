#pragma once
#include <string>

enum class TokenTypes {
    BECOMES,GG,HASAURA,LOSEAURA,STACKED,RATIOED, //OPERATORS: =,+,-,*,/,\0,
    BADVIBES //ILLEGAL(none of them)
};

struct Token {
TokenTypes type;
std::string literal;
};

class Lexer{
    private:
        std::string input;
        int position;
        int readPos;
        char currChar;
    public:
        Lexer(std::string sourceCode);
        void readNextChar();
        void skipWhiteSpace();
        Token nextToken();

        bool isLetter(char ch);
        void readIdentifiers();
};