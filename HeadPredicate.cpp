#include "HeadPredicate.h"

std::string HeadPredicate::toString() {
    std::stringstream sstr;
    sstr << predID->getTokenStr() << "(";
    for (size_t i = 0; i < idList.size(); i++) {
        sstr << idList.at(i)->getTokenStr();
        if (i < idList.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ")";
    return sstr.str();
}