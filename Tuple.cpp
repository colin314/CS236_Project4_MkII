#include "Tuple.h"

string Tuple::toString() const {
    stringstream sstr;
    sstr << "(";
    for (size_t i = 0; i < values.size(); i++) {
        sstr << values.at(i);
        if (i < values.size() - 1) {
            sstr << ",";
        }
    }
    sstr << ")";
    return sstr.str();
}