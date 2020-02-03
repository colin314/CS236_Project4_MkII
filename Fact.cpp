#include "Fact.h"

std::string Fact::toString() {
    std::stringstream sstr;
    sstr << factID->getTokenStr() << "(";
    for (size_t i = 0; i < factStrings.size(); i++) {
        sstr << factStrings.at(i);
        if (i < factStrings.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ").";
    return sstr.str();
}