#pragma once

#include "Token.h"
#include <exception>
#include <vector>
#include <string>
#include <sstream>

class Fact {
public:
    Fact(const Token& id) {
        factID = new Token(id);
    }
    ~Fact() {
        delete factID;
    }

    void setFactId(const Token& id){
        if (id.getTokenType() != TokenType::ID) { throw std::invalid_argument("Attempted to set fact ID with token that is not an ID."); }
        factID = new Token(id);
    }

    void addString(std::string fact){
        factStrings.push_back(fact);
    }

    const std::vector<std::string>* getFacts() const {
        return &factStrings;
    }

    std::vector<std::string>* getFactStringList() {
        return &factStrings;
    }

    std::string getID() const {
        return factID->getTokenStr();
    }

    std::string toString();

private:
    Token* factID;
    std::vector<std::string> factStrings;
};