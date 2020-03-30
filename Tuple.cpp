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

bool operator< (const Tuple& t1, const Tuple& t2) {

    if (t1.values.size() < t2.values.size()) {
        for (size_t i = 0; i < t1.values.size(); i++) {
            if (t1.values.at(i) != t2.values.at(i)) {
                return t1.values.at(i) < t2.values.at(i);
            }
        }
    }
    else {
        for (size_t i = 0; i < t2.values.size(); i++) {
            if (t2.values.at(i) != t1.values.at(i)) {
                return t1.values.at(i) < t2.values.at(i);
            }
        }
    }
    bool rv = t1.values.size() < t2.values.size();
    return rv;
}