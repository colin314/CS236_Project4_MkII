#pragma once

#include "Token.h"
#include "TokenType.h"
#include "Predicate.h"
#include "HeadPredicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "Expression.h"
#include "Scheme.h"
#include "Fact.h"
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
        for (size_t i = 0; i < facts.size(); i++)
        {
            delete facts.at(i);
        }
        for (size_t i = 0; i < schemes.size(); i++)
        {
            delete schemes.at(i);
        }
        for (size_t i = 0; i < queries.size(); i++)
        {
            delete queries.at(i);
        }
        
        
        
    }

    string parse(std::vector<Token>* const &inputTokens);
private:
    std::stack<string>* parseStack;
    std::queue<Token>* outputQueue;
    std::queue<Token>* schemesQueue;
    std::queue<Token>* factsQueue;
    std::queue<Token>* rulesQueue;
    std::queue<Token>* queriesQueue;
    std::vector<Scheme*> schemes;
    std::vector<Fact*> facts;
    std::vector<Predicate*> queries;

    void parseDatalogProgram(std::vector<Token>::iterator& tokens);
    void parseSchemeList(std::vector<Token>::iterator& tokens);
    void parseFactList(std::vector<Token>::iterator& tokens);
    void parseRuleList(std::vector<Token>::iterator& tokens);
    void parseQueryList(std::vector<Token>::iterator& tokens);
    void parseScheme(std::vector<Token>::iterator& tokens);
    void parseFact(std::vector<Token>::iterator& tokens);
    void parseRule(std::vector<Token>::iterator& tokens);
    void parseQuery(std::vector<Token>::iterator& tokens);
    void parseHeadPredicate(std::vector<Token>::iterator& tokens, Rule* rule);
    void parsePredicate(std::vector<Token>::iterator& tokens, std::vector<Predicate*>* predList);
    void parsePredicateList(std::vector<Token>::iterator& tokens, std::vector<Predicate*>* predList);
    void parseParameterList(std::vector<Token>::iterator& tokens);
    void parseStringList(std::vector<Token>::iterator& tokens, std::vector<std::string>* stringList);
    void parseIdList(std::vector<Token>::iterator& tokens, std::vector<Token>* idList);
    void parseParameter(std::vector<Token>::iterator& tokens);
    void parseExpression(std::vector<Token>::iterator& tokens);
    void parseOperator(std::vector<Token>::iterator& tokens);
    void parseTerminal(std::vector<Token>::iterator& tokens, TokenType terminalType);
};