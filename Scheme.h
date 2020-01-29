#include "Token.h"
#include <vector>
#include <exception>

class Scheme {
public:
    Scheme(const Token& id) {
        schemeID = new Token(id);
    }
    Scheme() {
        schemeID = nullptr;
    }
    ~Scheme() {
        if (schemeID != nullptr) { delete schemeID; }
    }

    void setSchemeID(const Token& id){
        if (id.getTokenType() != TokenType::ID){ throw std::invalid_argument("Non-ID token passed to setSchemeID"); }
        schemeID = new Token(id);
    }

    void addIdToScheme(Token id) {
        if (id.getTokenType() != TokenType::ID) { throw std::invalid_argument("Non-ID token passed to addIdToScheme"); }
        ids.push_back(id);
    }

    std::vector<Token> getSchemeIds();
    Token getSchemeId();
    std::vector<Token>* getIdVector() { return &ids; }

private:
    Token* schemeID;
    std::vector<Token> ids;
};