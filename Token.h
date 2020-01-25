#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "TokenType.h"

class Token
{
public:
    Token(TokenType type, std::string tokenStr, int lineNum) {
        _type = type;
        _tokenStr = tokenStr;
        _lineNum = lineNum;
    }
    ~Token() {}

    TokenType getTokenType() {
        return _type;
    }
    std::string getTokenStr() {
        return _tokenStr;
    }
    int getLineNum() {
        return _lineNum;
    }
    std::string toString() const {
        std::ostringstream osstr;
        osstr << '(' << _type << ",\"" << _tokenStr << "\"," << _lineNum << ")";
        return osstr.str();
    }
    inline friend std::ostream& operator<<(std::ostream& os, const Token& tkn) {
        os << tkn.toString();
        return os;
    }
private:
    TokenType _type;
    int _lineNum;
    std::string _tokenStr;
};





