#pragma once

#include "Token.h"
#include "TokenType.h"
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <iostream>

using std::string;
using std::cout; using std::endl;

class DataLogger {
public:
    DataLogger() {
        parseStack = new std::stack<string>;
        outputQueue = new std::queue<Token>;
        schemesQueue = new std::queue<Token>;
        factsQueue = new std::queue<Token>;
        rulesQueue = new std::queue<Token>;
        queriesQueue = new std::queue<Token>;
    }
    ~DataLogger() {
        delete parseStack;
        delete outputQueue;
        delete schemesQueue;
        delete factsQueue;
        delete rulesQueue;
        delete queriesQueue;
    }

    string parse(std::vector<Token>* const &inputTokens);
private:
    std::stack<string>* parseStack;
    std::queue<Token>* outputQueue;
    std::queue<Token>* schemesQueue;
    std::queue<Token>* factsQueue;
    std::queue<Token>* rulesQueue;
    std::queue<Token>* queriesQueue;

    void parseDatalogProgram(std::vector<Token>::iterator& tokens);
    void parseSchemeList(std::vector<Token>::iterator& tokens);
    void parseFactList(std::vector<Token>::iterator& tokens);
    void parseRuleList(std::vector<Token>::iterator& tokens);
    void parseQueryList(std::vector<Token>::iterator& tokens);
    void parseScheme(std::vector<Token>::iterator& tokens);
    void parseFact(std::vector<Token>::iterator& tokens);
    void parseRule(std::vector<Token>::iterator& tokens);
    void parseQuery(std::vector<Token>::iterator& tokens);
    void parseHeadPredicate(std::vector<Token>::iterator& tokens);
    void parsePredicate(std::vector<Token>::iterator& tokens);
    void parsePredicateList(std::vector<Token>::iterator& tokens);
    void parseParameterList(std::vector<Token>::iterator& tokens);
    void parseStringList(std::vector<Token>::iterator& tokens);
    void parseIdList(std::vector<Token>::iterator& tokens);
    void parseParameter(std::vector<Token>::iterator& tokens);
    void parseExpression(std::vector<Token>::iterator& tokens);
    void parseOperator(std::vector<Token>::iterator& tokens);
    void parseTerminal(std::vector<Token>::iterator& tokens, TokenType terminalType);
};