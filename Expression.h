#pragma once

#include "Parameter.h"
#include <string>
#include <sstream>
#include <vector>

using std::vector;

class Parameter;

class Expression {
public:
    Expression() {
        _operator = nullptr;
    }
    ~Expression();

    std::string toString();

    vector<Parameter*>* getParams() { return &params; }
    Token** getOperatorToken() { return &_operator; }

private:
    vector<Parameter*> params;
    Token* _operator;

};

