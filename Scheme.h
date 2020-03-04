#pragma once

#include "Token.h"
#include <vector>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>

class Scheme {
public:
    Scheme(const Token& id) {
        schemeID = new Token(id);
    }
    Scheme() {
        schemeID = nullptr;
    }
    ~Scheme() {
        if (schemeID != nullptr) { delete schemeID; }
        for (size_t i = 0; i < ids.size(); i++) {
            delete ids.at(i);
        }
    }

    void setSchemeID(const Token& id){
        if (id.getTokenType() != TokenType::ID){ throw std::invalid_argument("Non-ID token passed to setSchemeID"); }
        schemeID = new Token(id);
    }

    void addIdToScheme(const Token& id) {
        if (id.getTokenType() != TokenType::ID) { throw std::invalid_argument("Non-ID token passed to addIdToScheme"); }
        ids.push_back(new Token(id));
    }

    std::vector<Token*>::const_iterator begin() const {
        return ids.cbegin();
    }

    std::vector<Token*>::const_iterator end() const {
        return ids.cend();
    }

    Token getSchemeId();
    std::vector<Token*>* getIdVector() { return &ids; }
    std::string toString();

private:
    Token* schemeID;
    std::vector<Token*> ids;
};