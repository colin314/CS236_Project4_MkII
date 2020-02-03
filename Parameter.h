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
    void setString(const Token& str) {
        if (str.getTokenType() != STRING) { throw std::invalid_argument("Non-String token given to StringParam.\n"); }
        if (_str != nullptr) { delete _str; }
        _str = new Token(str);
    }

private:
    Token* _str;
};

class IdParam : public Parameter {
public:
    IdParam() {
        paramType = TokenType::ID;
        _id = nullptr;
    }
    ~IdParam() {
        if (_id != nullptr) { delete _id; }
    }

    std::string toString() { return _id->getTokenStr(); }
    void setId(const Token& id) {
        if (id.getTokenType() != ID) { throw std::invalid_argument("Non-ID token given to IdParam.\n"); }
        if (_id != nullptr) { delete _id; }
        _id = new Token(id);
    }

private:
    Token* _id;
};

class ExpParam : public Parameter {
public:
    ExpParam() {
        paramType = TokenType::EXPRESSION;
        _exp = nullptr;
    }
    ~ExpParam();

    void setExpression(Expression* expression) { _exp = expression; }
    Expression* getExpression() { return _exp; }

    std::string toString();

private:
    Expression* _exp;
};