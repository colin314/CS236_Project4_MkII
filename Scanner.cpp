#include "Scanner.h"

std::vector<Token> Scanner::Tokenize() {
    std::vector<Token> tokenVec = std::vector<Token>();
    char character = '\0';
    while (_input->get(character)) {
        if (character == '\n') {
            lineNum++;
            continue;
        }
        if (std::isblank(character)) {
            continue;
        }
        tokenVec.push_back(readCharacter(character));
    }

    tokenVec.push_back(Token(TokenType::_EOF, "", lineNum));

    return tokenVec;
}

Token Scanner::readCharacter(char& character) {

    if (std::isalpha(character)) {
        return evaluateAlpha(character);
    }

    switch (character) {
    case ',':
        return Token(TokenType::COMMA, ",", lineNum);
    case '.':
        return Token(TokenType::PERIOD, ".", lineNum);
    case '?':
        return Token(TokenType::Q_MARK, "?", lineNum);
    case '(':
        return Token(TokenType::LEFT_PAREN, "(", lineNum);
    case ')':
        return Token(TokenType::RIGHT_PAREN, ")", lineNum);
    case '*':
        return Token(TokenType::MULTIPLY, "*", lineNum);
    case '+':
        return Token(TokenType::ADD, "+", lineNum);
    case ':':
        return evaluateColon();
    case '\'':
        return evaluateStr(character);
    case '#':
        return evaluateComment(character);
    default:
        return Token(TokenType::UNDEFINED, std::string(1, character), lineNum);
    }
}

Token Scanner::evaluateColon() {
    if (_input->peek() == '-') {
        _input->ignore();
        return Token(TokenType::COLON_DASH, ":-", lineNum);
    }
    else {
        return Token(TokenType::COLON, ":", lineNum);
    }
}

Token Scanner::evaluateAlpha(char& character) {
    std::ostringstream sstr;
    sstr << character;

    while (std::isalnum(_input->peek())) {
        _input->get(character);
        sstr << character;
    }

    std::string id = sstr.str();

    if (id == "Schemes") { return Token(TokenType::SCHEMES, id, lineNum); }
    else if (id == "Facts") { return Token(TokenType::FACTS, id, lineNum); }
    else if (id == "Rules") { return Token(TokenType::RULES, id, lineNum); }
    else if (id == "Queries") { return Token(TokenType::QUERIES, id, lineNum); }
    else { return Token(TokenType::ID, id, lineNum); }

}

Token Scanner::evaluateStr(char& character) {
    std::ostringstream sstr;
    int strLineNum = lineNum;

    sstr << character;

    while (_input->get(character)) {
        sstr << character;
        if (character == '\'') {
            if (_input->peek() == '\'') {
                sstr << (char)_input->get();
            }
            else {
                return Token(TokenType::STRING, sstr.str(), strLineNum);
            }
        }
        if (character == '\n') lineNum++;
    }

    //EOF reached

    return Token(TokenType::UNDEFINED, sstr.str(), strLineNum);

}

Token Scanner::evaluateComment(char& character) {
    bool blockComment = false;
    int commentLineNum = lineNum;
    std::ostringstream sstr;
    sstr << character;

    if (_input->peek() == '|') {
        sstr << (char)_input->get();
        blockComment = true;
    }

    while (_input->get(character)) {
        if (blockComment) {
            sstr << character;
            if (character == '\n') lineNum++;
            if (character == '|' && _input->peek() == '#') {
                sstr << (char)_input->get();
                return Token(TokenType::COMMENT, sstr.str(), commentLineNum);
            }
        }
        else {
            if (character != '\n') {
                sstr << character;
            }
            else {
                lineNum++;
                return Token(TokenType::COMMENT, sstr.str(), commentLineNum);
            }
        }
    }

    return Token(TokenType::UNDEFINED, sstr.str(), commentLineNum);
}