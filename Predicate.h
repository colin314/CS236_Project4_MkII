#pragma once

#include <string>
#include "Token.h"
#include "Parameter.h"
#include <vector>
#include <sstream>

class Predicate {
public:
    Predicate() {
        id = nullptr;
        leftParen = nullptr;
        rightParen = nullptr;
    }
    ~Predicate() 
    {
        if (id         != nullptr) { delete id; }
        if (leftParen  != nullptr) { delete leftParen; }
        if (rightParen != nullptr) { delete rightParen; }
    }

    std::string toString();

private:
    Token* id;
    Token* leftParen;
    std::vector<Parameter> parameters;
    Token* rightParen;
};

