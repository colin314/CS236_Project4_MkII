#include "Scheme.h"

Token Scheme::getSchemeId() {
    return *schemeID;
}

std::vector<Token> Scheme::getSchemeIds() {
    std::vector<Token> tokens;
    for (size_t i = 0; i < ids.size(); i++)
    {
        tokens.push_back(ids.at(i));
    }
    return tokens;
}

