#include "Rule.h"

std::string Rule::toString() {
    std::stringstream sstr;
    sstr << headPred->toString() << " :- ";
    for (size_t i = 0; i < predicates.size(); i++) {
        sstr << predicates.at(i)->toString();
        if (i < predicates.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ".";
    return sstr.str();
}