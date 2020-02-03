#include "Predicate.h"

std::string Predicate::toString() {
    std::stringstream sstr;
    sstr << id->getTokenStr() << '(';
    for (size_t i = 0; i < parameters.size(); i++) {
        sstr << parameters.at(i)->toString();
        if (i < parameters.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ')';
    return sstr.str();
}