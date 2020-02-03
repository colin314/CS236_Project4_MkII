#include "Expression.h"

std::string Expression::toString() {
    std::stringstream sstr;
    sstr << "(";
    sstr << params.at(0)->toString();
    sstr << _operator->getTokenStr();
    sstr << params.at(1)->toString();
    sstr << ")";
    return sstr.str();
}

Expression::~Expression() {
    for (size_t i = 0; i < params.size(); i++) {
        delete params.at(i);
    }
    if (_operator != nullptr) { delete _operator; }
}