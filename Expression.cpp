#include "Expression.h"

std::string Expression::toString() {
    std::stringstream sstr;
    sstr << "(" << leftParam->toString() << _operator->getTokenStr() << rightParam->toString() << ")";
    return sstr.str();
}

Expression::~Expression() {
    if (leftParam != nullptr) { delete leftParam; }
    if (rightParam != nullptr) { delete rightParam; }
    if (_operator != nullptr) { delete _operator; }
}