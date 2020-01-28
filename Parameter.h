#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Expression.h"

class Expression;

class Parameter {
public:
    Parameter() {
        paramType = TokenType::UNDEFINED;
    }
    ~Parameter() {}

    TokenType getType() { return paramType; }
    virtual std::string toString() = 0;

protected:
    TokenType paramType;

};

class StringParam : public Parameter {
public:
    StringParam() {
        paramType = TokenType::STRING;
        _str = nullptr;
    }
    ~StringParam() {
        if (_str != nullptr) { delete _str; }
    }

    std::string toString() { return _str->getTokenStr(); }
private:
    Token* _str;
};

class IdParam : public Parameter {
public:
    IdParam() {
        paramType = TokenType::ID;
        id = nullptr;
    }
    ~IdParam() {
        if (id != nullptr) { delete id; }
    }

    std::string toString() { return id->getTokenStr(); }

private:
    Token* id;
};

class ExpParam : public Parameter {
public:
    ExpParam() {
        paramType = TokenType::EXPRESSION;
        _exp = nullptr;
    }
    ~ExpParam();

    std::string toString();

private:
    Expression *_exp;
};