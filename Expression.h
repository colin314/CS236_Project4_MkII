#pragma once

#include "Parameter.h"
#include <string>
#include <sstream>

class Parameter;

class Expression {
public:
    Expression() {
        leftParam = nullptr;
        _operator = nullptr;
        rightParam = nullptr;
    }
    ~Expression();

    std::string toString();

    //void setLeftParam(const Parameter &leftParam);

private:
    Parameter* leftParam;
    Token* _operator;
    Parameter* rightParam;

};

