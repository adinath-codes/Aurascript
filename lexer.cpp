#include "lexer.h"
#include "opt.h"
Lexer::Lexer(std::string sourceCode){
        input=sourceCode;
         position=0;//Old position
         readPos=0;//curr reading position
         currChar=0;//curr reading character
};

void Lexer::readNextChar(){
    if(readPos<input.length()){
        currChar = input[readPos];
    }else{
        currChar=0; // NO char , ie currChar -> '\0'
    }
    position=readPos;
    readPos++;
};

void Lexer::skipWhiteSpace(){
    if(currChar==' ' || currChar=='\t' || currChar=='\r' || currChar=='\n'){
        readNextChar();
    }
}

bool Lexer::isLetter(char ch){
    // return ((ch|32)-'a')<=('z'-'a')
    return (bool)(IS_ALPHA_LUT[(unsigned char)ch]);// Used a LUT for high optimisation 
}
Token Lexer::nextToken(){
    Token tok;
    skipWhiteSpace();
    switch (currChar)
    {
    case '=':
        tok.type=TokenTypes::BECOMES;
        tok.literal = '=';
        break;
    
    case '+':
        tok.type=TokenTypes::HASAURA;
        tok.literal = '+';
        break;
    
    case '-':
        tok.type=TokenTypes::LOSEAURA;
        tok.literal = '-';
        break;
    
    case '*':
        tok.type=TokenTypes::STACKED;
        tok.literal = '*';
        break;
    
    case '/':
        tok.type=TokenTypes::RATIOED;
        tok.literal = '/';
        break;

    case '\0':
        tok.type = TokenTypes::GG;
        tok.literal = '\0';
        break;

    default:
        tok.type = TokenTypes::BADVIBES;
        tok.literal = std::string(1,currChar);
        break;
    }
    readNextChar();
    return tok;
}
