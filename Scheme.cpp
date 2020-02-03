#include "Scheme.h"

Token Scheme::getSchemeId() {
    return *schemeID;
}

std::string Scheme::toString() {
    std::stringstream sstr;
    sstr << schemeID->getTokenStr() << "(";
    for (size_t i = 0; i < ids.size(); ++i) {
        sstr << ids.at(i)->getTokenStr();
        if (i < ids.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ")";
    return sstr.str();
}

