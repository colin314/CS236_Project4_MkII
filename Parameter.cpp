#include "Parameter.h"

std::string ExpParam::toString() {
    return _exp->toString();
}

ExpParam::~ExpParam() {
    if (_exp != nullptr) { delete _exp; }
}