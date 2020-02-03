#include "Expression.h"

std::string Expression::toString() {
    return "Expression toString not implemented.\n";
}

Expression::~Expression() {
    for (size_t i = 0; i < params.size(); i++) {
        delete params.at(i);
    }
    if (_operator != nullptr) { delete _operator; }
}