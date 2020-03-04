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
    Predicate(const Predicate& old) {
        id = new Token(*old.id);
        for (size_t i = 0; i < old.parameters.size(); i++) {
            parameters.push_back(old.parameters.at(i));
        }
    }
    ~Predicate() 
    {
        delete id;
        for (size_t i = 0; i < parameters.size(); i++)
        {
            delete parameters.at(i);
        }
        
    }

    std::string getId() {
        return id->getTokenStr();
    }

    std::vector<Parameter*>* getParameters() {
        return &parameters;
    }

    std::string toString();

private:
    Token* id;
    std::vector<Parameter*> parameters;
};

