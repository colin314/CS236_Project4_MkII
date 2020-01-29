#pragma once

#include <string>
#include "HeadPredicate.h"
#include "Predicate.h"
#include <vector>

class Rule {
public:
    Rule() {
        headPred = nullptr;
    }
    ~Rule() {
        if (headPred != nullptr) { delete headPred; }
        for (size_t i = 0; i < predicates.size(); i++)
        {
            delete predicates.at(i);
        }
    }

    void setHeatPred(HeadPredicate* headPredicate){
        headPred = headPredicate;
    }

    std::vector<Predicate*>* getPredicateList() {
        return &predicates;
    }

    std::string toString();

private:
    HeadPredicate* headPred;
    std::vector<Predicate*> predicates;
};

