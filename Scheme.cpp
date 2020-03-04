#include "Scheme.h"

std::string Scheme::getSchemeId() const {
    return schemeID->getTokenStr();
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

