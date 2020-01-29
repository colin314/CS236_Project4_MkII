#pragma once

#include "Token.h"
#include <vector>

class HeadPredicate{
public:
    HeadPredicate(const Token& id) {
        predID = new Token(id);
    }
    ~HeadPredicate() {
        delete predID;
    }

    std::vector<Token>* getIdList() {
        return &idList;
    }

private:
    Token* predID;
    std::vector<Token> idList;
};