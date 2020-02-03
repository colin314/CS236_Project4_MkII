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
#include <sstream>
#include <set>

using std::string;
using std::cout; using std::endl;
using std::vector; using std::set;

class DataLogger {
public:
    DataLogger() {
        success = false;
        failToken = nullptr;
    }
    ~DataLogger() {
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
        for (size_t i = 0; i < rules.size(); i++) {
            delete rules.at(i);
        }
        if (failToken != nullptr) { delete failToken; }
    }
    void parse(vector<Token>* inputTokens);
    string toString();
private:
    vector<Scheme*> schemes;
    vector<Fact*> facts;
    vector<Rule*> rules;
    vector<Predicate*> queries;
    set<string> domain;
    bool success;
    Token* failToken;

    void parseDatalogProgram(vector<Token>::iterator& tokens);
    void parseSchemeList(vector<Token>::iterator& tokens);
    void parseFactList(vector<Token>::iterator& tokens);
    void parseRuleList(vector<Token>::iterator& tokens);
    void parseQueryList(vector<Token>::iterator& tokens);
    void parseScheme(vector<Token>::iterator& tokens);
    void parseFact(vector<Token>::iterator& tokens);
    void parseRule(vector<Token>::iterator& tokens);
    void parseQuery(vector<Token>::iterator& tokens);
    void parseHeadPredicate(vector<Token>::iterator& tokens, Rule* rule);
    void parsePredicate(vector<Token>::iterator& tokens, vector<Predicate*>* predList);
    void parsePredicateList(vector<Token>::iterator& tokens, vector<Predicate*>* predList);
    void parseParameterList(vector<Token>::iterator& tokens, vector<Parameter*>* paramList);
    void parseStringList(vector<Token>::iterator& tokens, vector<std::string>* stringList);
    void parseIdList(vector<Token>::iterator& tokens, vector<Token*>* idList);
    void parseParameter(vector<Token>::iterator& tokens, vector<Parameter*>* paramList);
    void parseExpression(vector<Token>::iterator& tokens, vector<Parameter*>* paramList);
    void parseOperator(vector<Token>::iterator& tokens, Token** opTkn);
    void parseTerminal(vector<Token>::iterator& tokens, TokenType terminalType);
    void checkTerminal(vector<Token>::iterator& tokens, TokenType ttype);
};