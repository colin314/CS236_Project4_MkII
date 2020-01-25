#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include <fstream>
#include <cctype>

using std::cout;
using std::endl;

class Scanner
{
public:
    Scanner(char* inFile) {
        _input = new std::ifstream(inFile);
        lineNum = 1;
    }
    ~Scanner() {
        delete _input;
    }

    std::vector<Token> Tokenize();

private:
    std::ifstream* _input;
    int lineNum;

    Token readCharacter(char& character);
    Token evaluateColon();
    Token evaluateAlpha(char& character);
    Token evaluateStr(char& character);
    Token evaluateComment(char& character);
};


