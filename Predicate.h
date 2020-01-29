#pragma once

#include <string>
#include "Token.h"
#include "Parameter.h"
#include <vector>
#include <sstream>

class Predicate {
public:
    Predicate(const Token& id) {
        this->id = new Token(id);
    }
    ~Predicate() 
    {
        delete id;
        for (size_t i = 0; i < parameters.size(); i++)
        {
            delete parameters.at(i);
        }
        
    }

    std::vector<Parameter*>* getParameters() {
        return &parameters;
    }

private:
    Token* id;
    std::vector<Parameter*> parameters;
};

